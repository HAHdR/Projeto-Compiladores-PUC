%{
#include <iostream>
#include <string>
#include "parser.tab.h"

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
