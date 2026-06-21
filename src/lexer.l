%{
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "src/ast.h"
#include "parser.tab.h"

int line_number = 1; // ADICIONE ESTA LINHA AQUI!
%}

%option noyywrap
%option yylineno

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
"%"			{ return '%'; }

[0-9]+                  {
    yylval.ival = atoi(yytext);
    return TOK_NUMBER;
}

[a-zA-Z_][a-zA-Z0-9_]* {
    /* Copia o texto lido para a variável semântica do Bison */
    yylval.sval = strdup(yytext);
    return TOK_IDENTIFIER;
}

\"[^\"]*\" {
    /* Truque para remover as aspas da string ("Ola Mundo" vira Ola Mundo) */
    yytext[strlen(yytext)-1] = '\0';
    yylval.sval = strdup(yytext + 1);
    return TOK_STRING;
}

.                       { std::cerr << "Erro Lexico na linha " << line_number << ": caractere invalido '" << yytext << "'\n"; }
