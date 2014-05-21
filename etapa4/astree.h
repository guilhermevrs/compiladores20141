/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#ifndef ASTREE_HEADER
#define ASTREE_HEADER

#include "hash.h"

#define MAX_SONS 4

#define ASTREE_DEF_SYMBOL      1
#define ASTREE_DEF_ADD         2
#define ASTREE_DEF_SUB         3
#define ASTREE_DEF_DIV         4
#define ASTREE_DEF_MUL         5
#define ASTREE_DEF_LESS        6
#define ASTREE_DEF_GREATER     7
#define ASTREE_DEF_OP_LE       8
#define ASTREE_DEF_OP_GE       9
#define ASTREE_DEF_OP_EQ       10
#define ASTREE_DEF_OP_NE       11
#define ASTREE_DEF_OP_AND      12
#define ASTREE_DEF_OP_OR       13
#define ASTREE_DEF_IF          23
#define ASTREE_DEF_IFELSE      25
#define ASTREE_DEF_LOOP        26
#define ASTREE_DEF_INPUT       27
#define ASTREE_DEF_OUTPUT      28
#define ASTREE_DEF_RETURN      29
#define ASTREE_DEF_VEC_ACCESS      30
#define ASTREE_DEF_FUNC_CALL       31
#define ASTREE_DEF_REF         32
#define ASTREE_DEF_DEREF       33
#define ASTREE_DEF_NEG         34
#define ASTREE_DEF_DECL        35
#define ASTREE_DEF_DECL_VEC        36
#define ASTREE_DEF_DECL_VEC_INIT   37
#define ASTREE_DEF_DECL_POINTER    38
#define ASTREE_DEF_FUNC        39
#define ASTREE_DEF_INIT_VEC        40
#define ASTREE_DEF_PARAM       41
#define ASTREE_DEF_PARAM_REF       42
#define ASTREE_DEF_COMMAND_BLOCK   43
#define ASTREE_DEF_OUT_LST     44
#define ASTREE_DEF_ATTR        45
#define ASTREE_DEF_ATTR_VEC        46
#define ASTREE_DEF_PROGRAM     47
#define ASTREE_DEF_KWWORD      48
#define ASTREE_DEF_KWBYTE      49
#define ASTREE_DEF_KWBOOL      50
#define ASTREE_DEF_PARAM_POINTER   51
#define ASTREE_DEF_BLOCK       52
#define ASTREE_DEF_SIMPLE_COMMAND  53

#define ASTREE_DEF_DEBUG 1000

typedef struct astreenode
{
    int type;
    HASH_NODE * symbol;
    int lineNumber;
    struct astreenode* son[MAX_SONS];
} ASTREE;

ASTREE * astCreate(int type, HASH_NODE * symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3);
void astPrintSingle(ASTREE *node);
void astPrintTree(ASTREE *root, int level);
void astCompile(ASTREE *root, FILE * out);
int dataTypeMap(int astType);

int astTreeCheckDeclaration(ASTREE *node);
int astTreeCheckUndeclared(HASH_TABLE *Table);

void astCheckNature(ASTREE *node,ASTREE *rootAux);
int expressionAnalyzes(ASTREE *ast, ASTREE *rootAux);
int resultOperTypesCheck(int verified, int expr1, int expr2, int lineNumber);
int operationTypesCheck(int expr1, int expr2);
void funcCallCheck(ASTREE *ast, char *text);
void varDeclAsFuncCheck(ASTREE *ast, char *text);
int paramsFuncCheck(ASTREE *ast, ASTREE *filho);


#endif
