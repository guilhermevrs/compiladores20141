/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#ifndef ASTREE_READER
#define ASTREE_READER

#include "hash.h"

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD 2

typedef struct astreenode
{
  int type;
  HASH_NODE *symbol;	
  struct astreenode* son[MAX_SONS];

}ASTREE;

ASTREE * astCreate(int type, ASTREE *s0, ASTREE *S1, ASTREE *S2, ASTREE *S3);
void asPrintSingle(ASTREE *node);
void asPrintTree(ASTREE *root, int level);

#endif
