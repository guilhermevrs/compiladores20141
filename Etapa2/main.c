/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 1

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include "hash.h"
#include "lex.yy.h"

extern int running;
extern int lineNumber;
extern HASH_TABLE hashTable;

int main(int argv, char **argc)
{
    extern int yydebug;
    int simb;

    if (argv < 2) {
        printf("Digite o nome do arquivo!!\n");
        exit(1);
    }
    
    yyin = fopen(argc[1],"r");
    printf("Arquivo: %s\n",argc[1]);

    while(running == 1) {
	yydebug = 1;
        yyparse();
    }

    printf("\n#Printing Hash Table\n\n");
    printHashTable(&hashTable);
    exit(0);
}

