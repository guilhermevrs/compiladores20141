%x comment
%{
/*
UFRGS - Compiladores B - Marcelo Johann - 2012/1 - Etapa 4

Alunos: Daniel Henrique Grehs e Victoria Ramos Pires.

Matrículas: 213998 e 213997.
*/

#include <stdio.h>
#include "hash_table.h"
#include "astree.h"
#include "y.tab.h"

int running = 1;
int lineNumber = 1;
void initMe();
int getLineNumber();

%}

INTEGER		[0-9]
CHAR		[a-zA-Z_]
SPECIAL		[,;:(){}\[\]{}\+\-\*<>=!\/]

%%

\n							++lineNumber;
"integer"						return KW_INTEGER;
"floating"						return KW_FLOATING;
"boolean"						return KW_BOOLEAN;
"character"						return KW_CHARACTER;
"declare"						return KW_DECLARE;
"if"							return KW_IF;
"then"							return KW_THEN;
"else"							return KW_ELSE;
"while"							return KW_WHILE;
"do"							return KW_DO;
"input"							return KW_INPUT;
"return"						return KW_RETURN;
"output"						return KW_OUTPUT;

"false"							{ yylval.symbol = hashInsert(SYMBOL_LIT_FALSE, yytext); return LIT_FALSE; }
"true"							{ yylval.symbol = hashInsert(SYMBOL_LIT_TRUE, yytext); return LIT_TRUE; }

{CHAR}({CHAR}|{INTEGER})*		{ yylval.symbol = hashInsert(SYMBOL_TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }
{INTEGER}+				{ yylval.symbol = hashInsert(SYMBOL_LIT_INTEGER, yytext); return LIT_INTEGER; }
{INTEGER}+\.{INTEGER}+			{ yylval.symbol = hashInsert(SYMBOL_LIT_FLOATING, yytext); return LIT_FLOATING; }

'(\\.|[^\\'])'				{ yylval.symbol = hashInsert(SYMBOL_LIT_CHAR, yytext); return LIT_CHAR; }
\"(\\.|[^\\"])*\"			{ yylval.symbol = hashInsert(SYMBOL_LIT_STRING, yytext); return LIT_STRING; }

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

int yywrap() { running = 0; return 1; }
void initMe() {
    hashInit();
}
int getLineNumber() { return lineNumber; }
