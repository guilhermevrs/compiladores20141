#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define MY_PRIME_NR	997

typedef struct {
    char *text;
    int type;
    int intVal;
    double floatVal;
    char charVal;
    int boolVal;
} TOKEN_CONTENT;

typedef struct sHASH_NODE {
    TOKEN_CONTENT content;
    struct sHASH_NODE *next;
} HASH_NODE;

typedef struct {
    HASH_NODE *hashArray[MY_PRIME_NR+1];
} HASH_TABLE;

int hashInit(HASH_TABLE *table);

int hashDestroy(HASH_TABLE *table);

HASH_NODE *hashInsert(HASH_TABLE *table, int type, char *text);

void printHashTable(HASH_TABLE *table);

TOKEN_CONTENT *hashGet(HASH_TABLE *table, int type, char *text);


#endif
