%{

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "y.tab.h"
#include "astree.h"

void initMe(void);
int LineNumber = 1;
int running = 1;


//HASH_TABLE hashtable;

#include "main.c"

%}

%x COMM

%%


"word"	{ return KW_WORD; }
"bool"	{ return KW_BOOL; }
"byte"	{ return KW_BYTE; }
"if"	{ return KW_IF;   } 
"then"	{ return KW_THEN; }
"else"	{ return KW_ELSE; }
"loop"	{ return KW_LOOP; }
"input"	{ return KW_INPUT; }
"output"	{ return KW_OUTPUT; }
"return"	{ return KW_RETURN; }

"<="	{ return OPERATOR_LE; }
">="	{ return OPERATOR_GE; }
"=="	{ return OPERATOR_EQ; }
"!="	{ return OPERATOR_NE; }
"&&"	{ return OPERATOR_AND;}
"||"	{ return OPERATOR_OR; }

[-,;:(){}+/<*>=!&\$\[\]] { return yytext[0] ;}

\n				{ ++LineNumber; }

"false"					{ yylval.symbol=hashInsert(&hashtable, LIT_FALSE, yytext); return LIT_FALSE; }
"true"					{ yylval.symbol=hashInsert(&hashtable, LIT_TRUE, yytext); return LIT_TRUE; }
"FALSE"					{ yylval.symbol=hashInsert(&hashtable, LIT_FALSE, yytext); return LIT_FALSE; }
"TRUE"					{ yylval.symbol=hashInsert(&hashtable, LIT_TRUE, yytext); return LIT_TRUE; }

[0-9]([0-9]|[a-fA-F])*			{yylval.symbol=hashInsert(&hashtable, LIT_INTEGER, yytext); return LIT_INTEGER; }
\'.\'							{yylval.symbol=hashInsert(&hashtable, LIT_CHAR, yytext); return LIT_CHAR; }
["][^"]*["]						{yylval.symbol=hashInsert(&hashtable, LIT_STRING, yytext); return LIT_STRING; }
[a-zA-Z_]([a-zA-Z_]|[0-9])*		{yylval.symbol=hashInsert(&hashtable, TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }

[ \t]   {}
"/*"	BEGIN(COMM);
"//".*	{}

<COMM>"*/" BEGIN(INITIAL);
<COMM>. {}
<COMM>\n { ++LineNumber; }

[0-9]([0-9]|[a-zA-Z])*			{yylval.symbol=hashInsert(&hashtable, TK_IDENTIFIER, yytext); return TK_IDENTIFIER;}
['][^']*[']	{ printf("Error. Undefined symbol [%s] at line %d. \t", yytext, LineNumber); return TOKEN_ERROR;}
.		{ printf("Error. Undefined symbol [%s] at line %d. \t", yytext, LineNumber); return TOKEN_ERROR;}

%%

void initMe(void){ hashInit(&hashtable); }
int getLineNumber(void){return LineNumber;}
int yywrap(){running=0;return 1; }

