/*
// UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 5
//
// Alunos: Guilherme Schwade e Guilherme Pretto.
//
// Matrículas: 192332 e 213991.
*/

#ifndef ASTREE_HEADER
#define ASTREE_HEADER

#include "hash.h"

#define MAX_SONS 4

#define ASTREE_DEF_SYMBOL			1
#define ASTREE_DEF_ADD				2
#define ASTREE_DEF_SUB				3	
#define ASTREE_DEF_DIV				4	
#define ASTREE_DEF_MUL				5	
#define ASTREE_DEF_LESS				6	
#define ASTREE_DEF_GREATER			7	
#define ASTREE_DEF_OP_LE			8	
#define ASTREE_DEF_OP_GE			9	
#define ASTREE_DEF_OP_EQ			10	
#define ASTREE_DEF_OP_NE			11	
#define ASTREE_DEF_OP_AND			12	
#define ASTREE_DEF_OP_OR			13	
#define ASTREE_DEF_IF				23	
#define ASTREE_DEF_IFELSE			25
#define ASTREE_DEF_LOOP				26
#define ASTREE_DEF_INPUT			27
#define ASTREE_DEF_OUTPUT			28
#define ASTREE_DEF_RETURN			29
#define ASTREE_DEF_VEC_ACCESS		30
#define ASTREE_DEF_FUNC_CALL		31
#define ASTREE_DEF_REF				32
#define ASTREE_DEF_DEREF			33
#define ASTREE_DEF_DECL				35	
#define ASTREE_DEF_DECL_VEC			36
#define ASTREE_DEF_DECL_VEC_INIT	37
#define ASTREE_DEF_DECL_POINTER		38
#define ASTREE_DEF_FUNC				39	
#define ASTREE_DEF_INIT_VEC			40
#define ASTREE_DEF_PARAM			41
#define ASTREE_DEF_PARAM_REF		42
#define ASTREE_DEF_COMMAND_BLOCK	43
#define ASTREE_DEF_OUT_LST			44
#define ASTREE_DEF_ATTR				45
#define ASTREE_DEF_ATTR_VEC			46
#define ASTREE_DEF_PROGRAM			47
#define ASTREE_DEF_KWWORD			48
#define ASTREE_DEF_KWBYTE			49
#define ASTREE_DEF_KWBOOL			50
#define ASTREE_DEF_PARAM_POINTER	51
#define ASTREE_DEF_BLOCK			52
#define ASTREE_DEF_SIMPLE_COMMAND	53

#define ASTREE_DEF_LIT_INTEGER		54
#define ASTREE_DEF_LIT_TRUE 		55
#define ASTREE_DEF_LIT_FALSE 		56
#define ASTREE_DEF_LIT_CHAR 		57
#define ASTREE_DEF_LIT_STRING		58
#define ASTREE_DEF_IDENTIFIER 		59

#define ASTREE_DEF_WORD				60
#define ASTREE_DEF_BYTE				61
#define ASTREE_DEF_BOOL 			62
#define ASTREE_DEF_POINTER			63

#define ASTREE_DEF_DEBUG 			1000

typedef struct astreenode
{
	int type;
	int datatype;
	int lineNumber;
	HASH_NODE * symbol;
	struct astreenode* son[MAX_SONS];
} ASTREE;

ASTREE * astCreate(int type, HASH_NODE * symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3, int lineNumber);
void astPrintSingle(ASTREE *node);
void astPrintTree(ASTREE *root, int level);
void astCompile(ASTREE *root, FILE * out);
void astSetDeclaration(ASTREE *node, int *errors);
void astSetParamDeclaration(ASTREE *node, int *errors);
void astCheckNature(ASTREE *node, int *errors);


#endif
