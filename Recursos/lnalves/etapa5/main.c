
/*
Lucas Neubert Alves - 194917

Vinícius Garcez Schaurich - 194915

Compiladores - Etapa1

*/

#include <stdio.h>
//#include "hash.h"
//#include "lex.yy.h"
#include "astree.h"



int main(int argc, char *argv[])
{	
	int simb;
	
	initMe();

	if (argc<2)
	{
		fprintf(stderr, "call with [input] [output]..\n");
		exit (1);
	}
	if (!(yyin = fopen(argv[1], "r")))
	{
		fprintf(stderr, "Cannot open file\n");
		exit(1);
	}
	
	if (!(outputfile = fopen(argv[2], "w")))
	{
		fprintf(stderr, "Cannot open file output...\n");
		exit(1);
	}
	
	while (running)
	{
		/*simb = yyparse();
		if(simb)
			printf("linha %d token %d \n", LineNumber, simb);*/
			
			yyparse();
			
			
	}
	
	fclose(outputfile);
	//hashPrint(&hashtable);
	exit(0);
	return 0;
}
