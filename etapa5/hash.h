/*
// UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 5
//
// Alunos: Guilherme Schwade e Guilherme Pretto.
//
// Matrículas: 192332 e 213991.
*/

#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE	997

#define SYMBOL_UNDEFINED	0
#define SYMBOL_LIT_INTEGER	1
#define SYMBOL_LIT_TRUE 	3
#define SYMBOL_LIT_FALSE 	4
#define SYMBOL_LIT_CHAR 	5
#define SYMBOL_LIT_STRING	6
#define SYMBOL_IDENTIFIER 	7

#define SYMBOL_VARIABLE		8
#define SYMBOL_VECTOR		9
#define SYMBOL_VECTORINIT  10
#define SYMBOL_POINTER	   11
#define SYMBOL_FUNCTION	   12

#define DATATYPE_UNDEFINED	0
#define DATATYPE_WORD		1
#define DATATYPE_BYTE		2
#define DATATYPE_BOOL		3


typedef struct hash_node
{
	char *text;
	int type;
	int datatype;
	int lineNumber;
	struct hash_node *next;
	struct astreenode *decl;
} HASH_NODE;

typedef struct hash_table
{
	int usedEntries;
	HASH_NODE *node[HASH_SIZE];
} HASH_TABLE;

void hashInit(HASH_TABLE *Table);
int hashAddress(HASH_TABLE *Table, char *text);
void hashResize(HASH_TABLE *Table);
HASH_NODE *hashInsert(HASH_TABLE *Table, char *text, int type, int lineNumber);
HASH_NODE *hashFind(HASH_TABLE *Table, char *text, int type);
void hashPrint(HASH_TABLE *Table);
void hashCheckUndeclared(HASH_TABLE *Table, int * errors);

#endif
