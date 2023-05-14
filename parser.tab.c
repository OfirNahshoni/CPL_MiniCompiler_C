
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

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

/* Line 189 of yacc.c  */
#line 1 "parser.y"

	// Includes
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include <stdbool.h>
	#include "symbol_table.h"
	#include "my_structs.h"
	#include "mips_trans.h"

	// Global variables
	symbol_table* SymbolTable;
	char current_type;
	bool is_prog_valid = true;

	// External variables (from lex file)
	extern int line;
	extern int col;
	extern int yylex(void);
	extern FILE* yyin;
	FILE* mips_file;

	// Functions declarations
	void yyerror(const char* msg);
	


/* Line 189 of yacc.c  */
#line 102 "parser.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
     NUM = 258,
     SENTENCE = 259,
     ID = 260,
     RELOP = 261,
     PLUS = 262,
     MINUS = 263,
     MUL = 264,
     DIV = 265,
     ASSIGN = 266,
     OR = 267,
     AND = 268,
     BREAK = 269,
     CASE = 270,
     DECL = 271,
     DEFAULT = 272,
     ELSE = 273,
     END = 274,
     FINAL = 275,
     FOREACH = 276,
     IF = 277,
     IN = 278,
     INT = 279,
     OUT = 280,
     PROGRAM = 281,
     REAL = 282,
     START = 283,
     STRING = 284,
     SWITCH = 285,
     THEN = 286,
     TILL = 287,
     WHILE = 288,
     WITH = 289
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 28 "parser.y"

	Op myop;
	Val val;



/* Line 214 of yacc.c  */
#line 179 "parser.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 191 "parser.tab.c"

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
# if YYENABLE_NLS
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   164

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNRULES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,     2,     2,     2,     2,     2,
      38,    39,     2,     2,    37,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    35,    36,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,    12,    13,    18,    19,    22,    24,
      25,    31,    35,    37,    45,    46,    48,    50,    52,    55,
      56,    58,    63,    65,    67,    69,    71,    77,    83,    89,
      94,   103,   109,   110,   121,   122,   133,   135,   139,   147,
     155,   159,   160,   166,   172,   178,   184,   188,   190,   194,
     196,   201,   205,   209,   213,   215,   219,   223,   225,   229,
     231
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    -1,    26,     5,    45,    28,    46,    54,
      19,    -1,    -1,    16,    47,    48,    52,    -1,    -1,    48,
      49,    -1,    49,    -1,    -1,    53,    50,    35,    51,    36,
      -1,     5,    37,    51,    -1,     5,    -1,    20,    53,     5,
      11,     3,    36,    52,    -1,    -1,    24,    -1,    27,    -1,
      29,    -1,    54,    55,    -1,    -1,    58,    -1,     5,    11,
       4,    36,    -1,    59,    -1,    56,    -1,    57,    -1,    62,
      -1,    23,    38,     5,    39,    36,    -1,    25,    38,    69,
      39,    36,    -1,    25,    38,     4,    39,    36,    -1,     5,
      11,    69,    36,    -1,    22,    38,    66,    39,    31,    55,
      18,    55,    -1,    33,    38,    66,    39,    62,    -1,    -1,
      21,     5,    11,     3,    32,     3,    34,    65,    60,    55,
      -1,    -1,    21,     5,    11,     3,    32,     5,    34,    65,
      61,    55,    -1,    63,    -1,    40,    54,    41,    -1,    30,
      38,     5,    39,    40,    64,    41,    -1,    15,     3,    35,
      54,    14,    36,    64,    -1,    17,    35,    54,    -1,    -1,
       5,    11,     5,     7,     3,    -1,     5,    11,     5,     8,
       3,    -1,     5,    11,     5,     9,     3,    -1,     5,    11,
       5,    10,     3,    -1,    66,    12,    67,    -1,    67,    -1,
      67,    13,    68,    -1,    68,    -1,    42,    38,    68,    39,
      -1,    69,     6,    69,    -1,    69,     7,    70,    -1,    69,
       8,    70,    -1,    70,    -1,    70,     9,    71,    -1,    70,
      10,    71,    -1,    71,    -1,    38,    69,    39,    -1,     5,
      -1,     3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    55,    55,    55,    81,    81,    86,    89,    90,    93,
      93,    97,   109,   123,   145,   148,   149,   150,   153,   154,
     157,   158,   176,   177,   178,   179,   182,   202,   205,   210,
     247,   248,   249,   249,   270,   270,   300,   303,   306,   325,
     328,   329,   336,   351,   366,   381,   398,   399,   402,   403,
     406,   407,   412,   427,   435,   442,   455,   468,   475,   478,
     501
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUM", "SENTENCE", "ID", "RELOP", "PLUS",
  "MINUS", "MUL", "DIV", "ASSIGN", "OR", "AND", "BREAK", "CASE", "DECL",
  "DEFAULT", "ELSE", "END", "FINAL", "FOREACH", "IF", "IN", "INT", "OUT",
  "PROGRAM", "REAL", "START", "STRING", "SWITCH", "THEN", "TILL", "WHILE",
  "WITH", "':'", "';'", "','", "'('", "')'", "'{'", "'}'", "'!'",
  "$accept", "program", "$@1", "declarations", "$@2", "declarlist", "decl",
  "$@3", "list", "cdecl", "type", "stmtlist", "stmt", "in_stmt",
  "out_stmt", "assign_stmt", "control_stmt", "$@4", "$@5", "stmt_block",
  "_switch", "cases", "step", "bool_expr", "bool_term", "bool_factor",
  "expression", "term", "factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    58,    59,    44,    40,    41,
     123,   125,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    45,    44,    47,    46,    46,    48,    48,    50,
      49,    51,    51,    52,    52,    53,    53,    53,    54,    54,
      55,    55,    55,    55,    55,    55,    56,    57,    57,    58,
      59,    59,    60,    59,    61,    59,    59,    62,    63,    64,
      64,    64,    65,    65,    65,    65,    66,    66,    67,    67,
      68,    68,    69,    69,    69,    70,    70,    70,    71,    71,
      71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     7,     0,     4,     0,     2,     1,     0,
       5,     3,     1,     7,     0,     1,     1,     1,     2,     0,
       1,     4,     1,     1,     1,     1,     5,     5,     5,     4,
       8,     5,     0,    10,     0,    10,     1,     3,     7,     7,
       3,     0,     5,     5,     5,     5,     3,     1,     3,     1,
       4,     3,     3,     3,     1,     3,     3,     1,     3,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     6,     4,    19,     0,
       0,    15,    16,    17,    14,     8,     9,     0,     3,     0,
       0,     0,     0,     0,     0,    19,    18,    23,    24,    20,
      22,    25,    36,     0,     7,     5,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    60,     0,    59,
       0,     0,    54,    57,     0,     0,     0,    47,    49,     0,
       0,     0,     0,     0,     0,    37,     0,    12,     0,    21,
       0,     0,     0,    29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    10,
      58,    52,    53,    55,    56,     0,     0,    46,     0,    48,
      51,    26,    28,    27,    41,    31,     0,    11,     0,     0,
      50,     0,     0,     0,     0,    14,     0,     0,     0,     0,
      19,    38,    13,     0,    32,    34,    30,    19,    40,     0,
       0,     0,     0,     0,    33,    35,     0,     0,     0,     0,
       0,    41,    42,    43,    44,    45,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,     8,     9,    14,    15,    36,    68,    35,
      16,    10,    26,    27,    28,    29,    30,   130,   131,    31,
      32,   114,   124,    56,    57,    58,    59,    52,    53
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -68
static const yytype_int16 yypact[] =
{
     -14,    50,    18,   -68,   -68,    32,    58,   -68,   -68,   -18,
      21,   -68,   -68,   -68,    70,   -68,   -68,    51,   -68,    61,
      55,    60,    76,    77,    78,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -18,   -68,   -68,    54,    12,    85,    -1,
     102,    30,   112,    -1,    -2,   113,   114,   -68,    84,   -68,
      19,     0,    74,   -68,   118,    86,    13,   109,   -68,   103,
      87,    88,    41,    89,    46,   -68,   119,    92,    95,   -68,
      69,    19,    19,   -68,    19,    19,    91,    -1,    -1,    94,
      -1,    19,    97,    98,    99,   100,   101,   129,   114,   -68,
     -68,    74,    74,   -68,   -68,    24,   104,   109,    48,   -68,
      79,   -68,   -68,   -68,    15,   -68,   106,   -68,   105,   110,
     -68,   120,   133,   111,   107,   117,   140,   140,    48,   115,
     -68,   -68,   -68,   136,   -68,   -68,   -68,   -68,    48,   144,
      48,    48,    42,    96,   -68,   -68,   116,   148,   150,   151,
     152,    15,   -68,   -68,   -68,   -68,   -68
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -68,   -68,   -68,   -68,   -68,   -68,   142,   -68,    71,    43,
     124,   -25,   -39,   -68,   -68,   -68,   -68,   -68,   -68,    75,
     -68,    22,    45,   121,    82,   -67,   -36,    29,    38
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      44,    51,    47,    17,    49,    62,    11,    71,    72,    12,
      96,    13,     1,    99,    70,    47,    48,    49,     4,    19,
      20,    21,    47,    22,    49,    78,    17,   108,    23,   109,
     112,    24,   113,    47,    61,    49,    73,    50,    25,    65,
      18,    55,    19,    20,    21,   100,    22,    17,    71,    72,
      50,    23,    79,    17,    24,     3,   136,    50,    78,   111,
       6,    25,    37,    19,    20,    21,    38,    22,    50,    19,
      20,    21,    23,    22,     7,    24,    71,    72,    23,   126,
      84,    24,    25,    74,    75,    86,    71,    72,    25,    46,
      33,   134,   135,    39,    11,   128,    54,    12,    40,    13,
      91,    92,   132,   137,   138,   139,   140,    60,    90,    81,
      71,    72,    93,    94,    41,    42,    43,    63,    66,    67,
      69,    76,    80,    95,    77,    98,    82,    83,    85,    88,
      87,    89,   106,   101,   102,   103,   119,    33,   118,   116,
     104,    25,   115,   110,   117,   123,   120,   129,   121,   133,
     127,   142,   141,   143,   144,   145,    34,    45,   122,   107,
      97,   105,   125,   146,    64
};

static const yytype_uint8 yycheck[] =
{
      25,    37,     3,     5,     5,    41,    24,     7,     8,    27,
      77,    29,    26,    80,    50,     3,     4,     5,     0,    21,
      22,    23,     3,    25,     5,    12,     5,     3,    30,     5,
      15,    33,    17,     3,     4,     5,    36,    38,    40,    41,
      19,    42,    21,    22,    23,    81,    25,     5,     7,     8,
      38,    30,    39,     5,    33,     5,    14,    38,    12,    98,
      28,    40,    11,    21,    22,    23,     5,    25,    38,    21,
      22,    23,    30,    25,    16,    33,     7,     8,    30,   118,
      39,    33,    40,     9,    10,    39,     7,     8,    40,    35,
      20,   130,   131,    38,    24,   120,    11,    27,    38,    29,
      71,    72,   127,     7,     8,     9,    10,     5,    39,     6,
       7,     8,    74,    75,    38,    38,    38,     5,     5,     5,
      36,     3,    13,    32,    38,    31,    39,    39,    39,    37,
      11,    36,     3,    36,    36,    36,     3,    20,    18,    34,
      40,    40,    36,    39,    34,     5,    35,    11,    41,     5,
      35,     3,    36,     3,     3,     3,    14,    33,   115,    88,
      78,    86,   117,   141,    43
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,    44,     5,     0,    45,    28,    16,    46,    47,
      54,    24,    27,    29,    48,    49,    53,     5,    19,    21,
      22,    23,    25,    30,    33,    40,    55,    56,    57,    58,
      59,    62,    63,    20,    49,    52,    50,    11,     5,    38,
      38,    38,    38,    38,    54,    53,    35,     3,     4,     5,
      38,    69,    70,    71,    11,    42,    66,    67,    68,    69,
       5,     4,    69,     5,    66,    41,     5,     5,    51,    36,
      69,     7,     8,    36,     9,    10,     3,    38,    12,    39,
      13,     6,    39,    39,    39,    39,    39,    11,    37,    36,
      39,    70,    70,    71,    71,    32,    68,    67,    31,    68,
      69,    36,    36,    36,    40,    62,     3,    51,     3,     5,
      39,    55,    15,    17,    64,    36,    34,    34,    18,     3,
      35,    41,    52,     5,    65,    65,    55,    35,    54,    11,
      60,    61,    54,     5,    55,    55,    14,     7,     8,     9,
      10,    36,     3,     3,     3,     3,    64
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
        case 2:

/* Line 1455 of yacc.c  */
#line 55 "parser.y"
    {	
	// Create the symbol table
	SymbolTable = create_symbol_table(2);
	// Header of mips_file
	generate_mips_header(mips_file);
;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 61 "parser.y"
    { 
	if (is_prog_valid) {
		// CMD
		printf("\n--------------------------\nResult: ");
		printf("Success\n");
		print(SymbolTable);
		free_symbol_table(SymbolTable);

		// Terminate program - mips
		generate_mips_footer(mips_file);
	}
	else {
		// CMD
		printf("\n--------------------------\nResult: ");
		printf("Not Valid\n");
		free_symbol_table(SymbolTable);
	}
;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 81 "parser.y"
    { 
		generate_mips_data_section(mips_file); // .data
	;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 83 "parser.y"
    { 
			generate_mips_text_section(mips_file); // .text
		;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 93 "parser.y"
    { current_type = (yyvsp[(1) - (1)].val).type; ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 93 "parser.y"
    { // r1 
	// printf("\nr1\n");
;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 97 "parser.y"
    { // r2.1
	symbol_table_entry* tempID = lookup(SymbolTable, (yyvsp[(1) - (3)].val).sval);
	if (tempID) {
		is_prog_valid = false;
		yyerror("ID is already defined");
	}
	else {
		// printf("\nr2.1\n");
		add_attribute(SymbolTable, (yyvsp[(1) - (3)].val).sval, current_type, false, false);
		translate_declar(mips_file, current_type, (yyvsp[(1) - (3)].val).sval, "0");
	}
;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 109 "parser.y"
    { // r2.2
	symbol_table_entry* tempID = lookup(SymbolTable, (yyvsp[(1) - (1)].val).sval);
	if (tempID) {
		is_prog_valid = false;
		yyerror("ID already defined");
	}
	else {
		// printf("\nr2.2\n");
		add_attribute(SymbolTable, (yyvsp[(1) - (1)].val).sval, current_type, false, false);
		translate_declar(mips_file, current_type, (yyvsp[(1) - (1)].val).sval, "0");
	}
;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 123 "parser.y"
    {
	current_type = (yyvsp[(2) - (7)].val).type;
	symbol_table_entry* tempID = lookup(SymbolTable, (yyvsp[(3) - (7)].val).sval);
	if (tempID) {
		is_prog_valid = false;
		yyerror("ID is already defined.");
	}
	else {
		if (current_type == 's') {
			is_prog_valid = false;
			yyerror("Cannot define const string variable.");
		}
		else if ((yyvsp[(2) - (7)].val).type == 'i' && (yyvsp[(5) - (7)].val).type == 'r') {
			is_prog_valid = false;
			yyerror("Cannot assign real value to int.");
		}
		else {
			add_attribute(SymbolTable, (yyvsp[(3) - (7)].val).sval, (yyvsp[(2) - (7)].val).type, true, true);
			translate_declar(mips_file, current_type, (yyvsp[(3) - (7)].val).sval, (yyvsp[(5) - (7)].val).sval);
		}
	}
;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 148 "parser.y"
    { (yyval.val).type = 'i'; ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 149 "parser.y"
    { (yyval.val).type = 'r'; ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 150 "parser.y"
    { (yyval.val).type = 's'; ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 158 "parser.y"
    {
	symbol_table_entry* tempID = lookup(SymbolTable, (yyvsp[(1) - (4)].val).sval);
	if (tempID == NULL){
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (tempID->type != 's') {
			is_prog_valid = false;
			yyerror("String must be assigned to string type only.");
		}
		else {
			tempID->is_init = true;
			// mips
			translate_assignment(mips_file, tempID->name, (yyvsp[(3) - (4)].val).sval, false, tempID->type, NULL, false);
		}
	}
;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 182 "parser.y"
    {
	symbol_table_entry* tempID = lookup(SymbolTable, (yyvsp[(3) - (5)].val).sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("Cannot execute input method, ID is not declared.");
	}
	else {
		if (tempID->is_const) {
			is_prog_valid = false;
			yyerror("You cannot change value of const (final) variable.");
		}
		else {
			tempID->is_init = true;
			// mips - input
			translate_input(mips_file, tempID->name, tempID->type);
		}
	}
;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 202 "parser.y"
    { // int or real
	translate_output(mips_file, (yyvsp[(3) - (5)].val).sval, (yyvsp[(3) - (5)].val).type);
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 205 "parser.y"
    { // string
	translate_output(mips_file, (yyvsp[(3) - (5)].val).sval, (yyvsp[(3) - (5)].val).type);
;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 210 "parser.y"
    { // expression.type = 'i' or 'r'
	char* id_reg_name;
	char* exp_reg_name;
	symbol_table_entry* tempID = lookup(SymbolTable, (yyvsp[(1) - (4)].val).sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (tempID->is_const) {
			is_prog_valid = false;
			yyerror("Cannot assign value to const (final) variable.");
		}
		if (tempID->type != (yyvsp[(3) - (4)].val).type) { // 'i' = 'r' // 'r' == 'i' // 'r' = 's'
			if (tempID->type == 'i' || tempID->type == 's') {
				is_prog_valid = false;
				yyerror("Assign operation is not valid.");
			}
			else { // tempID-> = 'r' & expression.type = 'i' (need casting from int to float)
				tempID->is_init = true;
				// Generate reg_name
				id_reg_name = generate_reg_name(tempID->type); // 'r'
				// mips
				translate_assignment(mips_file, tempID->name, (yyvsp[(3) - (4)].val).sval, (yyvsp[(3) - (4)].val).is_num, tempID->type, id_reg_name, true);
			}
		}
		else { // (tempID->type and expression.type) = 'i' or (tempID->type and expression.type) = 'r'
			tempID->is_init = true;
			// Generate reg_name
			id_reg_name = generate_reg_name(tempID->type); // 'i' or 'r'
			// mips
			translate_assignment(mips_file, tempID->name, (yyvsp[(3) - (4)].val).sval, (yyvsp[(3) - (4)].val).is_num, tempID->type, id_reg_name, false);
		}
	}
;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 249 "parser.y"
    {
	symbol_table_entry* tempID = lookup(SymbolTable, (yyvsp[(2) - (8)].val).sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("Loop ID is not declared!");
	}
	else {
		if (tempID->is_const) {
			is_prog_valid = false;
			yyerror("Cannot assign value to const (final) variable.");
		}
		else {
			if ((yyvsp[(2) - (8)].val).type == 'i' && (yyvsp[(4) - (8)].val).type == 'r') {
				is_prog_valid = false;
				yyerror("Cannot assign real value to int.");
			}
			else
				tempID->is_init = true;
		}
	}
;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 270 "parser.y"
    {
	symbol_table_entry* tempID1 = lookup(SymbolTable, (yyvsp[(2) - (8)].val).sval);
	symbol_table_entry* tempID2 = lookup(SymbolTable, (yyvsp[(6) - (8)].val).sval);
	if (tempID1 == NULL) {
		is_prog_valid = false;
		yyerror("Loop ID is not declared!");
	}
	else if (tempID2 == NULL) {
		is_prog_valid = false;
		yyerror("Up barrier ID is not declared!");
	}
	else {
		if (tempID1->is_const) {
			is_prog_valid = false;
			yyerror("Cannot assign value to const (final) variable.");
		}
		else {
			if ((yyvsp[(2) - (8)].val).type == 'i' && (yyvsp[(4) - (8)].val).type == 'r') {
				is_prog_valid = false;
				yyerror("Cannot assign real value to int.");
			}
			else if (tempID2->is_init == false) {
				is_prog_valid = false;
				yyerror("Up barrier loop ID is not initialized.");
			}
			else
				tempID1->is_init = true;
		}
	}
;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 306 "parser.y"
    {
	symbol_table_entry* tempID = lookup(SymbolTable, (yyvsp[(3) - (7)].val).sval);
	if (tempID == NULL) {
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (tempID->is_init == false) {
			is_prog_valid = false;
			yyerror("Switch ID is not initialized.");
		}
		else if (tempID->type != current_type) {
			is_prog_valid = false;
			yyerror("Type of case ID is not the same as NUM.");
		}
	}
;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 325 "parser.y"
    {
	current_type = (yyvsp[(2) - (7)].val).type;
;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 329 "parser.y"
    {
	is_prog_valid = false;
	yyerror("default keyword is missing.");
;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 336 "parser.y"
    {
	if (strcmp((yyvsp[(1) - (5)].val).sval, (yyvsp[(3) - (5)].val).sval) != 0) { // Infinite loop
		is_prog_valid = false;
		yyerror("Danger to Infinite loop !! Step ID must match the loop variable ID.");
	}
	else {
		symbol_table_entry* tempID1 = lookup(SymbolTable, (yyvsp[(1) - (5)].val).sval);
		if (tempID1 == NULL) {
			is_prog_valid = false;
			yyerror("ID is not declared!");
		}
		else
			tempID1->is_init = true;
	}
;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 351 "parser.y"
    {
	if (strcmp((yyvsp[(1) - (5)].val).sval, (yyvsp[(3) - (5)].val).sval) != 0) { // Infinite loop
		is_prog_valid = false;
		yyerror("Danger to Infinite loop !! Step ID must match the loop variable ID.");
	}
	else {
		symbol_table_entry* tempID1 = lookup(SymbolTable, (yyvsp[(1) - (5)].val).sval);
		if (tempID1 == NULL) {
			is_prog_valid = false;
			yyerror("ID is not declared!");
		}
		else
			tempID1->is_init = true;
	}
;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 366 "parser.y"
    {
	if (strcmp((yyvsp[(1) - (5)].val).sval, (yyvsp[(3) - (5)].val).sval) != 0) { // Infinite loop
		is_prog_valid = false;
		yyerror("Danger to Infinite loop !! Step ID must match the loop variable ID.");
	}
	else {
		symbol_table_entry* tempID1 = lookup(SymbolTable, (yyvsp[(1) - (5)].val).sval);
		if (tempID1 == NULL) {
			is_prog_valid = false;
			yyerror("ID is not declared!");
		}
		else
			tempID1->is_init = true;
	}
;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 381 "parser.y"
    { // i = i / 4
	if (strcmp((yyvsp[(1) - (5)].val).sval, (yyvsp[(3) - (5)].val).sval) != 0) { // Infinite loop
		is_prog_valid = false;
		yyerror("Danger to Infinite loop !! Step ID must match the loop variable ID.");
	}
	else {
		symbol_table_entry* tempID1 = lookup(SymbolTable, (yyvsp[(1) - (5)].val).sval);
		if (tempID1 == NULL) {
			is_prog_valid = false;
			yyerror("ID is not declared!");
		}
		else
			tempID1->is_init = true;
	}
;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 412 "parser.y"
    {
	// Registers
	char* reg1_name = generate_reg_name((yyvsp[(1) - (3)].val).type); // $t0
	char* reg2_name = generate_reg_name((yyvsp[(3) - (3)].val).type); // $t1

	// Type Checking
	if ((yyvsp[(1) - (3)].val).type == 'r' || (yyvsp[(3) - (3)].val).type == 'r')
		(yyval.val).type = 'r';
	else
		(yyval.val).type = 'i';

	//

	(yyval.val).is_num = true;
;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 427 "parser.y"
    {
	if ((yyvsp[(1) - (3)].val).type == 'r' || (yyvsp[(3) - (3)].val).type == 'r')
		(yyval.val).type = 'r';
	else
		(yyval.val).type = 'i';

	(yyval.val).is_num = true;
;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 435 "parser.y"
    { 
	(yyval.val).type = (yyvsp[(1) - (1)].val).type;
	(yyval.val).sval = (yyvsp[(1) - (1)].val).sval; 
	(yyval.val).is_num = (yyvsp[(1) - (1)].val).is_num;
;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 442 "parser.y"
    {
	if ((yyvsp[(1) - (3)].val).type == 'r' || (yyvsp[(3) - (3)].val).type == 'r')
		(yyval.val).type = 'r';
	else
		if ((yyvsp[(1) - (3)].val).type == 's' || (yyvsp[(3) - (3)].val).type == 's') {
			is_prog_valid = false;
			yyerror("Cannot do arithmetic operations on strings");
		}
		else {
			(yyval.val).type = (yyvsp[(1) - (3)].val).type;
			(yyval.val).is_num = true;
		}
;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 455 "parser.y"
    {
	if ((yyvsp[(1) - (3)].val).type == 'r' || (yyvsp[(3) - (3)].val).type == 'r')
		(yyval.val).type = 'r';
	else
		if ((yyvsp[(1) - (3)].val).type == 's' || (yyvsp[(3) - (3)].val).type == 's') {
			is_prog_valid = false;
			yyerror("Cannot do arithmetic operations on strings");
		}
		else {
			(yyval.val).type = (yyvsp[(1) - (3)].val).type;
			(yyval.val).is_num = true;
		}
;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 468 "parser.y"
    {
	(yyval.val).type = (yyvsp[(1) - (1)].val).type;
	(yyval.val).sval = (yyvsp[(1) - (1)].val).sval;
	(yyval.val).is_num = (yyvsp[(1) - (1)].val).is_num;
;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 475 "parser.y"
    {
	(yyval.val).type = (yyvsp[(2) - (3)].val).type;
;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 478 "parser.y"
    {
	symbol_table_entry* tempID = lookup(SymbolTable, (yyvsp[(1) - (1)].val).sval);
	if (tempID == NULL) { // ERROR
		is_prog_valid = false;
		yyerror("ID is not declared!");
	}
	else {
		if (tempID->type == 's') { // ERROR
			is_prog_valid = false;
			yyerror("String should not used in arithmetic operations!");
		}
		else if (tempID->is_init == false) { // ERROR
			is_prog_valid = false;
			yyerror("ID is not initialized.");
		}
		else { // OK
			current_type = tempID->type;
			(yyval.val).type = current_type;
			(yyval.val).sval = (yyvsp[(1) - (1)].val).sval;
			(yyval.val).is_num = false;
		}
	}
;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 501 "parser.y"
    {
	current_type = (yyvsp[(1) - (1)].val).type; // 'r' or 'i'
	(yyval.val).type = current_type;
	(yyval.val).sval = (yyvsp[(1) - (1)].val).sval;
	(yyval.val).is_num = true;
;}
    break;



/* Line 1455 of yacc.c  */
#line 2104 "parser.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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
      if (yyn != YYPACT_NINF)
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1675 of yacc.c  */
#line 509 "parser.y"

// Main function
int main(int argc, char* argv[])
{
	yyin = fopen(argv[1], "r");
	assert(yyin);

	// Open mips file for write mode
    mips_file = fopen("mips_res.asm", "w");
    assert(mips_file);

	printf("%d) ", line++);

	do {
		yyparse();
	} while(!feof(yyin));

	fclose(yyin);
	fclose(mips_file);

	return 0;
}

/* Functions Implementations */
void yyerror(const char* msg) 
{ // Function to print the error
	fprintf(stderr, "\nError (line %d, col %d): %s\n", line-1, col, msg);
}
