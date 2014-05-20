/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto

Matrícula: 192332 e 213991.
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

#define DATATYPE_UNDEFINED 0
#define DATATYPE_VARIABLE 1
#define DATATYPE_VECTOR 2
#define DATATYPE_POINTER 3
#define DATATYPE_FUNCTION 4
#define DATATYPE_PARAM 5


typedef struct hash_node
{
	char *text;
             int dataType;
	int type;
	struct hash_node *next;
} HASH_NODE;

typedef struct hash_table
{
	int usedEntries;
	HASH_NODE *node[HASH_SIZE];
} HASH_TABLE;


void hashInit(HASH_TABLE *Table);
int hashAddress(HASH_TABLE *Table, char *text);
void hashResize(HASH_TABLE *Table);
HASH_NODE *hashInsert(HASH_TABLE *Table, char *text, int type);
HASH_NODE *hashFind(HASH_TABLE *Table, char *text, int type);
void hashPrint(HASH_TABLE *Table);

#endif
