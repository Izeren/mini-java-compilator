/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */

#line 67 "src/bison.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "bison.hpp".  */
#ifndef YY_YY_SRC_BISON_HPP_INCLUDED
# define YY_YY_SRC_BISON_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "src/grammatic.bizon" /* yacc.c:355  */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string>
    #include <stdbool.h>
    #include "shared_ptrs_nodes/Expressions.h"
	#include "shared_ptrs_nodes/Statements.h"
	#include "shared_ptrs_nodes/Classes.h"

       
    #define YYERROR_VERBOSE 1        

#line 110 "src/bison.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NEW = 258,
    CLASS = 259,
    EXTENDS = 260,
    THIS = 261,
    RETURN = 262,
    PUBLIC = 263,
    PRIVATE = 264,
    STATIC = 265,
    PRINTLN = 266,
    INT = 267,
    BOOLEAN = 268,
    VOID = 269,
    INT_ARRAY = 270,
    LENGTH = 271,
    TRUE = 272,
    FALSE = 273,
    WHILE = 274,
    IF = 275,
    ELSE = 276,
    NUM = 277,
    ID = 278,
    LPAREN = 279,
    RPAREN = 280,
    LBRACKET = 281,
    RBRACKET = 282,
    LBRACE = 283,
    RBRACE = 284,
    COMMA = 285,
    DOT = 286,
    SEMI = 287,
    COMMENT = 288,
    AND = 289,
    OR = 290,
    PLUS = 291,
    MINUS = 292,
    TIMES = 293,
    MOD = 294,
    MAIN = 295,
    STRING = 296,
    LESS = 297,
    GREATER = 298,
    NOT = 299,
    ASSIGN = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 24 "src/grammatic.bizon" /* yacc.c:355  */


	CProgram* Program; // Указатель на класс-программу
	CClass* Class; // Указатель класс
	IStatement* Statement;
	IExpression* Expression;
	CType* Type;
	CField* VarDeclaration;
	CFieldList* VarDeclaratitionList;
	CArgument* Argument;
	CArgumentList* ArgumentList;
	CMethod* MethodDeclaration;
	CMethodList* MethodDeclarationList;
	CMainMethod* MainMethod;
	CMainClass* MainClass;
	CExpList* ExpressionList;
	char *string;

#line 187 "src/bison.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (CProgram** program);

#endif /* !YY_YY_SRC_BISON_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 218 "src/bison.cpp" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 14 "src/grammatic.bizon" /* yacc.c:359  */
    
int yylex (void);
void yyerror ( CProgram**, char const * );

#line 225 "src/bison.cpp" /* yacc.c:359  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   295

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  155

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   113,   113,   115,   119,   128,   138,   140,   144,   149,
     156,   162,   170,   172,   176,   180,   182,   186,   190,   192,
     194,   196,   200,   202,   206,   208,   212,   214,   216,   218,
     220,   222,   226,   228,   230,   232,   234,   236,   238,   240,
     242,   244,   246,   248,   250,   252,   254,   256,   258,   260,
     262,   264,   268,   270
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NEW", "CLASS", "EXTENDS", "THIS",
  "RETURN", "PUBLIC", "PRIVATE", "STATIC", "PRINTLN", "INT", "BOOLEAN",
  "VOID", "INT_ARRAY", "LENGTH", "TRUE", "FALSE", "WHILE", "IF", "ELSE",
  "NUM", "ID", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LBRACE",
  "RBRACE", "COMMA", "DOT", "SEMI", "COMMENT", "AND", "OR", "PLUS",
  "MINUS", "TIMES", "MOD", "MAIN", "STRING", "LESS", "GREATER", "NOT",
  "ASSIGN", "$accept", "Program", "MainClass", "MainMethod",
  "ClassDeclarationList", "Class", "MethodDeclaration",
  "MethodDeclarationList", "VarDeclaration", "VarDeclaratitionList",
  "Argument", "Type", "ArgumentList", "StatementList", "Statement",
  "Expression", "ExpressionList", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF -103

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-103)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       7,   -18,    19,    38,    28,  -103,    39,  -103,    38,    69,
       5,  -103,    70,    50,    68,     8,    78,  -103,    66,    80,
    -103,  -103,     8,    52,    72,    67,     8,    82,  -103,     8,
       8,    52,    81,    89,    99,    52,  -103,   101,   109,  -103,
    -103,  -103,    94,   117,   114,   125,   126,  -103,     8,     8,
     136,     8,   137,   141,   152,   156,  -103,  -103,   163,   165,
     155,   256,   256,   166,   178,   181,   184,     1,   256,   209,
     256,   214,   256,     6,     6,     6,     6,     6,   193,     6,
    -103,     6,   201,    -5,  -103,  -103,  -103,  -103,  -103,     6,
       6,    32,    47,    62,    91,   105,  -103,   119,   133,  -103,
     207,   211,    77,    33,   204,     6,    -1,     6,     6,     6,
       6,     6,     6,     6,     6,   256,   256,   199,  -103,   218,
     220,     6,   225,  -103,  -103,   147,  -103,   234,   226,   217,
     251,   251,    33,    33,   235,   203,  -103,   249,     6,  -103,
    -103,   161,  -103,  -103,     6,   256,   175,  -103,   189,   255,
    -103,  -103,     6,  -103,  -103
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     3,     6,     0,
       0,     7,     0,     0,     0,    15,     0,     4,     0,    20,
      19,    21,    15,    12,     0,     0,    15,     0,    16,     0,
       0,    12,     0,     0,     0,    12,    18,     0,     0,    13,
       8,    14,     0,     0,     0,     0,     0,     9,    22,    22,
       0,    22,     0,     0,     0,     0,    23,    17,     0,     0,
       0,    24,    24,     0,     0,     0,     0,     0,    24,     0,
      24,     0,    24,     0,     0,     0,     0,     0,     0,     0,
      25,     0,     0,     0,    47,    44,    45,    43,    46,     0,
       0,     0,     0,     0,     0,     0,    26,     0,     0,     5,
       0,     0,     0,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    30,     0,
       0,     0,     0,    51,    29,     0,    41,     0,    35,    36,
      32,    33,    34,    39,    37,    38,    28,     0,     0,    10,
      11,     0,    49,    40,    52,     0,     0,    48,     0,     0,
      27,    31,    52,    42,    53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -103,  -103,  -103,  -103,   273,  -103,  -103,    18,  -103,    29,
    -103,    -4,     3,   223,  -102,   -73,   131
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    13,     7,     8,    31,    32,    22,    23,
      51,    24,    53,    69,    70,   148,   149
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      91,    92,    93,    94,    95,     4,    97,   100,    98,    83,
      14,     1,    84,   136,   137,   126,   102,   103,   101,     5,
      19,    20,   127,    85,    86,    37,    38,    76,    87,    88,
      89,    21,   125,    15,   128,   129,   130,   131,   132,   133,
     134,   135,     6,   150,    52,    52,    77,    52,   141,    39,
      90,    28,    54,    43,    56,    35,     9,   104,   105,   105,
      29,    30,    10,   106,   106,   146,   107,   108,   109,   110,
     111,   112,   115,   105,   113,   114,   114,    12,   106,    17,
      16,   107,   108,   109,   110,   111,   112,   116,   105,   113,
     114,    18,    25,   106,    26,    33,   107,   108,   109,   110,
     111,   112,   123,   105,   113,   114,    27,    34,   106,    36,
      40,   107,   108,   109,   110,   111,   112,   105,   117,   113,
     114,    41,   106,    42,    44,   107,   108,   109,   110,   111,
     112,   105,    45,   113,   114,    46,   106,   118,    48,   107,
     108,   109,   110,   111,   112,   105,    47,   113,   114,    49,
     106,   119,    50,   107,   108,   109,   110,   111,   112,   105,
      57,   113,   114,    55,   106,   120,    58,   107,   108,   109,
     110,   111,   112,   105,   143,   113,   114,    59,   106,    60,
      63,   107,   108,   109,   110,   111,   112,   105,   147,   113,
     114,    61,   106,    62,    72,   107,   108,   109,   110,   111,
     112,   105,    73,   113,   114,    74,   106,   151,    75,   107,
     108,   109,   110,   111,   112,   105,    79,   113,   114,   152,
     106,    81,    96,   107,   108,   109,   110,   111,   112,   105,
      99,   113,   114,   121,   106,   122,   124,   107,   108,   109,
     110,   111,   112,   105,   138,   113,   114,   139,   106,   140,
     142,   107,   105,   109,   110,   111,   112,   106,   144,   113,
     114,   105,   109,   110,   111,   112,   106,    64,   113,   114,
     145,   109,   110,   111,   112,    65,    66,   105,   114,    67,
     153,    11,   106,   154,    68,    71,     0,     0,     0,   111,
     112,    78,     0,    80,   114,    82
};

static const yytype_int16 yycheck[] =
{
      73,    74,    75,    76,    77,    23,    79,    12,    81,     3,
       5,     4,     6,   115,   116,    16,    89,    90,    23,     0,
      12,    13,    23,    17,    18,    29,    30,    26,    22,    23,
      24,    23,   105,    28,   107,   108,   109,   110,   111,   112,
     113,   114,     4,   145,    48,    49,    45,    51,   121,    31,
      44,    22,    49,    35,    51,    26,    28,    25,    26,    26,
       8,     9,    23,    31,    31,   138,    34,    35,    36,    37,
      38,    39,    25,    26,    42,    43,    43,     8,    31,    29,
      10,    34,    35,    36,    37,    38,    39,    25,    26,    42,
      43,    23,    14,    31,    28,    23,    34,    35,    36,    37,
      38,    39,    25,    26,    42,    43,    26,    40,    31,    27,
      29,    34,    35,    36,    37,    38,    39,    26,    27,    42,
      43,    32,    31,    24,    23,    34,    35,    36,    37,    38,
      39,    26,    23,    42,    43,    41,    31,    32,    24,    34,
      35,    36,    37,    38,    39,    26,    29,    42,    43,    24,
      31,    32,    26,    34,    35,    36,    37,    38,    39,    26,
      23,    42,    43,    27,    31,    32,    25,    34,    35,    36,
      37,    38,    39,    26,    27,    42,    43,    25,    31,    23,
      25,    34,    35,    36,    37,    38,    39,    26,    27,    42,
      43,    28,    31,    28,    28,    34,    35,    36,    37,    38,
      39,    26,    24,    42,    43,    24,    31,    32,    24,    34,
      35,    36,    37,    38,    39,    26,     7,    42,    43,    30,
      31,     7,    29,    34,    35,    36,    37,    38,    39,    26,
      29,    42,    43,    26,    31,    24,    32,    34,    35,    36,
      37,    38,    39,    26,    45,    42,    43,    29,    31,    29,
      25,    34,    26,    36,    37,    38,    39,    31,    24,    42,
      43,    26,    36,    37,    38,    39,    31,    11,    42,    43,
      21,    36,    37,    38,    39,    19,    20,    26,    43,    23,
      25,     8,    31,   152,    28,    62,    -1,    -1,    -1,    38,
      39,    68,    -1,    70,    43,    72
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    47,    48,    23,     0,     4,    50,    51,    28,
      23,    50,     8,    49,     5,    28,    10,    29,    23,    12,
      13,    23,    54,    55,    57,    14,    28,    26,    55,     8,
       9,    52,    53,    23,    40,    55,    27,    57,    57,    53,
      29,    32,    24,    53,    23,    23,    41,    29,    24,    24,
      26,    56,    57,    58,    58,    27,    58,    23,    25,    25,
      23,    28,    28,    25,    11,    19,    20,    23,    28,    59,
      60,    59,    28,    24,    24,    24,    26,    45,    59,     7,
      59,     7,    59,     3,     6,    17,    18,    22,    23,    24,
      44,    61,    61,    61,    61,    61,    29,    61,    61,    29,
      12,    23,    61,    61,    25,    26,    31,    34,    35,    36,
      37,    38,    39,    42,    43,    25,    25,    27,    32,    32,
      32,    26,    24,    25,    32,    61,    16,    23,    61,    61,
      61,    61,    61,    61,    61,    61,    60,    60,    45,    29,
      29,    61,    25,    27,    24,    21,    61,    27,    61,    62,
      60,    32,    30,    25,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    48,    49,    50,    50,    51,    51,
      52,    52,    53,    53,    54,    55,    55,    56,    57,    57,
      57,    57,    58,    58,    59,    59,    60,    60,    60,    60,
      60,    60,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     5,    13,     0,     2,     6,     8,
      12,    12,     0,     2,     3,     0,     2,     2,     3,     1,
       1,     1,     0,     2,     0,     2,     3,     7,     5,     5,
       4,     7,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     6,     1,     1,     1,     1,     1,     5,     4,
       2,     3,     0,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (program, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, program); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, CProgram** program)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (program);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, CProgram** program)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, program);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, CProgram** program)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , program);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, program); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, CProgram** program)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (program);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (CProgram** program)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 113 "src/grammatic.bizon" /* yacc.c:1646  */
    { *program = (yyval.Program) = new CProgram( (yyvsp[0].MainClass), 0 ); }
#line 1525 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 115 "src/grammatic.bizon" /* yacc.c:1646  */
    { *program = (yyval.Program) = new CProgram( (yyvsp[-1].MainClass), (yyvsp[0].ClassDeclarationList) ); }
#line 1531 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 122 "src/grammatic.bizon" /* yacc.c:1646  */
    {	
		(yyval.MainClass) = new CMainClass( (yyvsp[-3].string), (yyvsp[-1].MainMethod) );
	}
#line 1539 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 132 "src/grammatic.bizon" /* yacc.c:1646  */
    {	
		(yyval.MainMethod) = new CMainMethod( 0, 0, (yyvsp[-1].Statement) );
	}
#line 1547 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 138 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.ClassDeclarationList) = nullptr; }
#line 1553 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 140 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.ClassDeclarationList) = new CClassDeclarationList( (yyvsp[-1].Class), (yyvsp[0].ClassDeclarationList) ); }
#line 1559 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 147 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Class) = new CClass( (yyvsp[-4].string), 0, (yyvsp[-2].VarDeclaratitionList), (yyvsp[-1].MethodDeclarationList) ); }
#line 1565 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 152 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Class) = new CClass( (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].VarDeclaratitionList), (yyvsp[-1].MethodDeclarationList) ); }
#line 1571 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 160 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.MethodDeclaration) = new CMethod( (yyvsp[-10].Type), (yyvsp[-9].string), (yyvsp[-7].ArgumentList), (yyvsp[-4].Statement) ); }
#line 1577 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 166 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.MethodDeclaration) = new CMethod( (yyvsp[-10].Type), (yyvsp[-9].string), (yyvsp[-7].ArgumentList), (yyvsp[-4].Statement) ); }
#line 1583 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 170 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.MethodDeclarationList) = nullptr; }
#line 1589 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 172 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.MethodDeclarationList) = CMethodList( (yyvsp[-1].MethodDeclaration), (yyvsp[0].MethodDeclarationList) ); }
#line 1595 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 176 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.VarDeclaration) = new CField( (yyvsp[-2].Type), (yyvsp[-1].string) ); }
#line 1601 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 180 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.VarDeclaratitionList) = nullptr; }
#line 1607 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 182 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.VarDeclaratitionList) = new CFieldList( (yyvsp[-1].VarDeclaration), (yyvsp[0].VarDeclaratitionList) ); }
#line 1613 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 186 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Argument) = new CArgument( (yyvsp[-1].Type), (yyvsp[0].string) ); }
#line 1619 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 190 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Type) = new CType( (yyvsp[-2].string) ); }
#line 1625 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 192 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Type) = new CType( (yyvsp[0].string) ); }
#line 1631 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 194 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Type) = new CType( (yyvsp[0].string) ); }
#line 1637 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 196 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Type) = new CType( (yyvsp[0].string) ); }
#line 1643 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 200 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.ArgumentList) = nullptr; }
#line 1649 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 202 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.ArgumentList) = CArgumentList( (yyvsp[-1].Argument), (yyvsp[0].ArgumentList) ); }
#line 1655 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 206 "src/grammatic.bizon" /* yacc.c:1646  */
    {(yyval.Statement) = nullptr; }
#line 1661 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 208 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Statement) = new CCompoundStm((yyvsp[-1].Statement), (yyvsp[0].Statement)); }
#line 1667 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 212 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Statement) = (yyvsp[-1].Statement) }
#line 1673 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 214 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Statement) = new CIfStm( (yyvsp[-4].Expression), (yyvsp[-2].Statement), (yyvsp[0].Statement) ); }
#line 1679 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 216 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Statement) = new CWhileStm( (yyvsp[-2].Expression), (yyvsp[0].Statement) ); }
#line 1685 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 218 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Statement) = new CPrintStm( (yyvsp[-2].Expression) ); }
#line 1691 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 220 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Statement) = new CAssignStm( (yyvsp[-3].string), (yyvsp[-1].Expression) ); }
#line 1697 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 222 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Statement) = new CAssignSubscriptStm( (yyvsp[-6].string), (yyvsp[-4].Expression), (yyvsp[-1].Expression) ); }
#line 1703 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 226 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new COpExpression( (yyvsp[-2].Expression), COpExpression::TOperation::PLUS, (yyvsp[0].Expression) ); }
#line 1709 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 228 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new COpExpression( (yyvsp[-2].Expression), COpExpression::TOperation::Minus, (yyvsp[0].Expression) ); }
#line 1715 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 230 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new COpExpression( (yyvsp[-2].Expression), COpExpression::TOperation::TIMES, (yyvsp[0].Expression) ); }
#line 1721 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 232 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CLogOpExp( (yyvsp[-2].Expression), TLogicalOperation::AND, (yyvsp[0].Expression) ); }
#line 1727 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 234 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CLogOpExp( (yyvsp[-2].Expression), TLogicalOperation::OR, (yyvsp[0].Expression) ); }
#line 1733 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 236 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CCompareExpression( (yyvsp[-2].Expression), CCompareExpression::LESS, (yyvsp[0].Expression) ); }
#line 1739 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 238 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CCompareExpression( (yyvsp[-2].Expression), CCompareExpression::GREATER, (yyvsp[0].Expression) ); }
#line 1745 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 240 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new COpExpression( (yyvsp[-2].Expression), COpExpression::TOperation::MOD, (yyvsp[0].Expression) ); }
#line 1751 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 242 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CByIndexExpression((CArrayExpression*) (yyvsp[-3].Expression), (yyvsp[-1].Expression)); }
#line 1757 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 244 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CGetLengthExp( (CArrayExpression*) (yyvsp[-2].Expression) ); }
#line 1763 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 246 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CCallMethodExp( (CClass*) (yyvsp[-5].Expression), (yyvsp[-3].string), (CExpList*) (yyvsp[-1].ExpressionList)) ; }
#line 1769 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 248 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CNumExpresion((yyvsp[0].string)); }
#line 1775 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 250 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CLogExp(true); }
#line 1781 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 252 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CLogExp(false); }
#line 1787 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 254 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CIdExp((yyvsp[0].string)); }
#line 1793 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 256 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CThisExpression(); }
#line 1799 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 258 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = CArrayExpression((yyvsp[-1].Expression)); }
#line 1805 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 260 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = new CIdExp((yyvsp[-2].string)); }
#line 1811 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 262 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = CNegativeExpression((yyvsp[0].Expression)); }
#line 1817 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 264 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.Expression) = (yyvsp[-1].Expression) }
#line 1823 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 268 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.ExpressionList) = nullptr; }
#line 1829 "src/bison.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 270 "src/grammatic.bizon" /* yacc.c:1646  */
    { (yyval.ExpressionList) = new CExpList((yyvsp[-2].Expression), (CExpList*) (yyvsp[0].ExpressionList)); }
#line 1835 "src/bison.cpp" /* yacc.c:1646  */
    break;


#line 1839 "src/bison.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (program, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (program, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc, program);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, program);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (program, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, program);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, program);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 272 "src/grammatic.bizon" /* yacc.c:1906  */
