%{
#include <iostream>
#include <memory>
#include <string>
#include "src/ast.h"  // <- CORRIJA AQUI (adicione o src/)

extern int yylex();
// ...

// Protótipos das funções do Flex e de erro
extern int yylex();
extern int yylineno;
void yyerror(const char *s);

// Variável global que guardará a raiz da AST para o main.cpp acessar
BlockAST* programRoot = nullptr;
%}

%union {
    int ival;
    char* sval;
    ASTNode* ast_node;
    BlockAST* block_node;
}

/* Tokens gerados pelo analisador léxico */
%token <sval> TOK_IDENTIFIER TOK_STRING
%token <ival> TOK_NUMBER
%token TOK_PROGRAM TOK_VAR TOK_BEGIN TOK_END TOK_ASSIGN TOK_WRITELN
%token TOK_INTEGER TOK_BOOLEAN
%token TOK_IF TOK_THEN TOK_ELSE TOK_WHILE TOK_DO TOK_FOR TOK_TO
%token TOK_PROCEDURE TOK_FUNCTION TOK_WRITE TOK_AND TOK_OR TOK_NOT
%token TOK_EQ TOK_LT TOK_GT

/* Definição de tipos para evitar erros de conversão no C++ */
%type <block_node> statement_list
%type <ast_node> statement expression compound_statement

/* Precedência de operadores: da menor (topo) para a maior (base).
   Resolve ambiguidade tipo "a + b * c" e "a < b and c < d". */
%left TOK_OR
%left TOK_AND
%nonassoc TOK_EQ TOK_LT TOK_GT
%left '+' '-'
%left '*' '/'

/* Clássica resolução do "dangling else": TOK_ELSE tem precedência maior,
   então o parser prefere "shiftar" o else e associá-lo ao if mais próximo. */
%nonassoc TOK_THEN
%nonassoc TOK_ELSE

%%

/* Regra inicial do programa Mini-Pascal */
program:
    TOK_PROGRAM TOK_IDENTIFIER ';' declarations TOK_BEGIN statement_list TOK_END '.' {
        programRoot = $6; // O sexto elemento ($6) é o 'statement_list'
    }
    ;

declarations:
    /* Permite bloco de variáveis vazio */
    | TOK_VAR variable_decl_list
    ;

variable_decl_list:
    variable_decl
    | variable_decl_list variable_decl
    ;

variable_decl:
    TOK_IDENTIFIER ':' type ';' {
        // Aqui pode ser inserida a lógica de inserção na tabela de símbolos de tipos
        free($1);
    }
    ;

type:
    TOK_INTEGER
    | TOK_BOOLEAN
    ;

/* Regra que agrupa múltiplos comandos, separados por ';' (estilo Pascal).
   A terceira alternativa tolera um ';' sobrando antes do 'end'. */
statement_list:
    statement {
        $$ = new BlockAST();
        $$->addStatement(std::unique_ptr<ASTNode>($1));
    }
    | statement_list ';' statement {
        $1->addStatement(std::unique_ptr<ASTNode>($3));
        $$ = $1; // Passa o bloco acumulado adiante na árvore
    }
    | statement_list ';' {
        // Permite um ';' sobrando antes do 'end' (muito comum em Pascal)
        $$ = $1;
    }
    ;

/* Bloco begin...end usado como o corpo de um if/while/for */
compound_statement:
    TOK_BEGIN statement_list TOK_END {
        $$ = $2;
    }
    ;

/* Definição dos comandos individuais (sem ';' embutido — o ';' agora
   é só o separador entre comandos, tratado em statement_list) */
statement:
    TOK_IDENTIFIER TOK_ASSIGN expression {
        // $1 é o nome da variável (char*), $3 é o nó da expressão (ASTNode*)
        $$ = new AssignmentAST(std::string($1), std::unique_ptr<ASTNode>($3));
        free($1); // Liberta a memória do char* alocado pelo Flex
    }
    | TOK_WRITELN '(' TOK_STRING ')' {
        // Cria um nó de escrita contendo um nó de string interna
        $$ = new WritelnAST(std::unique_ptr<ASTNode>(new StringAST(std::string($3))));
        free($3);
    }
    | TOK_IF expression TOK_THEN statement %prec TOK_THEN {
        $$ = new IfAST(std::unique_ptr<ASTNode>($2), std::unique_ptr<ASTNode>($4), nullptr);
    }
    | TOK_IF expression TOK_THEN statement TOK_ELSE statement {
        $$ = new IfAST(std::unique_ptr<ASTNode>($2), std::unique_ptr<ASTNode>($4), std::unique_ptr<ASTNode>($6));
    }
    | TOK_WHILE expression TOK_DO statement {
        $$ = new WhileAST(std::unique_ptr<ASTNode>($2), std::unique_ptr<ASTNode>($4));
    }
    | compound_statement {
        $$ = $1;
    }
    ;

/* Expressões: números, variáveis, e operadores aritméticos/relacionais/lógicos */
expression:
    TOK_NUMBER {
        $$ = new NumberAST($1);
    }
    | TOK_IDENTIFIER {
        $$ = new VariableAST(std::string($1));
        free($1);
    }
    | expression '+' expression {
        $$ = new BinaryExprAST(BinOp::ADD, std::unique_ptr<ASTNode>($1), std::unique_ptr<ASTNode>($3));
    }
    | expression '-' expression {
        $$ = new BinaryExprAST(BinOp::SUB, std::unique_ptr<ASTNode>($1), std::unique_ptr<ASTNode>($3));
    }
    | expression '*' expression {
        $$ = new BinaryExprAST(BinOp::MUL, std::unique_ptr<ASTNode>($1), std::unique_ptr<ASTNode>($3));
    }
    | expression '/' expression {
        $$ = new BinaryExprAST(BinOp::DIV, std::unique_ptr<ASTNode>($1), std::unique_ptr<ASTNode>($3));
    }
    | expression TOK_LT expression {
        $$ = new BinaryExprAST(BinOp::LT, std::unique_ptr<ASTNode>($1), std::unique_ptr<ASTNode>($3));
    }
    | expression TOK_GT expression {
        $$ = new BinaryExprAST(BinOp::GT, std::unique_ptr<ASTNode>($1), std::unique_ptr<ASTNode>($3));
    }
    | expression TOK_EQ expression {
        $$ = new BinaryExprAST(BinOp::EQ, std::unique_ptr<ASTNode>($1), std::unique_ptr<ASTNode>($3));
    }
    | expression TOK_AND expression {
        $$ = new BinaryExprAST(BinOp::AND, std::unique_ptr<ASTNode>($1), std::unique_ptr<ASTNode>($3));
    }
    | expression TOK_OR expression {
        $$ = new BinaryExprAST(BinOp::OR, std::unique_ptr<ASTNode>($1), std::unique_ptr<ASTNode>($3));
    }
    | '(' expression ')' {
        $$ = $2;
    }
    ;

%%

void yyerror(const char *s) {
    std::cerr << "Erro sintático na linha " << yylineno << ": " << s << std::endl;
}
