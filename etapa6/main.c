/*
// UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 6
//
// Alunos: Guilherme Schwade e Guilherme Pretto.
//
// Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include "astree.h"
#include "hash.h"
#include "lex.yy.h"
#include "y.tab.h"

int yylex();
extern FILE * yyin;
FILE * out;

extern int lineNumber;
extern int running;
extern HASH_TABLE Table;
extern ASTREE *Tree;
extern int errors;

int main(int argc, char **argv)
{
	initMe();

	int token;
	token = 0;

	errors = 0;

	if (argc < 2)
	{
		fprintf(stderr, "Write files names.\n");
		return 1;
	}
	if (! (yyin = fopen(argv[1], "r")))
	{
		fprintf(stderr, "File '%s' does not exist.\n", argv[1]);		
		return 2;
	}
	if (! (out = fopen(argv[2], "w")))
	{
		fprintf(stderr, "File '%s' does not exist.\n", argv[2]);		
		return 2;
	}

	yyparse();
	astCompile(Tree, out); 

	if (errors)
	{ 
		printf("Total errors: %d\n", errors);		
		exit(4);
	}
	else
	{ 
		exit(0);
	}
}