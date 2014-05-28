#ifndef HASH_H
#define HASH_H
/*
Lucas Neubert Alves - 194917

Vinícius Garcez Schaurich - 194915

Compiladores - Etapa2

*/

#define SYMBOL_IDENTIFIER 1
#define SYMBOL_VARIABLE 2
#define SYMBOL_VECTOR 3
#define SYMBOL_FUNCTION 4
#define SYMBOL_PARAM 5
#define SYMBOL_POINTER 6

#define SYMBOL_LABEL 7

#define HASH_TABLE_SIZE 3331

typedef struct HASH_CELL{
    char *lexem;
    int type;
    int dataType;
    struct ASTREE *funcParam;
    struct 	HASH_CELL *next;
} HASH_CELL;


typedef struct {
    HASH_CELL *hashlist[HASH_TABLE_SIZE+1];
} HASH_TABLE;


int hashInit(HASH_TABLE *htable);
int hashAddress(char *content);
HASH_CELL *hashInsert(HASH_TABLE *htable, int type, char *content);
HASH_CELL *hashSeek(HASH_TABLE *htable, int type, char *content);
void hashPrint(HASH_TABLE *htable);


HASH_CELL *makeTemp();

HASH_CELL *makeLabel();

HASH_TABLE hashtable;

#endif



