/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOK_IDENTIFIER = 258,          /* TOK_IDENTIFIER  */
    TOK_STRING = 259,              /* TOK_STRING  */
    TOK_NUMBER = 260,              /* TOK_NUMBER  */
    TOK_PROGRAM = 261,             /* TOK_PROGRAM  */
    TOK_VAR = 262,                 /* TOK_VAR  */
    TOK_BEGIN = 263,               /* TOK_BEGIN  */
    TOK_END = 264,                 /* TOK_END  */
    TOK_ASSIGN = 265,              /* TOK_ASSIGN  */
    TOK_WRITELN = 266,             /* TOK_WRITELN  */
    TOK_INTEGER = 267,             /* TOK_INTEGER  */
    TOK_BOOLEAN = 268,             /* TOK_BOOLEAN  */
    TOK_IF = 269,                  /* TOK_IF  */
    TOK_THEN = 270,                /* TOK_THEN  */
    TOK_ELSE = 271,                /* TOK_ELSE  */
    TOK_WHILE = 272,               /* TOK_WHILE  */
    TOK_DO = 273,                  /* TOK_DO  */
    TOK_FOR = 274,                 /* TOK_FOR  */
    TOK_TO = 275,                  /* TOK_TO  */
    TOK_PROCEDURE = 276,           /* TOK_PROCEDURE  */
    TOK_FUNCTION = 277,            /* TOK_FUNCTION  */
    TOK_WRITE = 278,               /* TOK_WRITE  */
    TOK_AND = 279,                 /* TOK_AND  */
    TOK_OR = 280,                  /* TOK_OR  */
    TOK_NOT = 281,                 /* TOK_NOT  */
    TOK_EQ = 282,                  /* TOK_EQ  */
    TOK_LT = 283,                  /* TOK_LT  */
    TOK_GT = 284                   /* TOK_GT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "src/parser.y"

    int ival;
    char* sval;
    ASTNode* ast_node;
    BlockAST* block_node;
    std::vector<std::string>* param_vec;
    std::vector<ASTNode*>* arg_vec;

#line 102 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
