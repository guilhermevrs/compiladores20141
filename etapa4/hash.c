/*
UFRGS - Compiladores B - Marcelo Johann - 2013/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrícula: 192332 e 213991.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "astree.h"
#include "hash.h"

static int hash_i = 1;

void hashInit (HASH_TABLE *Table)
{
	int i;

	for (i = 0; i < hash_i*HASH_SIZE; ++i)
	{
		Table -> node[i] = 0;
	}
	Table -> usedEntries = 0;
}

int hashAddress (HASH_TABLE *Table, char *text)
{
	int address;
	int i;

	address = 1;
	for (i = 0; i < strlen(text); ++i)
	{
		address = (address * text[i]) % (hash_i*HASH_SIZE + 1);
	}
	return address - 1;
}

void hashResize(HASH_TABLE *Table)
{
	int i;
	hash_i = hash_i*2;
	for(i = HASH_SIZE; i<hash_i*HASH_SIZE; ++i)
	{
		Table -> node[i] = 0;
	}
}

HASH_NODE *hashInsert (HASH_TABLE *Table, char *text, int type)
{
	HASH_NODE *node;
	int address;

	if (Table->usedEntries > hash_i*HASH_SIZE/2)
	{
		hashResize(Table);
	}

	address = 0;
	node  = hashFind(Table, text, type);

	if (node == 0)
	{
		address = hashAddress(Table, text);
		HASH_NODE *newNode;
		newNode = (HASH_NODE*)calloc(1, sizeof(HASH_NODE));
		newNode -> type = type;
                          newNode -> lineNumber = getLineNumber();
                          newNode -> dataType = DATATYPE_UNDEFINED;
		newNode -> text = (char*)calloc(sizeof(strlen(text)+1), sizeof(strlen(text)+1));
		strcpy(newNode -> text, text);
		newNode -> next = Table -> node[address];
		Table -> node[address] = newNode;

		Table -> usedEntries++;
		return newNode;
	}
	else
	{
		return node;
	}

}

HASH_NODE *hashFind (HASH_TABLE *Table, char *text, int type)
{
	int address;
	int i;
	HASH_NODE *pt;

	address = hashAddress(Table, text);

	for (i = 0; i < hash_i*HASH_SIZE; ++i)
	{
		for (pt = Table -> node[i]; pt; pt = pt -> next)
		{
			if (!strcmp(pt -> text, text)){
				return pt;
			}
		}
	}

	return 0;
}

void hashPrint (HASH_TABLE *Table)
{
	int i;
	HASH_NODE *pt;

	printf("\n");
	for (i = 0; i < hash_i*HASH_SIZE; ++i)
	{
		for (pt = Table -> node[i]; pt; pt = pt -> next)
		{
			printf("Token[%d]: %s \n", i, pt -> text);
		}
	}
	printf("Table has %d entries\n", Table->usedEntries);
}

