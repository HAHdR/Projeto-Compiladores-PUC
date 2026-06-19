#include <iostream>
#include <cstdio>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>

extern int yyparse(); 
extern FILE* yyin; 

// Alocação das instâncias globais
llvm::LLVMContext* TheContext = nullptr;
llvm::Module* TheModule = nullptr;
llvm::IRBuilder<>* Builder = nullptr;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso correto: " << argv[0] << " <arquivo_fonte.pas>\n";
        return 1;
    }

    FILE* infile = fopen(argv[1], "r");
    if (!infile) {
        std::cerr << "Erro crasso: Nao foi possivel abrir o arquivo " << argv[1] << "\n";
        return 1;
    }

    yyin = infile;

    // INICIALIZAÇÃO BLINDADA: Garante a criação dos objetos antes de qualquer parser rodar
    TheContext = new llvm::LLVMContext();
    TheModule = new llvm::Module("meu_compilador_module", *TheContext);
    Builder = new llvm::IRBuilder<>(*TheContext);

    std::cout << "Iniciando a compilacao: " << argv[1] << "\n";
    
    int result = yyparse();
    fclose(infile);

    if (result == 0 && TheModule) {
        std::cout << "Analise concluida! Gravando o codigo LLVM em 'saida.ll'...\n";
        
        std::error_code EC;
        llvm::raw_fd_ostream dest("saida.ll", EC, llvm::sys::fs::OF_None);
        
        if (EC) {
            std::cerr << "Erro ao criar o arquivo de saida: " << EC.message() << "\n";
            return 1;
        }

        TheModule->print(dest, nullptr);
        std::cout << "Arquivo 'saida.ll' gerado com SUCESSO!\n";
    } else {
        std::cerr << "Falha na compilacao devido a erros.\n";
    }

    return result;
}
