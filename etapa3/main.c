/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "lex.yy.h"
#include "y.tab.h"

int yylex();
extern FILE * yyin;

extern int lineNumber;
extern int running;
extern HASH_TABLE Table;

int main(int argc, char **argv)
{
	initMe();

	int token;
	token = 0;

	if (argc < 2)
	{
		fprintf(stderr, "Please, indicate the file name.\n");
		return 1;
	}
	if (! (yyin = fopen(argv[1], "r")))
	{
		fprintf(stderr, "File '%s' does not exist.\n", argv[1]);		
		return 2;
	}

	yyparse();
	
	hashPrint(&Table);
	
	exit(0);
}
