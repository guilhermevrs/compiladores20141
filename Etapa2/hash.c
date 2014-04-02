/*
UFRGS - Compiladores B - Marcelo Johann - 2013/1 - Etapa 2

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrícula: 192332 e 213991.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"
#include "y.tab.h"

HASH_NODE *Table[HASH_SIZE];

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

void hash_init(void)
{
    int i;
    for(i=0;i<HASH_SIZE;i++)
        Table[i] = 0;
}

int hash_address(char* text)
{
    int address = 1;
    int i;

    for(i=0;i<strlen(text);++i)
        address = ((address*text[i])%HASH_SIZE)+1;
		
    return address-1;
}

HASH_NODE *hash_find(char *text)
{
	HASH_NODE *node;
	int address = hash_address(text);
	for(node = Table[address]; node != 0; node = node->next)
		if(!strcmp(text,node->text))
			return node;
	return 0;		
}

HASH_NODE *hash_insert(char *text, int type)
{
	HASH_NODE *node;
	int address = 0;
	int len;
	
	len = strlen(text);

	if(node = hash_find(text))
		return node;
		
	address = hash_address(text);
	node = (HASH_NODE*) calloc (1,sizeof(HASH_NODE));
	if (type != LIT_CHAR && type != LIT_STRING)
	{
        node->text = malloc(len + 1);
        strcpy(node->text, text);
    	}
	else
	{
        node->text = malloc(len - 2 + 1);
        strncpy(node->text , text + 1, len - 2);
		removeBarra(node->text);
	}
    	node->type = type;
    
    	node->intVal = 0;
    	node->charVal = ' ';
    	node->boolVal = 0;
    
	switch (type) 
	{
		case LIT_INTEGER:
			node->intVal = atoi(text);
			break;
		case LIT_CHAR:
		    node->charVal = text[1];
		    break;
		case LIT_TRUE:
		    node->boolVal = 1;
		    break;
		case LIT_FALSE:
		    node->boolVal = 0;
		    break;
		default:
		    break;
	}
	
	node->next = Table[address];
	Table[address] = node;
	
	return node;
	
}

void hash_print(void)
{
	int i;
	HASH_NODE *node;


	for(i=0;i< HASH_SIZE;i++)
	{
		for(node = Table[i]; node; node = node->next)
			{{
			printf("tipo %d texto %s ", node->type, node->text);
            		printf("int %d ", node->intVal);
            		printf("char %c ", node->charVal);
            		printf("bool %d\n", node->boolVal);
			}}		
	}

}
