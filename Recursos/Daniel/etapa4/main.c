/*
UFRGS - Compiladores B - Marcelo Johann - 2012/1 - Etapa 4

Alunos: Daniel Henrique Grehs e Victoria Ramos Pires.

Matrículas: 213998 e 213997.
*/

#include <stdio.h>
#include "hash_table.h"
#include "lex.yy.h"
#include "astree.h"

extern int running;
extern int lineNumber;
extern HASH_NODE *hashTable[MY_PRIME_NR+1];
extern FILE *ExitTree;

int main(int argv, char **argc)
{
    extern int yydebug;
    int simb;

	initMe();
    if (argv < 3) {
        printf("\nPLEASE:\n     ./etapa4 inputFileName outPutFileName\n");
        exit(1);
    }
    
    yyin = fopen(argc[1],"r");
    if (yyin==NULL){
	printf("\nNão consegue abrir a entrada\n");
	exit(1);
    }
    ExitTree = fopen(argc[2], "w");
    if (ExitTree==NULL){
	printf("\nNão consegue abrir a saida\n");
	exit(1);
    }

    yyparse();

    fclose(ExitTree);
    //printf("\n#************* Printing Hash Table *************\n\n");
    //printHashTable(&hashTable);
    exit(0);
}
