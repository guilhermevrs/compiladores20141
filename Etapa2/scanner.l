%x comment

%{
/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 1

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include "hash.h"
#include "y.tab.h"

int running = 1;
int lineNumber = 1;

void initMe(void) { hash_init(); }
int getLineNumber(void) { return lineNumber; }

%}
INTEGER		[0-9]
CHAR			[a-zA-Z_]
SPECIAL		[,;:(){}\[\]{}\+\-\*<>=!&$\/]

%%

\n								++lineNumber;
"word"							return KW_WORD;
"bool"							return KW_BOOL;
"byte"							return KW_BYTE;
"if"							return KW_IF;
"then"							return KW_THEN;
"else"							return KW_ELSE;
"loop"							return KW_LOOP;
"input"							return KW_INPUT;
"return"						return KW_RETURN;
"output"						return KW_OUTPUT;

"FALSE"							{ yylval.symbol = hash_insert( yytext, LIT_FALSE); return LIT_FALSE; }
"TRUE"							{ yylval.symbol = hash_insert( yytext, LIT_TRUE); return LIT_TRUE; }
({INTEGER})+						{ yylval.symbol = hash_insert( yytext, LIT_INTEGER); return LIT_INTEGER; }

({CHAR}|{INTEGER})+				{ yylval.symbol = hash_insert( yytext, TK_IDENTIFIER); return TK_IDENTIFIER; }

'(\\.|[^\\'])+'						{ yylval.symbol = hash_insert( yytext, LIT_CHAR); return LIT_CHAR; }
\"(\\.|[^\\"])*\"					{ yylval.symbol = hash_insert( yytext, LIT_STRING); return LIT_STRING; }

"<="							return OPERATOR_LE;
">="							return OPERATOR_GE;
"=="							return OPERATOR_EQ;
"!="							return OPERATOR_NE;
"&&"							return OPERATOR_AND;
"||"							return OPERATOR_OR;

[ \t\v\f]						/* Ignorar caracteres inuteis */
\/\/.*							/* Ignorar comentarios */
"/*"         					BEGIN(comment);
<comment>[^*\n]*
<comment>"*"+[^*/\n]*
<comment>"\n"					++lineNumber;
<comment>"*"+"/"				BEGIN(INITIAL);

{SPECIAL}						return yytext[0];


.	{ printf("ERROR at line %d. Undefined symbol \"%s\"n",getLineNumber(),yytext); return TOKEN_ERROR; }

%%

int yywrap(void) { running = 0; return 1; }
