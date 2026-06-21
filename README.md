# Projeto-Compiladores-PUC

**MEMBROS:** Henrique Abreu Hollanda da Rocha, Matheus Guido Noronha Moreira Passos e Thiago Salanti Mambrini.

### 1. Modelo de Sintaxe
O compilador baseia-se na sintaxe da linguagem de programação **Mini-Pascal**, seguindo uma estrutura de programa fortemente tipada e em blocos.

### 2. Tipos de Dados Suportados
*   `integer`: Utilizado para todas as operações aritméticas, contagens dos laços de repetição e passagem de parâmetros.
*   `boolean`: Utilizado para avaliar as expressões lógicas e condições de controle de fluxo (`true` ou `false`).

### 3. Estruturas de Controle e Sintaxe
*   **Declaração de Variáveis:** Feita no bloco `var`, utilizando a sintaxe padrão `nome_variavel : tipo;`.
*   **Atribuição:** Operador `:=` (ex: `x := 10;`).
*   **Estruturas Condicionais:** `if condition then ... else ...`
*   **Laços de Repetição:** `while condition do ...`
*   **Estrutura Principal:**

```pascal
    program NomeDoPrograma;
    var
      x : integer;
    begin
      // Código aqui
    end.
    ```

### 4. Padrão de Comentários
Para otimizar o processamento do analisador léxico (Flex), a linguagem aceitará exclusivamente comentários de linha única utilizando o delimitador:
*   `//` (Comentário de estilo de linha comum)
```

### 4. Capturas de Tela do Terminal
* Ao executar o script de automação do bash que compila todos os programas-testes e os executa com parâmetros específicos, obtemos os seguintes resultados: 
<img width="939" height="536" alt="Captura de tela 2026-06-21 204741" src="https://github.com/user-attachments/assets/f89de448-b058-4f06-9b03-c8441c5e5b0b" />
<img width="775" height="439" alt="image" src="https://github.com/user-attachments/assets/c3d9224e-bda3-4973-bce8-9ea236cb7563" />
<img width="747" height="398" alt="image" src="https://github.com/user-attachments/assets/966c3be1-e687-49bc-93d8-355ad6d0e702" />




