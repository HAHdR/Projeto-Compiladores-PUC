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

        // 2. Cria a assinatura da função main: int main()
        llvm::FunctionType *MainType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(TheContext), false);
        llvm::Function *MainFunction = llvm::Function::Create(
            MainType, llvm::Function::ExternalLinkage, "main", TheModule.get());

        // 3. Cria o bloco básico de entrada e posiciona o builder nele
        llvm::BasicBlock *EntryBB = llvm::BasicBlock::Create(TheContext, "entry", MainFunction);
        Builder.SetInsertPoint(EntryBB);

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