#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash_table.h"
#include "y.tab.h"

void removeBarra(char* str)
{
	int len,i,j;
	bool found = false;
	len = strlen(str);
	for (i = 0; i < len; ++i)
	{
		if (found){
			if ((str[i] == '\\') || (str[i] == '\"')) 
				for(j = i-1; j < len; ++j)
					str[j] = str[j+1];
			found = false;
		}
					
		else
			if(str[i] == '\\')
				found = true;
	}

}

void createTokenContent(TOKEN_CONTENT *content, int type, char *text) {
    int len;

    len = strlen(text);
    
    if (type != LIT_CHAR && type != LIT_STRING) {
        content->text = malloc(len + 1);
        strcpy(content->text, text);
    } else {
        content->text = malloc(len - 2 + 1);
        strncpy(content->text , text + 1, len - 2);
	removeBarra(content->text);
    }
    content->type = type;
    
    content->intVal = 0;
    content->floatVal = 0.0;
    content->charVal = ' ';
    content->boolVal = 0;
    
    switch (type) {
        case LIT_INTEGER:
            content->intVal = atoi(text);
            break;
        case LIT_FLOATING:
            content->floatVal = atof(text);
            //content->floatVal = 999;
            break;
        case LIT_CHAR:
            content->charVal = text[1];
            break;
        case LIT_TRUE:
            content->boolVal = 1;
            break;
        case LIT_FALSE:
            content->boolVal = 0;
            break;
        default:
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
    HASH_NODE *n;
    
    for (n = node; n != NULL; n->next) {
        if (n->content.type == type && strcmp(text, n->content.text) == 0)
            break;
    }
    return n;
}  

int hashInit(HASH_TABLE *table) {
    int i;
    for (i = 0; i < MY_PRIME_NR+1; i++)
        table->hashArray[i] = NULL;
        
    return 0;
}

int hashDestroy(HASH_TABLE *table) {
    int i;
    HASH_NODE *node;
    
    for (i = 0; i < MY_PRIME_NR+1; i++) {
        for (node = table->hashArray[i]; node != NULL; node = node->next) {
            destroyTokenContent(&node->content);
            free(node);
        }
        table->hashArray[i] = NULL;
    }
        
    return 0;
}

HASH_NODE *hashInsert(HASH_TABLE *table, int type, char *text) {
    int address;
    HASH_NODE *node, *newNode, *existingNode;
    
    address = getHashCode(text);
    node = table->hashArray[address];
    existingNode = findNode(node, type, text);

    if (existingNode != NULL) {
        return existingNode;
    }

    newNode = malloc(sizeof(HASH_NODE));
    createTokenContent(&newNode->content, type, text);
    newNode->next = node;
    table->hashArray[address] = newNode;
    
    return ;    
}

TOKEN_CONTENT *hashGet(HASH_TABLE *table, int type, char *text) {
    int address;
    HASH_NODE *node;
    
    address = getHashCode(text);
    
    node = findNode(table->hashArray[address], type, text);
    
    if (node != NULL) {
        return &node->content;
    }    
    return NULL;
}

void printHashTable(HASH_TABLE *table) {
    int i;
    HASH_NODE *node;
    
    for (i = 0; i < MY_PRIME_NR+1; i++) {
        for (node = table->hashArray[i]; node != NULL; node = node->next) {
            printf("tipo %d texto %s ", node->content.type, node->content.text);
            printf("int %d ", node->content.intVal);
            printf("float %f ", node->content.floatVal);
            printf("char %c ", node->content.charVal);
            printf("bool %d\n", node->content.boolVal);
        }
    }        
}
