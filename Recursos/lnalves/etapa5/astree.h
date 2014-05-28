#ifndef ASTREE_H
#define ASTREE_H

#include "hash.h"
#include <stdio.h>

#define SYMBOL_IDENTIFIER 1


#define MAX_SONS 4
#define ASTREE_SYMBOL 1
//#define ASTREE_LIT_INT 2
#define ASTREE_SOMA 3
#define ASTREE_SUB 4
#define ASTREE_MULT 5
#define ASTREE_DIV 6
#define ASTREE_SCALAR_ASS 7
#define ASTREE_CMDL 8
#define ASTREE_GLIST 9
#define ASTREE_VARDEC 10
#define ASTREE_VETDEC 11
#define ASTREE_PARAM 12
#define ASTREE_WORD 13
#define ASTREE_BYTE 14
#define ASTREE_BOOL 15
#define ASTREE_FUNDEC 16
#define ASTREE_KW_INPUT 17
#define ASTREE_KW_OUTPUT 18
#define ASTREE_KW_RETURN 19
#define ASTREE_IF 20
#define ASTREE_IFELSE 21
#define ASTREE_LOOP 22

#define ASTREE_LE 23
#define ASTREE_GE 24
#define ASTREE_EQ 25
#define ASTREE_NE 26
#define ASTREE_AND 27
#define ASTREE_OR 28
#define ASTREE_LESS 29
#define ASTREE_GREAT 30


#define ASTREE_VETOR 32
#define ASTREE_DEREFVET 33
#define ASTREE_REFVET 34
#define ASTREE_FUNC 35
#define ASTREE_EXPRESSION 36

#define ASTREE_VETOR_ASS 37

#define ASTREE_OUTPUT 38
#define ASTREE_OUTPUT2 39
//////
#define ASTREE_BLOCO 40
#define ASTREE_DECLOC 41
#define ASTREE_INITVET 42
#define ASTREE_INITVET2 43
#define ASTREE_CTRLBLOCO 44
#define ASTREE_VETDEC2 45
#define ASTREE_VETDEC3 46
#define ASTREE_VETDEC4 47
#define ASTREE_PARAM2 48
#define ASTREE_PARAMFUNC 49
#define ASTREE_PARAMFUNC2 50
#define ASTREE_VAR 51

typedef struct ASTREE
	{
	int type;
	int valor;
	int impresso;
	int lineNumber;
	HASH_CELL* symbol;
	struct ASTREE *son[MAX_SONS];
	
	}ASTREE;
	
	
ASTREE *astreeCreate( int type, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3, HASH_CELL *n );

void astreesPrintSingle (ASTREE *node);
void astreePrintTree (ASTREE *node, int level);

FILE* outputfile;

#endif
