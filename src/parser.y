%{
#include <iostream>
#include <string>

extern int yylex();
extern int line_number;
void yyerror(const char *s);
%}

/* Define como os tokens serão tratados internamente */
%union {
    int num;
    std::string* str;
}

%token TOK_PROGRAM TOK_VAR TOK_BEGIN TOK_END
%token TOK_INTEGER TOK_BOOLEAN TOK_ASSIGN
%token TOK_IF TOK_THEN TOK_ELSE TOK_WHILE TOK_DO TOK_FOR TOK_TO
%token TOK_PROCEDURE TOK_FUNCTION TOK_WRITE TOK_WRITELN
%token TOK_AND TOK_OR TOK_NOT TOK_EQ TOK_LT TOK_GT
%token <str> TOK_IDENTIFIER TOK_STRING
%token <num> TOK_NUM

%%

/* REGRAS DA GRAMÁTICA MINI-PASCAL */

program:
    TOK_PROGRAM TOK_IDENTIFIER ';' declarations block '.' 
    { std::cout << "Analise Sintatica concluida com SUCESSO!\n"; }
    ;

declarations:
    TOK_VAR variable_list
    | /* vazio - caso o programa nao tenha variaveis */
    ;

variable_list:
    variable_list variable_declaration
    | variable_declaration
    ;

variable_declaration:
    TOK_IDENTIFIER ':' type ';'
    ;

type:
    TOK_INTEGER
    | TOK_BOOLEAN
    | TOK_STRING
    ;

block:
    TOK_BEGIN statements TOK_END
    ;

statements:
    statements statement ';'
    | statement ';'
    | /* vazio */
    ;

statement:
    TOK_IDENTIFIER TOK_ASSIGN expression
    | TOK_WRITELN '(' TOK_STRING ')'
    | TOK_WRITELN '(' expression ')'
    | block
    ;

expression:
    TOK_NUM
    | TOK_IDENTIFIER
    | expression '+' expression
    | expression '-' expression
    ;

%%

/* Função de tratamento de erro */
void yyerror(const char *s) {
    std::cerr << "Erro Sintatico na linha " << line_number << ": " << s << "\n";
}
