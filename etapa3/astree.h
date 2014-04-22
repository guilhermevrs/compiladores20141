/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#ifndef ASTREE_READER
#define ASTREE_READER

#define MAX_SONS 4

#define AST_ADD    	    1
#define AST_SUB             2
#define AST_MUL             3
#define AST_DIV       	    4

#define AST_KW_WORD         5
#define AST_KW_BOOL         7
#define AST_KW_BYTE         8
#define AST_KW_IF           9
#define AST_KW_IF_ELSE	    10
#define AST_KW_LOOP         11
#define AST_KW_INPUT        13
#define AST_KW_OUTPUT       14
#define AST_KW_RETURN       15

#define AST_OPERATOR_LE     16
#define AST_OPERATOR_GE     17
#define AST_OPERATOR_EQ     18
#define AST_OPERATOR_NE     19
#define AST_OPERATOR_AND    20
#define AST_OPERATOR_OR     21

#define AST_LIT_INTEGER     22
#define AST_LIT_TRUE        24
#define AST_LIT_FALSE       25
#define AST_LIT_CHAR        26
#define AST_LIT_STRING      27
#define AST_TK_IDENTIFIER   28

#define AST_IGUAL	    29
#define AST_MAIOR	    30
#define AST_MENOR   	    31
#define AST_NEG		    32 // !
#define AST_exprComParent   33

#define AST_bloco           42
#define AST_outp    	    44
#define AST_outp2    	    44


#define AST_ATRIB_CONST     60
#define AST_ATRIB_VET       61
#define AST_exprComChavesTK_IDENTIFIER 62
#define AST_exprComParFuncTK_IDENTIFIER 63

#define AST_decl_var	    67
#define AST_decl_vetch      68
#define AST_decl_vet	    69
#define AST_decl_pointer    70

#define AST_SYMBOL 71

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

typedef struct astreenode
{
  int type;
  HASH_NODE *symbol;
  struct astreenode* son[MAX_SONS];
  int impresso;
}ASTREE;

ASTREE *astCreate(int type, HASH_NODE *symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3);
void asPrintTree(ASTREE *root, int level);
void asPrintSingle(ASTREE *node);


#endif
