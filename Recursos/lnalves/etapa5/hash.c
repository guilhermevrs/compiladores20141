
/*
Lucas Neubert Alves - 194917

Vinícius Garcez Schaurich - 194915

Compiladores - Etapa2

*/

#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include "hash.h"
#include "astree.h"
#include "y.tab.h"

int hashInit(HASH_TABLE *htable){
	int i;
	for(i=0 ; i<HASH_TABLE_SIZE+1 ; i++)
		htable->hashlist[i]=NULL;
	return 0;
}

int hashAddress(char *content)
{
	int address;
	int number, i;
	number = 0;
	for (i = 0; content[i] != '\0'; i++)
		number += content[i];
	address = (number % HASH_TABLE_SIZE) + 1;	//calculo do endereço da hash
	return address;
}

HASH_CELL *hashInsert(HASH_TABLE *htable, int type, char *content)
{
	HASH_CELL *actual, *new;
	int addr;
	
	
	new = hashSeek(htable,type,content);
	if(new !=NULL)
		return new;	//nodo encontrado
	

	addr = hashAddress(content);
	actual = htable->hashlist[addr];
	new = (HASH_CELL*)malloc(sizeof(HASH_CELL));
	new->type = type;
	new->lexem = malloc(strlen(content)+2);
	strcpy(new->lexem,content);
	new->next = actual;
	htable->hashlist[addr] = new;
	
	return new;
}

HASH_CELL *hashSeek(HASH_TABLE *htable, int type, char *content)
{
	HASH_CELL *hcell;
	int addr, finded=0;;
	
	addr = hashAddress(content);
	hcell = htable->hashlist[addr];
	while((finded==0) && hcell!=NULL)
	{
		if(hcell->type==type && (strcmp(hcell->lexem,content)==0))
			finded=1;
		else
			hcell=hcell->next;
	}
	
	if(finded==1)
		return hcell;
	else
		return NULL;	
}

void hashPrint(HASH_TABLE *htable)
{
	int i;
	HASH_CELL *actual;

	for(i=0 ; i < HASH_TABLE_SIZE+1 ; i++)
	{
		for(actual = htable->hashlist[i] ; actual != NULL ; actual = actual->next)
		{
			switch(actual->type)
			{
				case LIT_INTEGER: 	printf("POS[%d] - Tipo: INT Valor: %s \n",i , actual->lexem);
									break;
				case LIT_CHAR:		printf("POS[%d] - Tipo: CHAR Valor: %s \n",i , actual->lexem);
									break;
				case LIT_STRING:	printf("POS[%d] - Tipo: STRING Valor: %s \n",i , actual->lexem);
									break;
				case LIT_FALSE:		printf("POS[%d] - Tipo: FALSE Valor: %s \n",i , actual->lexem);
									break;
				case LIT_TRUE:		printf("POS[%d] - Tipo: TRUE Valor: %s \n",i , actual->lexem);
									break;
				default:			printf("POS[%d] - Identifier: %s \n",i , actual->lexem);
									break;
			}
		}
	}
}



HASH_CELL *makeTemp()
{
	static int nextTemp = 0;
	char buffer[128];

	sprintf(buffer, "__Temp%d", nextTemp);
	nextTemp++;

	return hashInsert(&hashtable, SYMBOL_VARIABLE, buffer);


}

HASH_CELL *makeLabel()
{
	static int nextLabel = 0;
	char buffer[128];

	sprintf(buffer, "__Label%d", nextLabel);
	nextLabel++;

	return hashInsert(&hashtable, SYMBOL_LABEL, buffer);


}

