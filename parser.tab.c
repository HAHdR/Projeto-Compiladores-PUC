/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

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

// Lista global de todas as funções/procedimentos declarados (ver ast.h)
std::vector<std::unique_ptr<FunctionDefAST>> FunctionDecls;

#line 92 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TOK_IDENTIFIER = 3,             /* TOK_IDENTIFIER  */
  YYSYMBOL_TOK_STRING = 4,                 /* TOK_STRING  */
  YYSYMBOL_TOK_NUMBER = 5,                 /* TOK_NUMBER  */
  YYSYMBOL_TOK_PROGRAM = 6,                /* TOK_PROGRAM  */
  YYSYMBOL_TOK_VAR = 7,                    /* TOK_VAR  */
  YYSYMBOL_TOK_BEGIN = 8,                  /* TOK_BEGIN  */
  YYSYMBOL_TOK_END = 9,                    /* TOK_END  */
  YYSYMBOL_TOK_ASSIGN = 10,                /* TOK_ASSIGN  */
  YYSYMBOL_TOK_WRITELN = 11,               /* TOK_WRITELN  */
  YYSYMBOL_TOK_INTEGER = 12,               /* TOK_INTEGER  */
  YYSYMBOL_TOK_BOOLEAN = 13,               /* TOK_BOOLEAN  */
  YYSYMBOL_TOK_IF = 14,                    /* TOK_IF  */
  YYSYMBOL_TOK_THEN = 15,                  /* TOK_THEN  */
  YYSYMBOL_TOK_ELSE = 16,                  /* TOK_ELSE  */
  YYSYMBOL_TOK_WHILE = 17,                 /* TOK_WHILE  */
  YYSYMBOL_TOK_DO = 18,                    /* TOK_DO  */
  YYSYMBOL_TOK_FOR = 19,                   /* TOK_FOR  */
  YYSYMBOL_TOK_TO = 20,                    /* TOK_TO  */
  YYSYMBOL_TOK_PROCEDURE = 21,             /* TOK_PROCEDURE  */
  YYSYMBOL_TOK_FUNCTION = 22,              /* TOK_FUNCTION  */
  YYSYMBOL_TOK_WRITE = 23,                 /* TOK_WRITE  */
  YYSYMBOL_TOK_AND = 24,                   /* TOK_AND  */
  YYSYMBOL_TOK_OR = 25,                    /* TOK_OR  */
  YYSYMBOL_TOK_NOT = 26,                   /* TOK_NOT  */
  YYSYMBOL_TOK_EQ = 27,                    /* TOK_EQ  */
  YYSYMBOL_TOK_LT = 28,                    /* TOK_LT  */
  YYSYMBOL_TOK_GT = 29,                    /* TOK_GT  */
  YYSYMBOL_30_ = 30,                       /* '+'  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '*'  */
  YYSYMBOL_33_ = 33,                       /* '/'  */
  YYSYMBOL_34_ = 34,                       /* ';'  */
  YYSYMBOL_35_ = 35,                       /* '.'  */
  YYSYMBOL_36_ = 36,                       /* '('  */
  YYSYMBOL_37_ = 37,                       /* ')'  */
  YYSYMBOL_38_ = 38,                       /* ':'  */
  YYSYMBOL_39_ = 39,                       /* ','  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_program = 41,                   /* program  */
  YYSYMBOL_subprogram_decls = 42,          /* subprogram_decls  */
  YYSYMBOL_function_decl = 43,             /* function_decl  */
  YYSYMBOL_procedure_decl = 44,            /* procedure_decl  */
  YYSYMBOL_param_list_opt = 45,            /* param_list_opt  */
  YYSYMBOL_param_list = 46,                /* param_list  */
  YYSYMBOL_arg_list_opt = 47,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 48,                  /* arg_list  */
  YYSYMBOL_declarations = 49,              /* declarations  */
  YYSYMBOL_variable_decl_list = 50,        /* variable_decl_list  */
  YYSYMBOL_variable_decl = 51,             /* variable_decl  */
  YYSYMBOL_type = 52,                      /* type  */
  YYSYMBOL_statement_list = 53,            /* statement_list  */
  YYSYMBOL_compound_statement = 54,        /* compound_statement  */
  YYSYMBOL_statement = 55,                 /* statement  */
  YYSYMBOL_expression = 56                 /* expression  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   198

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  49
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  126

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    37,    32,    30,    39,    31,    35,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    38,    34,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    63,    63,    70,    72,    73,    78,    90,   102,   103,
     107,   112,   121,   122,   126,   130,   136,   138,   142,   143,
     147,   154,   155,   161,   165,   169,   177,   185,   190,   195,
     199,   202,   205,   208,   214,   223,   230,   233,   237,   241,
     249,   252,   255,   258,   261,   264,   267,   270,   273,   276
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TOK_IDENTIFIER",
  "TOK_STRING", "TOK_NUMBER", "TOK_PROGRAM", "TOK_VAR", "TOK_BEGIN",
  "TOK_END", "TOK_ASSIGN", "TOK_WRITELN", "TOK_INTEGER", "TOK_BOOLEAN",
  "TOK_IF", "TOK_THEN", "TOK_ELSE", "TOK_WHILE", "TOK_DO", "TOK_FOR",
  "TOK_TO", "TOK_PROCEDURE", "TOK_FUNCTION", "TOK_WRITE", "TOK_AND",
  "TOK_OR", "TOK_NOT", "TOK_EQ", "TOK_LT", "TOK_GT", "'+'", "'-'", "'*'",
  "'/'", "';'", "'.'", "'('", "')'", "':'", "','", "$accept", "program",
  "subprogram_decls", "function_decl", "procedure_decl", "param_list_opt",
  "param_list", "arg_list_opt", "arg_list", "declarations",
  "variable_decl_list", "variable_decl", "type", "statement_list",
  "compound_statement", "statement", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-93)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       3,     7,    28,    -8,   -93,    44,    32,   -93,    11,    32,
     -93,    26,     4,   -93,    42,    51,    54,   -93,   -93,   -93,
     -93,    55,    -7,    42,    24,    16,    16,    61,    52,    -4,
     -93,   -93,    56,    57,   -93,    16,    16,    -3,    16,    58,
     -93,   -93,    16,    53,    72,    77,    16,    31,    42,    92,
      92,   144,    70,    69,   144,   -93,    98,    16,   109,    42,
      16,    16,    16,    16,    16,    16,    16,    16,    16,    42,
      16,   120,   -93,   -93,    71,    73,    80,    74,   -93,    16,
     -93,    87,   -93,   116,   151,    43,   158,   158,   158,    30,
      30,   -93,   -93,   -93,   134,   -93,     4,   121,   140,   118,
     144,   -93,    42,    16,   -93,    44,   122,     4,   -93,    88,
     162,     4,   159,    42,    42,   -93,    44,   -93,    -2,   184,
     160,    42,   -93,    -1,   161,   -93
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,    16,     0,     3,     0,    17,
      18,     0,     0,    19,     0,     0,     0,     4,     5,    21,
      22,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    23,     0,     0,    20,     0,    12,     0,     0,    38,
      37,    36,     0,     0,     0,     0,     0,     0,    25,     8,
       8,    27,     0,    13,    14,    26,     0,    12,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,    24,     0,     0,     9,     0,    34,     0,
      28,     0,    49,    30,    47,    48,    46,    44,    45,    40,
      41,    42,    43,    32,     0,    29,     0,     0,     0,     0,
      15,    39,     0,     0,    10,    16,     0,     0,    31,     0,
       0,     0,     0,     0,     0,    11,    16,    33,     0,     0,
       0,     0,     7,     0,     0,     6
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -93,   -93,   -93,   -93,   -93,   146,   -93,   141,   -93,   -92,
     -93,   188,   -84,   -23,   -93,   -44,   -24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    11,    17,    18,    75,    76,    52,    53,     7,
       9,    10,    21,    29,    30,    31,    54
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      37,    43,    44,    35,    73,    47,    55,   120,   124,     1,
       3,    51,   104,   110,    56,    83,    19,    20,    58,    39,
      40,    41,    71,   112,   119,    93,     5,   115,     4,    36,
      48,    48,    48,    48,    14,     8,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    22,    94,    15,    16,    12,
      23,     6,    42,    24,    32,   100,    25,    33,   108,    26,
      38,    27,    67,    68,    45,    28,    72,    60,    59,   117,
      62,    63,    64,    65,    66,    67,    68,    60,    61,   109,
      62,    63,    64,    65,    66,    67,    68,    70,    46,    34,
      69,   118,    49,    50,    57,    74,    60,    61,   123,    62,
      63,    64,    65,    66,    67,    68,   113,    78,    79,    96,
      97,    99,    60,    61,    98,    62,    63,    64,    65,    66,
      67,    68,    60,    61,   101,    62,    63,    64,    65,    66,
      67,    68,   102,    60,    61,    80,    62,    63,    64,    65,
      66,    67,    68,   106,    60,    61,    82,    62,    63,    64,
      65,    66,    67,    68,   103,   105,   107,    95,    60,    61,
     111,    62,    63,    64,    65,    66,    67,    68,    60,    61,
     114,    62,    63,    64,    65,    66,    67,    68,    62,    63,
      64,    65,    66,    67,    68,    -1,    -1,    -1,    65,    66,
      67,    68,   121,   116,   122,   125,    77,    13,    81
};

static const yytype_int8 yycheck[] =
{
      23,    25,    26,    10,    48,     9,     9,     9,     9,     6,
       3,    35,    96,   105,    38,    59,    12,    13,    42,     3,
       4,     5,    46,   107,   116,    69,    34,   111,     0,    36,
      34,    34,    34,    34,     8,     3,    60,    61,    62,    63,
      64,    65,    66,    67,    68,     3,    70,    21,    22,    38,
       8,     7,    36,    11,     3,    79,    14,     3,   102,    17,
      36,    19,    32,    33,     3,    23,    35,    24,    15,   113,
      27,    28,    29,    30,    31,    32,    33,    24,    25,   103,
      27,    28,    29,    30,    31,    32,    33,    10,    36,    34,
      18,   114,    36,    36,    36,     3,    24,    25,   121,    27,
      28,    29,    30,    31,    32,    33,    18,    37,    39,    38,
      37,    37,    24,    25,    34,    27,    28,    29,    30,    31,
      32,    33,    24,    25,    37,    27,    28,    29,    30,    31,
      32,    33,    16,    24,    25,    37,    27,    28,    29,    30,
      31,    32,    33,     3,    24,    25,    37,    27,    28,    29,
      30,    31,    32,    33,    20,    34,    38,    37,    24,    25,
      38,    27,    28,    29,    30,    31,    32,    33,    24,    25,
       8,    27,    28,    29,    30,    31,    32,    33,    27,    28,
      29,    30,    31,    32,    33,    27,    28,    29,    30,    31,
      32,    33,     8,    34,    34,    34,    50,     9,    57
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    41,     3,     0,    34,     7,    49,     3,    50,
      51,    42,    38,    51,     8,    21,    22,    43,    44,    12,
      13,    52,     3,     8,    11,    14,    17,    19,    23,    53,
      54,    55,     3,     3,    34,    10,    36,    53,    36,     3,
       4,     5,    36,    56,    56,     3,    36,     9,    34,    36,
      36,    56,    47,    48,    56,     9,    56,    36,    56,    15,
      24,    25,    27,    28,    29,    30,    31,    32,    33,    18,
      10,    56,    35,    55,     3,    45,    46,    45,    37,    39,
      37,    47,    37,    55,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    55,    56,    37,    38,    37,    34,    37,
      56,    37,    16,    20,    52,    34,     3,    38,    55,    56,
      49,    38,    52,    18,     8,    52,    34,    55,    53,    49,
       9,     8,    34,    53,     9,    34
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    43,    44,    45,    45,
      46,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    52,    52,    53,    53,    53,    54,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     9,     0,     2,     2,    13,    11,     0,     1,
       3,     5,     0,     1,     1,     3,     0,     2,     1,     2,
       4,     1,     1,     1,     3,     2,     3,     3,     4,     4,
       4,     6,     4,     8,     4,     1,     1,     1,     1,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: TOK_PROGRAM TOK_IDENTIFIER ';' declarations subprogram_decls TOK_BEGIN statement_list TOK_END '.'  */
#line 63 "src/parser.y"
                                                                                                      {
        programRoot = (yyvsp[-2].block_node); // statement_list do bloco principal (begin...end.)
    }
#line 1223 "parser.tab.c"
    break;

  case 6: /* function_decl: TOK_FUNCTION TOK_IDENTIFIER '(' param_list_opt ')' ':' type ';' declarations TOK_BEGIN statement_list TOK_END ';'  */
#line 78 "src/parser.y"
                                                                                                                      {
        std::vector<std::string> params = std::move(*(yyvsp[-9].param_vec));
        delete (yyvsp[-9].param_vec);
        auto proto = std::make_unique<PrototypeAST>(std::string((yyvsp[-11].sval)), params, /*IsFunction=*/true);
        auto body  = std::unique_ptr<BlockAST>((yyvsp[-2].block_node));
        FunctionDecls.push_back(std::make_unique<FunctionDefAST>(std::move(proto), std::move(body)));
        free((yyvsp[-11].sval));
    }
#line 1236 "parser.tab.c"
    break;

  case 7: /* procedure_decl: TOK_PROCEDURE TOK_IDENTIFIER '(' param_list_opt ')' ';' declarations TOK_BEGIN statement_list TOK_END ';'  */
#line 90 "src/parser.y"
                                                                                                              {
        std::vector<std::string> params = std::move(*(yyvsp[-7].param_vec));
        delete (yyvsp[-7].param_vec);
        auto proto = std::make_unique<PrototypeAST>(std::string((yyvsp[-9].sval)), params, /*IsFunction=*/false);
        auto body  = std::unique_ptr<BlockAST>((yyvsp[-2].block_node));
        FunctionDecls.push_back(std::make_unique<FunctionDefAST>(std::move(proto), std::move(body)));
        free((yyvsp[-9].sval));
    }
#line 1249 "parser.tab.c"
    break;

  case 8: /* param_list_opt: %empty  */
#line 102 "src/parser.y"
                { (yyval.param_vec) = new std::vector<std::string>(); }
#line 1255 "parser.tab.c"
    break;

  case 9: /* param_list_opt: param_list  */
#line 103 "src/parser.y"
                 { (yyval.param_vec) = (yyvsp[0].param_vec); }
#line 1261 "parser.tab.c"
    break;

  case 10: /* param_list: TOK_IDENTIFIER ':' type  */
#line 107 "src/parser.y"
                            {
        (yyval.param_vec) = new std::vector<std::string>();
        (yyval.param_vec)->push_back(std::string((yyvsp[-2].sval)));
        free((yyvsp[-2].sval));
    }
#line 1271 "parser.tab.c"
    break;

  case 11: /* param_list: param_list ';' TOK_IDENTIFIER ':' type  */
#line 112 "src/parser.y"
                                             {
        (yyvsp[-4].param_vec)->push_back(std::string((yyvsp[-2].sval)));
        free((yyvsp[-2].sval));
        (yyval.param_vec) = (yyvsp[-4].param_vec);
    }
#line 1281 "parser.tab.c"
    break;

  case 12: /* arg_list_opt: %empty  */
#line 121 "src/parser.y"
                { (yyval.arg_vec) = new std::vector<ASTNode*>(); }
#line 1287 "parser.tab.c"
    break;

  case 13: /* arg_list_opt: arg_list  */
#line 122 "src/parser.y"
               { (yyval.arg_vec) = (yyvsp[0].arg_vec); }
#line 1293 "parser.tab.c"
    break;

  case 14: /* arg_list: expression  */
#line 126 "src/parser.y"
               {
        (yyval.arg_vec) = new std::vector<ASTNode*>();
        (yyval.arg_vec)->push_back((yyvsp[0].ast_node));
    }
#line 1302 "parser.tab.c"
    break;

  case 15: /* arg_list: arg_list ',' expression  */
#line 130 "src/parser.y"
                              {
        (yyvsp[-2].arg_vec)->push_back((yyvsp[0].ast_node));
        (yyval.arg_vec) = (yyvsp[-2].arg_vec);
    }
#line 1311 "parser.tab.c"
    break;

  case 20: /* variable_decl: TOK_IDENTIFIER ':' type ';'  */
#line 147 "src/parser.y"
                                {
        // Aqui pode ser inserida a lógica de inserção na tabela de símbolos de tipos
        free((yyvsp[-3].sval));
    }
#line 1320 "parser.tab.c"
    break;

  case 23: /* statement_list: statement  */
#line 161 "src/parser.y"
              {
        (yyval.block_node) = new BlockAST();
        (yyval.block_node)->addStatement(std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1329 "parser.tab.c"
    break;

  case 24: /* statement_list: statement_list ';' statement  */
#line 165 "src/parser.y"
                                   {
        (yyvsp[-2].block_node)->addStatement(std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
        (yyval.block_node) = (yyvsp[-2].block_node); // Passa o bloco acumulado adiante na árvore
    }
#line 1338 "parser.tab.c"
    break;

  case 25: /* statement_list: statement_list ';'  */
#line 169 "src/parser.y"
                         {
        // Permite um ';' sobrando antes do 'end' (muito comum em Pascal)
        (yyval.block_node) = (yyvsp[-1].block_node);
    }
#line 1347 "parser.tab.c"
    break;

  case 26: /* compound_statement: TOK_BEGIN statement_list TOK_END  */
#line 177 "src/parser.y"
                                     {
        (yyval.ast_node) = (yyvsp[-1].block_node);
    }
#line 1355 "parser.tab.c"
    break;

  case 27: /* statement: TOK_IDENTIFIER TOK_ASSIGN expression  */
#line 185 "src/parser.y"
                                         {
        // $1 é o nome da variável (char*), $3 é o nó da expressão (ASTNode*)
        (yyval.ast_node) = new AssignmentAST(std::string((yyvsp[-2].sval)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
        free((yyvsp[-2].sval)); // Liberta a memória do char* alocado pelo Flex
    }
#line 1365 "parser.tab.c"
    break;

  case 28: /* statement: TOK_WRITELN '(' expression ')'  */
#line 190 "src/parser.y"
                                     {
        // Aceita string, inteiro, variável, chamada de função, etc.
        // O codegen decide %s ou %d olhando o tipo do valor gerado.
        (yyval.ast_node) = new WritelnAST(std::unique_ptr<ASTNode>((yyvsp[-1].ast_node)), /*Newline=*/true);
    }
#line 1375 "parser.tab.c"
    break;

  case 29: /* statement: TOK_WRITE '(' expression ')'  */
#line 195 "src/parser.y"
                                   {
        // Igual ao writeln, mas sem quebra de linha ao final.
        (yyval.ast_node) = new WritelnAST(std::unique_ptr<ASTNode>((yyvsp[-1].ast_node)), /*Newline=*/false);
    }
#line 1384 "parser.tab.c"
    break;

  case 30: /* statement: TOK_IF expression TOK_THEN statement  */
#line 199 "src/parser.y"
                                                          {
        (yyval.ast_node) = new IfAST(std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)), nullptr);
    }
#line 1392 "parser.tab.c"
    break;

  case 31: /* statement: TOK_IF expression TOK_THEN statement TOK_ELSE statement  */
#line 202 "src/parser.y"
                                                              {
        (yyval.ast_node) = new IfAST(std::unique_ptr<ASTNode>((yyvsp[-4].ast_node)), std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1400 "parser.tab.c"
    break;

  case 32: /* statement: TOK_WHILE expression TOK_DO statement  */
#line 205 "src/parser.y"
                                            {
        (yyval.ast_node) = new WhileAST(std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1408 "parser.tab.c"
    break;

  case 33: /* statement: TOK_FOR TOK_IDENTIFIER TOK_ASSIGN expression TOK_TO expression TOK_DO statement  */
#line 208 "src/parser.y"
                                                                                      {
        // for $2 := $4 to $6 do $8
        (yyval.ast_node) = new ForAST(std::string((yyvsp[-6].sval)), std::unique_ptr<ASTNode>((yyvsp[-4].ast_node)),
                         std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
        free((yyvsp[-6].sval));
    }
#line 1419 "parser.tab.c"
    break;

  case 34: /* statement: TOK_IDENTIFIER '(' arg_list_opt ')'  */
#line 214 "src/parser.y"
                                          {
        // Chamada de procedimento usada como statement (ex: "Imprime(x);").
        // O valor de retorno (se algum) é descartado pelo BlockAST.
        std::vector<std::unique_ptr<ASTNode>> args;
        for (auto* a : *(yyvsp[-1].arg_vec)) args.push_back(std::unique_ptr<ASTNode>(a));
        delete (yyvsp[-1].arg_vec);
        (yyval.ast_node) = new CallExprAST(std::string((yyvsp[-3].sval)), std::move(args));
        free((yyvsp[-3].sval));
    }
#line 1433 "parser.tab.c"
    break;

  case 35: /* statement: compound_statement  */
#line 223 "src/parser.y"
                         {
        (yyval.ast_node) = (yyvsp[0].ast_node);
    }
#line 1441 "parser.tab.c"
    break;

  case 36: /* expression: TOK_NUMBER  */
#line 230 "src/parser.y"
               {
        (yyval.ast_node) = new NumberAST((yyvsp[0].ival));
    }
#line 1449 "parser.tab.c"
    break;

  case 37: /* expression: TOK_STRING  */
#line 233 "src/parser.y"
                 {
        (yyval.ast_node) = new StringAST(std::string((yyvsp[0].sval)));
        free((yyvsp[0].sval));
    }
#line 1458 "parser.tab.c"
    break;

  case 38: /* expression: TOK_IDENTIFIER  */
#line 237 "src/parser.y"
                     {
        (yyval.ast_node) = new VariableAST(std::string((yyvsp[0].sval)));
        free((yyvsp[0].sval));
    }
#line 1467 "parser.tab.c"
    break;

  case 39: /* expression: TOK_IDENTIFIER '(' arg_list_opt ')'  */
#line 241 "src/parser.y"
                                          {
        // Chamada de função usada dentro de uma expressão (ex: "x := Fatorial(5);")
        std::vector<std::unique_ptr<ASTNode>> args;
        for (auto* a : *(yyvsp[-1].arg_vec)) args.push_back(std::unique_ptr<ASTNode>(a));
        delete (yyvsp[-1].arg_vec);
        (yyval.ast_node) = new CallExprAST(std::string((yyvsp[-3].sval)), std::move(args));
        free((yyvsp[-3].sval));
    }
#line 1480 "parser.tab.c"
    break;

  case 40: /* expression: expression '+' expression  */
#line 249 "src/parser.y"
                                {
        (yyval.ast_node) = new BinaryExprAST(BinOp::ADD, std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1488 "parser.tab.c"
    break;

  case 41: /* expression: expression '-' expression  */
#line 252 "src/parser.y"
                                {
        (yyval.ast_node) = new BinaryExprAST(BinOp::SUB, std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1496 "parser.tab.c"
    break;

  case 42: /* expression: expression '*' expression  */
#line 255 "src/parser.y"
                                {
        (yyval.ast_node) = new BinaryExprAST(BinOp::MUL, std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1504 "parser.tab.c"
    break;

  case 43: /* expression: expression '/' expression  */
#line 258 "src/parser.y"
                                {
        (yyval.ast_node) = new BinaryExprAST(BinOp::DIV, std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1512 "parser.tab.c"
    break;

  case 44: /* expression: expression TOK_LT expression  */
#line 261 "src/parser.y"
                                   {
        (yyval.ast_node) = new BinaryExprAST(BinOp::LT, std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1520 "parser.tab.c"
    break;

  case 45: /* expression: expression TOK_GT expression  */
#line 264 "src/parser.y"
                                   {
        (yyval.ast_node) = new BinaryExprAST(BinOp::GT, std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1528 "parser.tab.c"
    break;

  case 46: /* expression: expression TOK_EQ expression  */
#line 267 "src/parser.y"
                                   {
        (yyval.ast_node) = new BinaryExprAST(BinOp::EQ, std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1536 "parser.tab.c"
    break;

  case 47: /* expression: expression TOK_AND expression  */
#line 270 "src/parser.y"
                                    {
        (yyval.ast_node) = new BinaryExprAST(BinOp::AND, std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1544 "parser.tab.c"
    break;

  case 48: /* expression: expression TOK_OR expression  */
#line 273 "src/parser.y"
                                   {
        (yyval.ast_node) = new BinaryExprAST(BinOp::OR, std::unique_ptr<ASTNode>((yyvsp[-2].ast_node)), std::unique_ptr<ASTNode>((yyvsp[0].ast_node)));
    }
#line 1552 "parser.tab.c"
    break;

  case 49: /* expression: '(' expression ')'  */
#line 276 "src/parser.y"
                         {
        (yyval.ast_node) = (yyvsp[-1].ast_node);
    }
#line 1560 "parser.tab.c"
    break;


#line 1564 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 281 "src/parser.y"


void yyerror(const char *s) {
    std::cerr << "Erro sintático na linha " << yylineno << ": " << s << std::endl;
}
