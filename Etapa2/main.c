/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 1

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include "hash.h"
#include "lex.yy.h"


int main(int argv, char **argc)
{
    int token;
    yyin = fopen("teste.txt","r");
    while(running)
	{
        token = yylex();
        if(!running) break;
    }

    hash_print();
    return 0;
}

