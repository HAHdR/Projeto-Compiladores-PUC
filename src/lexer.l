%{
#include <iostream>
#include <string>

enum Tokens {
    TOK_PROGRAM = 258, TOK_VAR, TOK_BEGIN, TOK_END,
    TOK_INTEGER, TOK_BOOLEAN, TOK_IDENTIFIER, TOK_NUM,
    TOK_ASSIGN, TOK_IF, TOK_THEN, TOK_ELSE, TOK_WHILE, TOK_DO
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

":="                    { return TOK_ASSIGN; }
";"                     { return ';'; }
":"                     { return ':'; }
"\."                    { return '.'; }

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
