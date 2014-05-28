/*
UFRGS - Compiladores B - Marcelo Johann - 2012/1 - Etapa 4

Alunos: Daniel Henrique Grehs e Victoria Ramos Pires.

Matrículas: 213998 e 213997.
*/

#ifndef ASTREE_H
#define ASTREE_H

#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

#define MAX_NODE 	   4

#define AST_ADD 	    1
#define AST_SUB  	    2
#define AST_MUL             3
#define AST_DIV             4

#define AST_KW_INTEGER      5
#define AST_KW_FLOATING     6
#define AST_KW_BOOLEAN      7
#define AST_KW_CHARACTER    8
#define AST_KW_IF           9
#define AST_KW_IF_ELSE	    10
#define AST_KW_WHILE        11
#define AST_KW_DO_WHILE	    12
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
#define AST_LIT_FLOATING    23
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

#define AST_programa	    34
#define AST_declaracao_glob 35
#define AST_declaracao	    36
#define AST_funcao	    37
#define AST_parametros	    38
#define AST_vaiParaParametros 39
#define AST_parametro	    40
#define AST_blocks          41
#define AST_bloco           42
#define AST_cmd		    43
#define AST_outp	    44
#define AST_outp2	    45
#define AST_primary_expression 46
#define AST_exprComTK_IDENTIFIER 47
#define AST_TK_IDENTIFIER_VET 48
#define AST_vet		    49
#define AST_params_func     50
#define AST_contr_fluxo	    51
#define AST_cmds	    52

typedef struct astreenode
{
	struct sHASH_NODE *symbol;
	struct astreenode *scc[MAX_NODE];
	int type;
	int impresso;
	int lineNumber;
}ASTREE; 

ASTREE *astCreate(int type, struct sHASH_NODE *symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3);
void *astPrintTree(ASTREE *root);
void *astPrintNode(ASTREE *node);
int dataTypeMap(int astType);

#endif
