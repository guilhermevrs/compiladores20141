/*
UFRGS - Compiladores B - Marcelo Johann - 2012/1 - Etapa 4

Alunos: Daniel Henrique Grehs e Victoria Ramos Pires.

Matrículas: 213998 e 213997.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash_table.h"
#include "astree.h"
#include "y.tab.h"

void removeBarra(char* str)
{
    char* p = str, *q;
    for(; *p && *(p + 1); ++p)
      if(*p == '\\' && (*(p + 1) == '\"' || *(p + 1) == '\\'))
         for(q = p; *q; ++q)
            *q = *(q + 1);
}

void createTokenContent(TOKEN_CONTENT *content, int type, char *text) {
    int len = strlen(text);
    
    if (type != SYMBOL_LIT_CHAR && type != SYMBOL_LIT_STRING) {
        content->text = (char*) malloc(len + 1);
        strcpy(content->text, text);
    } else {
        content->text = (char*) malloc(len + 1);
        strncpy(content->text, text + 1, len - 2);
	    removeBarra(content->text);
    }

    content->type = type;
    content->intVal = 0;
    content->floatVal = 0.0;
    content->charVal = '\0';
    content->boolVal = 0;
    content->dataType  = 0;
    content->ast = 0;
    content->lineNumber = getLineNumber();
    
    switch (type) {
        case SYMBOL_LIT_INTEGER:
            content->intVal = atoi(text);
            break;
        case SYMBOL_LIT_FLOATING:
            content->floatVal = atof(text);
            break;
        case SYMBOL_LIT_CHAR:
            content->charVal = text[1];
            break;
        case SYMBOL_LIT_TRUE:
            content->boolVal = 1;
            break;
        case SYMBOL_LIT_FALSE:
            content->boolVal = 0;
            break;
    }
}

void destroyTokenContent(TOKEN_CONTENT *content) {
    if (content->text != NULL)
        free(content->text);
}

int getHashCode(char *text) {
    int address = 1;
    int i;
    
    for (i = 0; text[i] != '\0'; i++) {
        address = (address * text[i]) % MY_PRIME_NR +  1;
    }
    return address;
    
}

HASH_NODE *findNode(HASH_NODE *node, int type, char *text) {
    HASH_NODE *n = NULL;

    for (n = node; n != NULL; n->next) {
        if (n->content.type == type && strcmp(text, n->content.text) == 0) 
            return n;
    }
    return n;

}  

int hashInit() {
    int i;
    for (i = 0; i < MY_PRIME_NR+1; i++)
        hashTable[i] = NULL;
    return 0;
}

int hashDestroy() {
    int i;
    HASH_NODE *node;
    
    for (i = 0; i < MY_PRIME_NR+1; i++) {
        for (node = hashTable[i]; node != NULL; node = node->next) {
            destroyTokenContent(&node->content);
            free(node);
        }
        hashTable[i] = NULL;
    }
        
    return 0;
}

HASH_NODE *hashInsert(int type, char *text) {
    int address;
    HASH_NODE *node, *newNode, *existingNode;
    
    address = getHashCode(text);
    node = hashTable[address];

    existingNode = findNode(node, type, text);

    //printf("\n\n Node: %s com o tipo %d\n\n",)
    if (existingNode != NULL)
        return existingNode;

    newNode = malloc(sizeof(HASH_NODE));
    createTokenContent(&(newNode->content), type, text);
    newNode->next = node;
    hashTable[address] = newNode;
    return newNode;
}

TOKEN_CONTENT *hashGet(int type, char *text) {
    int address;
    HASH_NODE *node;
    
    address = getHashCode(text);
    
    node = findNode(hashTable[address], type, text);
    
    if (node != NULL) {
        return &(node->content);
    }    
    return NULL;
}

void printHashTable() {
    int i;
    HASH_NODE *node;
    
    for (i = 0; i < MY_PRIME_NR+1; i++) {
        for (node = hashTable[i]; node != NULL; node = node->next) {
            printf("tipo %d texto %s ", node->content.type, node->content.text);
            printf("int %d ", node->content.intVal);
            printf("float %f ", node->content.floatVal);
            printf("char %c ", node->content.charVal);
            printf("bool %d\n", node->content.boolVal);
        }
    }        
}
