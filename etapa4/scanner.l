/*
// UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 4
//
// Alunos: Guilherme Schwade e Guilherme Pretto.
//
// Matrículas: 192332 e 213991.
*/

%{

#include <stdio.h>
#include "astree.h"
#include "y.tab.h"
#include "hash.h"

HASH_TABLE Table;
int lineNumber;
int running;

%}

%x COMMENT


%%

"word"			{ return KW_WORD; }
"bool"			{ return KW_BOOL; }
"byte"			{ return KW_BYTE; }
"if"			{ return KW_IF; }
"then"			{ return KW_THEN; }
"else"			{ return KW_ELSE; }
"loop"			{ return KW_LOOP; }
"input"			{ return KW_INPUT; }
"output"		{ return KW_OUTPUT; }
"return"		{ return KW_RETURN; }

"\n"			{ ++lineNumber;}
"\t"			{}
" "			{}

"<="			{ return OPERATOR_LE; }
">="			{ return OPERATOR_GE; }
"=="			{ return OPERATOR_EQ; }
"!="			{ return OPERATOR_NE; }
"&&"			{ return OPERATOR_AND; }
"||"			{ return OPERATOR_OR; }

[<=>+*%/&$(){},;:!\-\[\]]	{ return yytext[0]; }

"//".*			{}
"/*"			{ BEGIN(COMMENT); }
<COMMENT>"*/"		{ BEGIN(INITIAL); }
<COMMENT>"\n"		{ lineNumber++; }
<COMMENT>.		{}


"true"				{ yylval.symbol = hashInsert(&Table, yytext, SYMBOL_LIT_TRUE,getLineNumber()); 
				  return LIT_TRUE; 
				}
"false"				{ yylval.symbol = hashInsert(&Table, yytext, SYMBOL_LIT_FALSE, getLineNumber()); 
				  return LIT_FALSE; 
				}

[0-9]+				{ yylval.symbol = hashInsert(&Table, yytext, SYMBOL_LIT_INTEGER, getLineNumber()); 
				  return LIT_INTEGER;
				}

[0-9]*[a-zA-Z_][a-zA-Z_0-9]*	{ yylval.symbol = hashInsert(&Table, yytext, SYMBOL_IDENTIFIER, getLineNumber()); 
				  return TK_IDENTIFIER;
				}

"\'"(.)"\'"			{ yylval.symbol = hashInsert(&Table, yytext, SYMBOL_LIT_CHAR, getLineNumber()); 
				  return LIT_CHAR;
				}

\"[^\"]*\"			{ yylval.symbol = hashInsert(&Table, yytext, SYMBOL_LIT_STRING, getLineNumber()); 
				  return LIT_STRING;
				}



.			{ return TOKEN_ERROR; }

%%

int getLineNumber(void)
{
	return lineNumber;
}

void initMe(void)
{
	running = 1;
	lineNumber = 1;
	hashInit(&Table);
}

int yywrap(void)
{
	running  = 0;
	return 1;
}
