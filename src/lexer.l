%{
#include <iostream>
#include <string>

// Enumeração com TODOS os tokens necessários para o projeto completo
enum Tokens {
    TOK_PROGRAM = 258, TOK_VAR, TOK_BEGIN, TOK_END,
    TOK_INTEGER, TOK_BOOLEAN, TOK_IDENTIFIER, TOK_NUM,
    TOK_ASSIGN, TOK_IF, TOK_THEN, TOK_ELSE, TOK_WHILE, TOK_DO,
    TOK_FOR, TOK_TO, TOK_PROCEDURE, TOK_FUNCTION,
    TOK_WRITE, TOK_WRITELN, TOK_STRING,
    TOK_AND, TOK_OR, TOK_NOT, TOK_EQ, TOK_LT, TOK_GT
};

int line_number = 1;
%}

%option noyywrap

%%

[ \t\r]                 { }
\n                      { line_number++; }

"//".* { }

"program"               { return TOK_PROGRAM; }
"var"                   { return TOK_VAR; }
"begin"                 { return TOK_BEGIN; }
"end"                   { return TOK_END; }
"integer"               { return TOK_INTEGER; }
"boolean"               { return TOK_BOOLEAN; }

"if"                    { return TOK_IF; }
"then"                  { return TOK_THEN; }
"else"                  { return TOK_ELSE; }
"while"                 { return TOK_WHILE; }
"do"                    { return TOK_DO; }
"for"                   { return TOK_FOR; }
"to"                    { return TOK_TO; }

"procedure"             { return TOK_PROCEDURE; }
"function"              { return TOK_FUNCTION; }

"write"                 { return TOK_WRITE; }
"writeln"               { return TOK_WRITELN; }

"and"                   { return TOK_AND; }
"or"                    { return TOK_OR; }
"not"                   { return TOK_NOT; }

":="                    { return TOK_ASSIGN; }
"="                     { return TOK_EQ; }
"<"                     { return TOK_LT; }
">"                     { return TOK_GT; }

"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
";"                     { return ';'; }
":"                     { return ':'; }
"\."                    { return '.'; }
","                     { return ','; }
"\("                    { return '('; }
"\)"                    { return ')'; }

\"[^\"]*\"              { return TOK_STRING; }

[0-9]+                  { return TOK_NUM; }
[a-zA-Z][a-zA-Z0-9]* { return TOK_IDENTIFIER; }

.                       { std::cerr << "Erro Lexico na linha " << line_number << ": caractere invalido '" << yytext << "'\n"; }

%%

int main(int argc, char** argv) {
    int token;
    while((token = yylex())) {
        std::cout << "Token: " << token << " -> " << yytext << " (Linha: " << line_number << ")\n";
    }
    return 0;
}
