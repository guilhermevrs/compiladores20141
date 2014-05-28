/*
UFRGS - Compiladores B - Marcelo Johann - 2012/1 - Etapa 4

Alunos: Daniel Henrique Grehs e Victoria Ramos Pires.

Matrículas: 213998 e 213997.
*/

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "astree.h"

#define MY_PRIME_NR	997

#define SYMBOL_TK_IDENTIFIER	1
#define SYMBOL_LIT_INTEGER	2
#define SYMBOL_LIT_FLOATING	3
#define SYMBOL_LIT_TRUE		4
#define SYMBOL_LIT_FALSE	5
#define SYMBOL_LIT_CHAR		6
#define SYMBOL_LIT_STRING	7

#define SYMBOL_VARIABLE		8
#define SYMBOL_VECTOR		9
#define SYMBOL_FUNCTION		10

#define DATATYPE_KW_INTEGER	1
#define DATATYPE_KW_FLOATING	2
#define DATATYPE_KW_CHARACTER	3
#define DATATYPE_KW_BOOLEAN	4

// É usado no scanner.l nas hashInsert(SYMBOL_LIT_FLOATING, yytext);

typedef struct {
    char *text;
    int type;
    int intVal;
    double floatVal;
    char charVal;
    int boolVal;
    void *ast;
    int dataType;
    int lineNumber;
} TOKEN_CONTENT;

typedef struct sHASH_NODE {
    TOKEN_CONTENT content;
    struct sHASH_NODE *next;
} HASH_NODE;

HASH_NODE *hashTable[MY_PRIME_NR+1];

int hashInit();

int hashDestroy();

HASH_NODE *hashInsert(int type, char *text);

void printHashTable();

TOKEN_CONTENT *hashGet(int type, char *text);


#endif
