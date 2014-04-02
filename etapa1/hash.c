/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 1

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

#define HASH_SIZE 997

HASH_NODE *Table[HASH_SIZE];

void hash_init(void)
{
    int i;
    for(i=0;i<HASH_SIZE;i++)
        Table[i] = 0;
}

int hash_address(char* text)
{
    int address = 0;
    int i;

    for(i=0;i<strlen(text);++i)
        address = (address*text[i])%HASH_SIZE+1;

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

HASH_NODE *hash_insert(char *text, int token)
{
	HASH_NODE *node = 0;
	int address = 0;

	if(node = hash_find(text))
		return node;

	address = hash_address(text);
	node = (HASH_NODE*) calloc (1,sizeof(HASH_NODE));
	node->token = token;
	node->text = (char*) calloc (strlen(text)+1, sizeof(char));

	strcpy(node->text,text);

	node->next = Table[address];
	Table[address] = node;

	return node;

}

void hash_print(void)
{
	int i = 0;
	HASH_NODE *node;

	node = Table[0];

	while(i != HASH_SIZE)
	{
		for(node = Table[i]; node != 0; node = node->next)
			printf("[%d]: Token: %d - Text: %s \n", i, node->token, node->text);

		i++;

	}

}
