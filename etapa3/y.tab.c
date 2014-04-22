/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 10 "parser.y"


#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"



/* Line 268 of yacc.c  */
#line 81 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     KW_WORD = 256,
     KW_BOOL = 258,
     KW_BYTE = 259,
     KW_IF = 261,
     KW_THEN = 262,
     KW_ELSE = 263,
     KW_LOOP = 264,
     KW_INPUT = 266,
     KW_OUTPUT = 267,
     KW_RETURN = 268,
     OPERATOR_LE = 270,
     OPERATOR_GE = 271,
     OPERATOR_EQ = 272,
     OPERATOR_NE = 273,
     OPERATOR_AND = 274,
     OPERATOR_OR = 275,
     TK_IDENTIFIER = 280,
     LIT_INTEGER = 281,
     LIT_FALSE = 283,
     LIT_TRUE = 284,
     LIT_CHAR = 285,
     LIT_STRING = 286,
     TOKEN_ERROR = 290
   };
#endif
/* Tokens.  */
#define KW_WORD 256
#define KW_BOOL 258
#define KW_BYTE 259
#define KW_IF 261
#define KW_THEN 262
#define KW_ELSE 263
#define KW_LOOP 264
#define KW_INPUT 266
#define KW_OUTPUT 267
#define KW_RETURN 268
#define OPERATOR_LE 270
#define OPERATOR_GE 271
#define OPERATOR_EQ 272
#define OPERATOR_NE 273
#define OPERATOR_AND 274
#define OPERATOR_OR 275
#define TK_IDENTIFIER 280
#define LIT_INTEGER 281
#define LIT_FALSE 283
#define LIT_TRUE 284
#define LIT_CHAR 285
#define LIT_STRING 286
#define TOKEN_ERROR 290




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 20 "parser.y"

  HASH_NODE *symbol;
  ASTREE *astree;
  int number;



/* Line 293 of yacc.c  */
#line 175 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 187 "y.tab.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   284

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNRULES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,     2,    32,     2,    33,     2,
      39,    40,    30,    28,    41,    29,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    35,    36,
      26,    44,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    43,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     3,     2,     4,     5,
       2,     6,     7,     8,     9,     2,    10,    11,    12,     2,
      13,    14,    15,    16,    17,    18,     2,     2,     2,     2,
      19,    20,     2,    21,    22,    23,    24,     2,     2,     2,
      25,     1,     2
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    15,    17,    19,
      25,    27,    29,    31,    33,    35,    44,    51,    53,    56,
      63,    71,    72,    75,    76,    80,    83,    87,    89,    91,
      95,    98,   100,   103,   105,   107,   109,   112,   115,   118,
     122,   129,   131,   135,   142,   151,   157,   159,   161,   163,
     165,   167,   172,   177,   181,   185,   189,   193,   197,   201,
     205,   209,   213,   217,   221,   225,   229,   232,   235,   238,
     239,   242,   243,   247,   249,   251,   253,   255,   257
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    47,    -1,    47,    46,    -1,    53,    -1,
      53,    46,    -1,    48,    -1,    50,    -1,    52,    -1,    66,
      65,    35,    49,    36,    -1,    20,    -1,    21,    -1,    22,
      -1,    23,    -1,    24,    -1,    66,    65,    37,    20,    38,
      35,    51,    36,    -1,    66,    65,    37,    20,    38,    36,
      -1,    49,    -1,    49,    51,    -1,    66,    32,    65,    35,
      49,    36,    -1,    66,    65,    39,    54,    40,    57,    36,
      -1,    -1,    56,    55,    -1,    -1,    41,    56,    55,    -1,
      66,    65,    -1,    66,    32,    65,    -1,    60,    -1,    58,
      -1,    42,    59,    43,    -1,    42,    43,    -1,    60,    -1,
      60,    59,    -1,    61,    -1,    63,    -1,    64,    -1,    10,
      65,    -1,    11,    62,    -1,    12,    67,    -1,    65,    44,
      67,    -1,    65,    37,    67,    38,    44,    67,    -1,    67,
      -1,    67,    41,    62,    -1,     6,    39,    67,    40,     7,
      57,    -1,     6,    39,    67,    40,     8,    57,     7,    57,
      -1,     9,    57,    39,    67,    40,    -1,    19,    -1,     3,
      -1,     5,    -1,     4,    -1,    70,    -1,    65,    37,    67,
      38,    -1,    65,    39,    68,    40,    -1,    67,    28,    67,
      -1,    67,    29,    67,    -1,    67,    31,    67,    -1,    67,
      30,    67,    -1,    67,    26,    67,    -1,    67,    27,    67,
      -1,    67,    13,    67,    -1,    67,    14,    67,    -1,    67,
      15,    67,    -1,    67,    16,    67,    -1,    67,    17,    67,
      -1,    67,    18,    67,    -1,    39,    67,    40,    -1,    34,
      67,    -1,    33,    67,    -1,    32,    67,    -1,    -1,    67,
      69,    -1,    -1,    41,    67,    69,    -1,    65,    -1,    20,
      -1,    21,    -1,    22,    -1,    23,    -1,    24,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    88,    88,    89,    90,    91,    97,    98,    99,   102,
     105,   106,   107,   108,   109,   112,   113,   116,   117,   120,
     126,   129,   130,   133,   134,   137,   138,   142,   143,   146,
     147,   150,   151,   155,   156,   157,   158,   159,   160,   163,
     164,   167,   168,   174,   175,   178,   184,   187,   188,   189,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   213,
     214,   217,   218,   221,   222,   223,   224,   225,   226
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KW_WORD", "KW_BOOL", "KW_BYTE", "KW_IF",
  "KW_THEN", "KW_ELSE", "KW_LOOP", "KW_INPUT", "KW_OUTPUT", "KW_RETURN",
  "OPERATOR_LE", "OPERATOR_GE", "OPERATOR_EQ", "OPERATOR_NE",
  "OPERATOR_AND", "OPERATOR_OR", "TK_IDENTIFIER", "LIT_INTEGER",
  "LIT_FALSE", "LIT_TRUE", "LIT_CHAR", "LIT_STRING", "TOKEN_ERROR", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'$'", "'&'", "'!'", "':'", "';'",
  "'['", "']'", "'('", "')'", "','", "'{'", "'}'", "'='", "$accept",
  "program", "decl_global", "decl", "init", "decl_vector", "init_vector",
  "decl_pointer", "function", "n_param", "n_param_2", "param", "command",
  "block", "command_block", "simple_command", "attribution", "out", "if",
  "loop", "identifier", "type", "expression", "n_param_ref",
  "n_param_ref2", "element", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   291,   292,   256,   258,   259,   261,   262,   263,   264,
     266,   267,   268,   270,   271,   272,   273,   274,   275,   280,
     281,   283,   284,   285,   286,   290,    60,    62,    43,    45,
      42,    47,    36,    38,    33,    58,    59,    91,    93,    40,
      41,    44,   123,   125,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    46,    46,    46,    47,    47,    47,    48,
      49,    49,    49,    49,    49,    50,    50,    51,    51,    52,
      53,    54,    54,    55,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    60,    60,    60,    60,    61,
      61,    62,    62,    63,    63,    64,    65,    66,    66,    66,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    68,
      68,    69,    69,    70,    70,    70,    70,    70,    70
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     1,     1,     5,
       1,     1,     1,     1,     1,     8,     6,     1,     2,     6,
       7,     0,     2,     0,     3,     2,     3,     1,     1,     3,
       2,     1,     2,     1,     1,     1,     2,     2,     2,     3,
       6,     1,     3,     6,     8,     5,     1,     1,     1,     1,
       1,     4,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     0,
       2,     0,     3,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    47,    49,    48,     0,     2,     6,     7,     8,     4,
       0,     1,     3,     5,    46,     0,     0,     0,     0,     0,
      21,     0,    10,    11,    12,    13,    14,     0,     0,     0,
      23,     0,     0,     9,     0,     0,     0,    22,     0,    25,
      19,     0,    16,     0,     0,     0,     0,     0,     0,     0,
      28,    27,    33,    34,    35,     0,    23,    26,    17,     0,
       0,     0,    36,    74,    75,    76,    77,    78,     0,     0,
       0,     0,    37,    73,    41,    50,    38,    30,     0,    31,
      20,     0,     0,    24,    18,    15,     0,     0,    68,    67,
      66,     0,     0,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,    32,     0,
      39,     0,     0,    65,     0,    71,     0,    59,    60,    61,
      62,    63,    64,    57,    58,    53,    54,    56,    55,    42,
       0,     0,     0,    45,    51,     0,    70,    52,     0,    43,
       0,    71,    40,     0,    72,    44
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    58,     7,    59,     8,     9,    29,
      37,    30,    49,    50,    78,    51,    52,    72,    53,    54,
      73,    10,    74,   116,   136,    75
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -47
static const yytype_int16 yypact[] =
{
      93,   -47,   -47,   -47,    22,    93,   -47,   -47,   -47,    93,
      -9,   -47,   -47,   -47,   -47,     8,   -22,    11,    21,    38,
      93,    21,   -47,   -47,   -47,   -47,   -47,    34,    47,    46,
      58,    -8,    65,   -47,    17,    45,    93,   -47,     8,   -47,
     -47,    21,   -47,    63,    45,     8,   206,   206,    -3,    73,
     -47,   -47,   -47,   -47,   -47,   -25,    58,   -47,    21,    74,
     206,    72,   -47,   -47,   -47,   -47,   -47,   -47,   206,   206,
     206,   206,   -47,    26,    77,   -47,   233,   -47,    69,   265,
     -47,   206,   206,   -47,   -47,   -47,   129,   206,   -47,   -47,
     -47,   148,   206,   206,   206,   206,   206,   206,   206,   206,
     206,   206,   206,   206,   206,   206,   206,   -47,   -47,   186,
     233,    29,   167,   -47,   205,   110,    75,     1,     1,     1,
       1,   239,   239,     1,     1,    37,    37,   -47,   -47,   -47,
      76,    45,    45,   -47,   -47,   206,   -47,   -47,   206,   -47,
     106,   110,   233,    45,   -47,   -47
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -47,     9,   -47,   -47,    41,   -47,    61,   -47,   -47,   -47,
      60,    94,   -43,   -47,    50,   -46,   -47,    25,   -47,   -47,
     -10,   -16,   -21,   -47,    -7,   -47
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      16,    61,    79,    43,    31,    17,    44,    45,    46,    47,
      14,    14,    81,    18,    12,    19,    14,    20,    13,    82,
      31,    39,    11,    15,    38,    55,    76,    14,    57,   102,
     103,   104,   105,    79,    55,    62,   131,   132,    55,    86,
      77,    22,    23,    24,    25,    26,    21,    88,    89,    90,
      91,    43,    41,    42,    44,    45,    46,    47,    28,    27,
     109,   110,    32,    92,    14,    93,   112,   104,   105,    55,
      33,   114,   115,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,    34,    35,    48,   139,   140,
      94,    95,    96,    97,    98,    99,     1,     2,     3,    36,
     145,    40,    60,   100,   101,   102,   103,   104,   105,    80,
      85,    87,   107,   143,   141,   137,    83,   142,   106,    84,
     138,    55,    55,    94,    95,    96,    97,    98,    99,   108,
      56,   129,     0,    55,   144,     0,   100,   101,   102,   103,
     104,   105,    94,    95,    96,    97,    98,    99,     0,     0,
       0,   135,     0,     0,     0,   100,   101,   102,   103,   104,
     105,    94,    95,    96,    97,    98,    99,     0,     0,   111,
       0,     0,     0,     0,   100,   101,   102,   103,   104,   105,
      94,    95,    96,    97,    98,    99,     0,     0,   113,     0,
       0,     0,     0,   100,   101,   102,   103,   104,   105,    94,
      95,    96,    97,    98,    99,     0,     0,   133,     0,     0,
       0,     0,   100,   101,   102,   103,   104,   105,    94,    95,
      96,    97,    98,    99,   130,    14,    63,    64,    65,    66,
      67,   100,   101,   102,   103,   104,   105,     0,    68,    69,
      70,     0,     0,   134,     0,    71,    94,    95,    96,    97,
      98,    99,    94,    95,    96,    97,     0,     0,     0,   100,
     101,   102,   103,   104,   105,   100,   101,   102,   103,   104,
     105,    43,     0,     0,    44,    45,    46,    47,     0,     0,
       0,     0,     0,     0,    14
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-47))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      10,    44,    48,     6,    20,    15,     9,    10,    11,    12,
      19,    19,    37,    35,     5,    37,    19,    39,     9,    44,
      36,    31,     0,    32,    32,    35,    47,    19,    38,    28,
      29,    30,    31,    79,    44,    45,     7,     8,    48,    60,
      43,    20,    21,    22,    23,    24,    35,    68,    69,    70,
      71,     6,    35,    36,     9,    10,    11,    12,    20,    18,
      81,    82,    21,    37,    19,    39,    87,    30,    31,    79,
      36,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,    38,    40,    42,   131,   132,
      13,    14,    15,    16,    17,    18,     3,     4,     5,    41,
     143,    36,    39,    26,    27,    28,    29,    30,    31,    36,
      36,    39,    43,     7,   135,    40,    56,   138,    41,    58,
      44,   131,   132,    13,    14,    15,    16,    17,    18,    79,
      36,   106,    -1,   143,   141,    -1,    26,    27,    28,    29,
      30,    31,    13,    14,    15,    16,    17,    18,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      31,    13,    14,    15,    16,    17,    18,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,    31,
      13,    14,    15,    16,    17,    18,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    26,    27,    28,    29,    30,    31,    13,
      14,    15,    16,    17,    18,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    31,    13,    14,
      15,    16,    17,    18,    38,    19,    20,    21,    22,    23,
      24,    26,    27,    28,    29,    30,    31,    -1,    32,    33,
      34,    -1,    -1,    38,    -1,    39,    13,    14,    15,    16,
      17,    18,    13,    14,    15,    16,    -1,    -1,    -1,    26,
      27,    28,    29,    30,    31,    26,    27,    28,    29,    30,
      31,     6,    -1,    -1,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,    46,    47,    48,    50,    52,    53,
      66,     0,    46,    46,    19,    32,    65,    65,    35,    37,
      39,    35,    20,    21,    22,    23,    24,    49,    20,    54,
      56,    66,    49,    36,    38,    40,    41,    55,    32,    65,
      36,    35,    36,     6,     9,    10,    11,    12,    42,    57,
      58,    60,    61,    63,    64,    65,    56,    65,    49,    51,
      39,    57,    65,    20,    21,    22,    23,    24,    32,    33,
      34,    39,    62,    65,    67,    70,    67,    43,    59,    60,
      36,    37,    44,    55,    51,    36,    67,    39,    67,    67,
      67,    67,    37,    39,    13,    14,    15,    16,    17,    18,
      26,    27,    28,    29,    30,    31,    41,    43,    59,    67,
      67,    40,    67,    40,    67,    67,    68,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    62,
      38,     7,     8,    40,    38,    41,    69,    40,    44,    57,
      57,    67,    67,     7,    69,    57
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 9:

/* Line 1806 of yacc.c  */
#line 102 "parser.y"
    { (yyval.astree) = astCreate(AST_decl_var,(yyvsp[(2) - (5)].astree),(yyvsp[(1) - (5)].astree),(yyvsp[(4) - (5)].astree), 0, 0);}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 105 "parser.y"
    { (yyval.astree) = astCreate(AST_LIT_INTEGER,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 106 "parser.y"
    { (yyval.astree) = astCreate(AST_LIT_FALSE,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 107 "parser.y"
    { (yyval.astree) = astCreate(AST_LIT_TRUE,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 108 "parser.y"
    { (yyval.astree) = astCreate(AST_LIT_CHAR,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 109 "parser.y"
    { (yyval.astree) = astCreate(AST_LIT_STRING,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 112 "parser.y"
    { (yyval.astree) = astCreate(AST_decl_vetch,(yyvsp[(2) - (8)].astree),(yyvsp[(1) - (8)].astree),(yyvsp[(4) - (8)].symbol), (yyvsp[(7) - (8)].astree), 0);}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 113 "parser.y"
    { (yyval.astree) = astCreate(AST_decl_vet,(yyvsp[(2) - (6)].astree),(yyvsp[(1) - (6)].astree),(yyvsp[(4) - (6)].symbol), 0, 0);}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 120 "parser.y"
    { (yyval.astree) = astCreate(AST_decl_pointer,(yyvsp[(3) - (6)].astree),(yyvsp[(1) - (6)].astree),(yyvsp[(5) - (6)].astree), 0, 0);}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 146 "parser.y"
    {(yyval.astree) = astCreate(AST_bloco, 0, (yyvsp[(2) - (3)].astree), 0, 0, 0);}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 158 "parser.y"
    {(yyval.astree) = astCreate(AST_KW_INPUT, (yyvsp[(2) - (2)].astree), 0, 0, 0, 0);}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 159 "parser.y"
    {(yyval.astree) = astCreate(AST_KW_OUTPUT,0, (yyvsp[(2) - (2)].astree), 0, 0, 0);}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 160 "parser.y"
    {(yyval.astree) = astCreate(AST_KW_RETURN,0, (yyvsp[(2) - (2)].astree), 0, 0, 0);}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 163 "parser.y"
    {(yyval.astree) = astCreate(AST_ATRIB_CONST, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0, 0);}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 164 "parser.y"
    {(yyval.astree) = astCreate(AST_ATRIB_VET, (yyvsp[(1) - (6)].astree), (yyvsp[(3) - (6)].astree), (yyvsp[(6) - (6)].astree), 0, 0);}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 167 "parser.y"
    {(yyval.astree) = astCreate(AST_outp,0, (yyvsp[(1) - (1)].astree), 0, 0, 0);}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 168 "parser.y"
    {(yyval.astree) = astCreate(AST_outp2,0, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0);}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 174 "parser.y"
    { (yyval.astree) = astCreate(AST_KW_IF, 0, (yyvsp[(3) - (6)].astree),(yyvsp[(6) - (6)].astree), 0, 0);}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 175 "parser.y"
    { (yyval.astree) = astCreate(AST_KW_IF_ELSE, 0, (yyvsp[(3) - (8)].astree),(yyvsp[(6) - (8)].astree),(yyvsp[(8) - (8)].astree), 0);}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 178 "parser.y"
    { (yyval.astree) = astCreate(AST_KW_LOOP, 0, (yyvsp[(2) - (5)].astree),(yyvsp[(4) - (5)].astree), 0, 0);}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 184 "parser.y"
    { (yyval.astree) = astCreate(AST_TK_IDENTIFIER,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 187 "parser.y"
    { (yyval.astree) = astCreate(AST_KW_WORD, 0, 0, 0, 0, 0);}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 188 "parser.y"
    { (yyval.astree) = astCreate(AST_KW_BYTE, 0, 0, 0, 0, 0);}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 189 "parser.y"
    { (yyval.astree) = astCreate(AST_KW_BOOL, 0, 0, 0, 0, 0);}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 193 "parser.y"
    { (yyval.astree) = astCreate(AST_exprComChavesTK_IDENTIFIER,(yyvsp[(1) - (4)].astree), (yyvsp[(3) - (4)].astree), 0, 0, 0);}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 194 "parser.y"
    { (yyval.astree) = astCreate(AST_exprComParFuncTK_IDENTIFIER,(yyvsp[(1) - (4)].astree), (yyvsp[(3) - (4)].astree), 0, 0, 0);}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 195 "parser.y"
    { (yyval.astree) = astCreate(AST_ADD, 0, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0,);}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 196 "parser.y"
    { (yyval.astree) = astCreate(AST_SUB, 0, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0,);}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 197 "parser.y"
    { (yyval.astree) = astCreate(AST_DIV, 0, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0,);}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 198 "parser.y"
    { (yyval.astree) = astCreate(AST_MUL, 0, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0,);}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 199 "parser.y"
    { (yyval.astree) = astCreate(AST_MENOR, 0, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0,);}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 200 "parser.y"
    { (yyval.astree) = astCreate(AST_MAIOR, 0, (yyvsp[(1) - (3)].astree), (yyvsp[(3) - (3)].astree), 0, 0,);}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 201 "parser.y"
    { (yyval.astree) = astCreate(AST_OPERATOR_LE, 0, (yyvsp[(1) - (3)].astree),(yyvsp[(3) - (3)].astree), 0, 0);}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 202 "parser.y"
    { (yyval.astree) = astCreate(AST_OPERATOR_GE, 0, (yyvsp[(1) - (3)].astree),(yyvsp[(3) - (3)].astree), 0, 0);}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 203 "parser.y"
    { (yyval.astree) = astCreate(AST_OPERATOR_EQ, 0, (yyvsp[(1) - (3)].astree),(yyvsp[(3) - (3)].astree), 0, 0);}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 204 "parser.y"
    { (yyval.astree) = astCreate(AST_OPERATOR_NE, 0, (yyvsp[(1) - (3)].astree),(yyvsp[(3) - (3)].astree), 0, 0);}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 205 "parser.y"
    { (yyval.astree) = astCreate(AST_OPERATOR_AND, 0, (yyvsp[(1) - (3)].astree),(yyvsp[(3) - (3)].astree), 0, 0);}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 206 "parser.y"
    { (yyval.astree) = astCreate(AST_OPERATOR_OR, 0, (yyvsp[(1) - (3)].astree),(yyvsp[(3) - (3)].astree), 0, 0);}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 207 "parser.y"
    { (yyval.astree) = astCreate(AST_exprComParent, 0, (yyvsp[(2) - (3)].astree), 0, 0, 0);}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 208 "parser.y"
    {(yyval.astree)=0;}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 209 "parser.y"
    {(yyval.astree)=0;}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 210 "parser.y"
    {(yyval.astree)=0;}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 222 "parser.y"
    { (yyval.astree) = astCreate(AST_LIT_INTEGER,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 223 "parser.y"
    { (yyval.astree) = astCreate(AST_LIT_FALSE,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 224 "parser.y"
    { (yyval.astree) = astCreate(AST_LIT_TRUE,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 225 "parser.y"
    { (yyval.astree) = astCreate(AST_LIT_CHAR,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 226 "parser.y"
    { (yyval.astree) = astCreate(AST_LIT_STRING,(yyvsp[(1) - (1)].symbol), 0, 0, 0, 0);}
    break;



/* Line 1806 of yacc.c  */
#line 1898 "y.tab.c"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 229 "parser.y"


int yyerror (char *s)
{
	fprintf(stderr, "Error in line %d: %s.\n", getLineNumber(), s);
	exit(3);
}

