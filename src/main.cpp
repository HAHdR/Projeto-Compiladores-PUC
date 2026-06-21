#include <iostream>
#include <memory>
#include <system_error>
#include <cstdio>
#include "ast.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"

extern int yyparse();
extern BlockAST* programRoot;
extern FILE* yyin; // declarado pelo Flex; por padrão aponta para stdin

int main(int argc, char** argv) {
    // Se o usuário passou um arquivo .pas como argumento, lemos dele.
    // Sem isso o yylex() fica esperando entrada digitada no terminal (stdin).
    if (argc > 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            std::cerr << "Erro: não foi possível abrir o arquivo '" << argv[1] << "'" << std::endl;
            return 1;
        }
        yyin = file;
    }

    std::cout << "Iniciando análise sintática..." << std::endl;

    if (yyparse() == 0 && programRoot != nullptr) {
        std::cout << "Análise concluída com sucesso! Gerando LLVM IR..." << std::endl;

        // 1. Cria o módulo LLVM que vai conter todo o código gerado
        TheModule = std::make_unique<llvm::Module>("meu_compilador_module", TheContext);

        // 1.5. Gera as funções/procedimentos declarados no programa, ANTES do
        //      main (assim main pode chamá-los). Duas passadas:
        //      - 1ª: só os protótipos, para permitir uma função chamar outra
        //        que aparece mais abaixo no arquivo-fonte.
        //      - 2ª: o corpo de cada função/procedimento.
        for (auto &FnDef : FunctionDecls) {
            FnDef->Proto->codegen();
        }
        for (auto &FnDef : FunctionDecls) {
            FnDef->codegen();
        }

        // 2. Cria a assinatura da função main: int main(int argc, char** argv)
        //    Precisamos do argc/argv DE VERDADE (passados pelo sistema
        //    operacional) para repassar o parâmetro de linha de comando ao
        //    programa Mini-Pascal (ex: "./fibonacci 10").
        llvm::Type* PtrTy = llvm::PointerType::getUnqual(TheContext); // "ptr" genérico (LLVM moderno usa ponteiros opacos)
        llvm::FunctionType *MainType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(TheContext),
            {llvm::Type::getInt32Ty(TheContext), PtrTy}, // (i32 argc, ptr argv)
            false);
        llvm::Function *MainFunction = llvm::Function::Create(
            MainType, llvm::Function::ExternalLinkage, "main", TheModule.get());

        auto MainArgIt = MainFunction->args().begin();
        llvm::Argument *ArgC = &*MainArgIt++;
        llvm::Argument *ArgV = &*MainArgIt;
        ArgC->setName("argc");
        ArgV->setName("argv");

        // 3. Cria o bloco básico de entrada e posiciona o builder nele
        llvm::BasicBlock *EntryBB = llvm::BasicBlock::Create(TheContext, "entry", MainFunction);
        Builder.SetInsertPoint(EntryBB);

        // 3.5 Declara a função 'atoi' da libc (converte char* -> int), usada
        //     para transformar o argumento de linha de comando (uma string)
        //     no inteiro que o programa Mini-Pascal vai efetivamente usar.
        llvm::Function *AtoiFn = TheModule->getFunction("atoi");
        if (!AtoiFn) {
            llvm::FunctionType *AtoiType = llvm::FunctionType::get(
                llvm::Type::getInt32Ty(TheContext), {PtrTy}, false);
            AtoiFn = llvm::Function::Create(AtoiType, llvm::Function::ExternalLinkage, "atoi", TheModule.get());
        }

        // 3.6 Expõe argc e argv[1] (já convertido p/ inteiro) como variáveis
        //     pré-declaradas "argc" e "argv1", acessíveis direto no Mini-Pascal
        //     (ex: "n := argv1;"). Se o programa for executado sem argumento
        //     extra (argc <= 1), argv1 fica 0 em vez de invadir memória inválida.
        llvm::AllocaInst *ArgcAlloca  = Builder.CreateAlloca(llvm::Type::getInt32Ty(TheContext), nullptr, "argc_slot");
        llvm::AllocaInst *Argv1Alloca = Builder.CreateAlloca(llvm::Type::getInt32Ty(TheContext), nullptr, "argv1_slot");
        Builder.CreateStore(ArgC, ArgcAlloca);
        NamedValues["argc"] = ArgcAlloca;
        NamedValues["argv1"] = Argv1Alloca;

        llvm::BasicBlock *HasArgBB  = llvm::BasicBlock::Create(TheContext, "hasarg", MainFunction);
        llvm::BasicBlock *NoArgBB   = llvm::BasicBlock::Create(TheContext, "noarg", MainFunction);
        llvm::BasicBlock *ArgDoneBB = llvm::BasicBlock::Create(TheContext, "argdone", MainFunction);

        llvm::Value* HasArgCond = Builder.CreateICmpSGT(
            ArgC, llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 1), "hasargcond");
        Builder.CreateCondBr(HasArgCond, HasArgBB, NoArgBB);

        // Caso normal: leu argv[1] (uma string) e converte para inteiro com atoi
        Builder.SetInsertPoint(HasArgBB);
        llvm::Value* Argv1Slot = Builder.CreateGEP(
            PtrTy, ArgV, llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 1), "argv1slot");
        llvm::Value* Argv1Str = Builder.CreateLoad(PtrTy, Argv1Slot, "argv1str");
        llvm::Value* Argv1Int = Builder.CreateCall(AtoiFn, {Argv1Str}, "argv1int");
        Builder.CreateStore(Argv1Int, Argv1Alloca);
        Builder.CreateBr(ArgDoneBB);

        // Caso sem argumento extra: argv1 = 0 (evita acessar memória fora do array argv)
        Builder.SetInsertPoint(NoArgBB);
        Builder.CreateStore(llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0), Argv1Alloca);
        Builder.CreateBr(ArgDoneBB);

        Builder.SetInsertPoint(ArgDoneBB);

        // 4. Dispara a geração de código recursiva a partir da raiz da árvore
        //    (cada statement do programa Mini-Pascal vira instruções LLVM aqui dentro)
        programRoot->codegen();

        // 5. Toda função main do LLVM precisa terminar com um "ret" explícito.
        //    Sem isso o IR fica mal formado e o LLVM recusa a verificação/otimização.
        Builder.CreateRet(llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), 0));

        // 6. Verifica se o IR gerado está bem formado (pega bugs de codegen na hora)
        if (llvm::verifyFunction(*MainFunction, &llvm::errs())) {
            std::cerr << "Erro: função main mal formada no LLVM IR!" << std::endl;
            return 1;
        }

        // 7. Grava o resultado no arquivo de saída saida.ll
        std::error_code EC;
        llvm::raw_fd_ostream OutFile("saida.ll", EC, llvm::sys::fs::OF_None);
        if (EC) {
            std::cerr << "Erro ao abrir saida.ll: " << EC.message() << std::endl;
            return 1;
        }
        TheModule->print(OutFile, nullptr);
        std::cout << "LLVM IR gravado em saida.ll" << std::endl;
    } else {
        std::cerr << "Falha na compilação." << std::endl;
        return 1;
    }
    return 0;
}