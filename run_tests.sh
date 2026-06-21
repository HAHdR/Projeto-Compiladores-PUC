#!/bin/bash

echo "Iniciando script de testes do meu_compilador..."

#Lista dos programas de teste e o argumento que passaremos para eles
#Formato: "nome_do_arquivo.pas argumento_de_teste"
declare -a testes=(
    "factor.pas 84"       # Esperado: fatores primos de 84
    "isprime.pas 23"      # Esperado: 1 (True)
    "fibonacci.pas 15"    # Esperado: primeiros 15 números da sequência
    "pidigits.pas 9"      # Esperado: primeiros 9 dígitos de Pi
)

echo "================================================"

for teste in "${testes[@]}"; do
    #Separa o nome do arquivo e o argumento
    read -r arquivo argumento <<< "$teste"
    
    # Extrai o nome sem a extensão (ex: de 'factor.pas' vira apenas 'factor')
    nome_base=$(basename "$arquivo" .pas)

    echo "Testando: $arquivo"
    
    #1- Chama o compilador para processar o .pas
    ./meu_compilador "$arquivo" 

    #2- Usa o clang para transformar o código LLVM IR no executável final nativo.
    clang "$nome_base.ll" -o "$nome_base"

    if [ -f "./$nome_base" ]; then
        echo "Executando: ./$nome_base $argumento"
        echo "------------------- SAÍDA -------------------"
        
        #Executa o programa passando o argumento
        ./"$nome_base" "$argumento"
        
        echo "---------------------------------------------"
    else
        echo "Erro: Executável $nome_base não foi gerado."
    fi
    echo ""
done

echo "Testes finalizados"
