#include <iostream>
#include <cstdio>

// Indica que essas funções e variáveis vêm dos arquivos do Bison/Flex
extern int yyparse(); 
extern FILE* yyin; 

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso correto: " << argv[0] << " <arquivo_fonte.pas>\n";
        return 1;
    }

    // Para abrir o arquivo .pas passado por argumento no terminal
    FILE* infile = fopen(argv[1], "r");
    if (!infile) {
        std::cerr << "Erro crasso: Nao foi possivel abrir o arquivo " << argv[1] << "\n";
        return 1;
    }

    // Diz para o Flex ler o arquivo em vez de ficar esperando o teclado
    yyin = infile;

    std::cout << "Iniciando a compilacao do arquivo: " << argv[1] << "\n";
    
    // Dispara o Parser (Bison)
    int result = yyparse();

    fclose(infile);

    if (result == 0) {
        std::cout << "Parabens! Sintaxe correta e validada!\n";
    } else {
        std::cerr << "Falha: O codigo possui erros sintatitcos.\n";
    }

    return result;
}
