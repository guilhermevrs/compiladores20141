%{
#include <stdio.h>
#include <stdlib.h>
//#include "hash.h"
//#include "astree.h"
#include "semantic.h"
#include "genco.h"

%}

%union
{
	ASTREE* astree;
	HASH_CELL *symbol;	

	/*exemplos aula*/
	int valor;
};

%right	'='
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE '<' '>' OPERATOR_AND OPERATOR_OR
%left	'+' '-'
%left	'*' '/'


%token KW_WORD		256
%token KW_BOOL		258
%token KW_BYTE		259
%token KW_IF		261
%token KW_THEN		262
%token KW_ELSE		263
%token KW_LOOP		264
%token KW_INPUT		266
%token KW_RETURN	267
%token KW_OUTPUT	268

%token OPERATOR_LE	270
%token OPERATOR_GE	271
%token OPERATOR_EQ	272
%token OPERATOR_NE	273
%token OPERATOR_AND	274
%token OPERATOR_OR	275

%token UNDEFINED		0
%token<symbol> TK_IDENTIFIER	1
%token<symbol> LIT_INTEGER		2
%token<symbol> LIT_FALSE		3
%token<symbol> LIT_TRUE			4
%token<symbol> LIT_CHAR			5
%token<symbol> LIT_STRING		6

%token TOKEN_ERROR		290

%type<astree> programa
%type<astree> decglob
%type<astree> vardec
%type<astree> vetordec
%type<astree> fundec
%type<astree> initvetor
%type<astree> literalvet
%type<astree> parametros
%type<astree> parametros2
%type<astree> tipo
%type<astree> controle_fluxo
%type<astree> output
%type<astree> ctrlbloco
%type<astree> params_func
%type<astree> params_func2
%type<astree> declocal

%type<astree> bloco
%type<astree> comandos
%type<astree> comando
%type<astree> literais
%type<astree> expressao

%%
program: programa {/*astreePrintTree ( $1, 0);*/
		checkDeclarations($1);
		checkUtilization($1);
		checkDataTypes($1);
		tac_print_list(tac_reverse(generateCode($1)));
		}
		;

programa: programa decglob { $$ = astreeCreate(ASTREE_GLIST,$1,$2,0,0, 0); }
		| { $$ = 0; }
		;

decglob: vardec ';' { $$ = $1; }
		| vetordec ';' {  $$ = $1; }
		| fundec {  $$ = $1; }
		;


vardec: tipo TK_IDENTIFIER ':' literais { $$ = astreeCreate(ASTREE_VARDEC,$1,$4,0,0,$2); $2->dataType = $1->type;}
		;

vetordec: tipo TK_IDENTIFIER '[' literalvet ']' { $$ = astreeCreate(ASTREE_VETDEC,$1,$4,0,0,$2); $2->dataType = $1->type;}
		| tipo TK_IDENTIFIER '[' literalvet ']' ':' initvetor { $$ = astreeCreate(ASTREE_VETDEC2,$1,$4,$7,0,$2); 
																$2->dataType = $1->type;}
		| tipo '$' TK_IDENTIFIER { $$ = astreeCreate(ASTREE_VETDEC3,$1,0,0,0,$3); $3->dataType = $1->type;}
		| tipo '$' TK_IDENTIFIER ':' literais { $$ = astreeCreate(ASTREE_VETDEC4,$1,$5,0,0,$3); $3->dataType = $1->type;}
		;

initvetor: literais { $$ = astreeCreate(ASTREE_INITVET,$1,0,0,0,0);  }
		| literais initvetor { $$ = astreeCreate(ASTREE_INITVET2,$1,$2,0,0,0) ; }
		;

literalvet: LIT_INTEGER { $$ = astreeCreate(ASTREE_SYMBOL,0,0,0,0, $1); $$->symbol = $1; $1->dataType = ASTREE_WORD; }
		;

literais: LIT_INTEGER	{ $$ = astreeCreate(ASTREE_SYMBOL,0,0,0,0, $1); $$->symbol = $1; $1->dataType = ASTREE_WORD;	}
		| LIT_FALSE		{ $$ = astreeCreate(ASTREE_SYMBOL,0,0,0,0, $1); $$->symbol = $1; $1->dataType = ASTREE_BOOL;    }
		| LIT_TRUE		{ $$ = astreeCreate(ASTREE_SYMBOL,0,0,0,0, $1); $$->symbol = $1; $1->dataType = ASTREE_BOOL;	}
		| LIT_CHAR		{ $$ = astreeCreate(ASTREE_SYMBOL,0,0,0,0, $1); $$->symbol = $1; $1->dataType = ASTREE_BYTE;	}
		| LIT_STRING	{ $$ = astreeCreate(ASTREE_SYMBOL,0,0,0,0, $1); $$->symbol = $1; $1->dataType = ASTREE_WORD;    }	
		;

tipo: KW_WORD 		{ $$ = astreeCreate(ASTREE_WORD,0,0,0,0,0); }
		| KW_BYTE	{ $$ = astreeCreate(ASTREE_BYTE,0,0,0,0,0); }
		| KW_BOOL	{ $$ = astreeCreate(ASTREE_BOOL,0,0,0,0,0); }
		;

fundec: tipo TK_IDENTIFIER '(' parametros ')' declocal bloco { $$ = astreeCreate(ASTREE_FUNDEC,$1,$4,$6,$7,$2); 
															   $2->dataType = $1->type; $2->funcParam = $4;}
		;
		
parametros: tipo TK_IDENTIFIER { $$ = astreeCreate(ASTREE_PARAM, $1,0,0,0, $2); $2->dataType = $1->type;}
			| tipo TK_IDENTIFIER ',' parametros2 { $$ = astreeCreate(ASTREE_PARAM, $1,$4,0,0, $2); $2->dataType = $1->type;}
			| { $$ = 0; }
			;

parametros2: tipo TK_IDENTIFIER 	{ $$ = astreeCreate(ASTREE_PARAM, $1,0,0,0, $2); $2->dataType = $1->type;}
			| tipo TK_IDENTIFIER ',' parametros2 { $$ = astreeCreate(ASTREE_PARAM, $1,$4,0,0, $2); $2->dataType = $1->type;}
			;

declocal: vardec ';' declocal { $$ = astreeCreate(ASTREE_DECLOC,$1,$3,0,0,0); }
		| { $$ = 0; }
		;

bloco: '{' comandos '}' { $$ = astreeCreate(ASTREE_BLOCO, $2, 0, 0, 0, 0); }
		;
		
ctrlbloco: comando { $$ = astreeCreate(ASTREE_CTRLBLOCO, $1, 0, 0, 0, 0); }
		;

comandos: comando ';' comandos { $$ = astreeCreate(ASTREE_CMDL, $1, $3, 0, 0, 0); }
		| {$$ = 0;}
		;

comando: TK_IDENTIFIER '=' expressao {  $$ = astreeCreate(ASTREE_SCALAR_ASS, $3, 0, 0, 0, $1); }
		| TK_IDENTIFIER '[' expressao ']' '=' expressao {$$ = astreeCreate(ASTREE_VETOR_ASS, $3, $6, 0, 0, $1);}
		| controle_fluxo {$$ = $1;}
		| KW_INPUT TK_IDENTIFIER {$$ = astreeCreate(ASTREE_KW_INPUT, 0, 0, 0, 0, $2);}
		| KW_OUTPUT output {$$ = astreeCreate(ASTREE_KW_OUTPUT, $2, 0, 0, 0, 0);}
		| KW_RETURN expressao {$$ = astreeCreate(ASTREE_KW_RETURN, $2, 0, 0, 0, 0);}
		| bloco
		;

output: expressao { $$ = astreeCreate(ASTREE_OUTPUT, $1, 0, 0, 0, 0); }
		| expressao ',' output { $$ = astreeCreate(ASTREE_OUTPUT2, $1, $3, 0, 0, NULL); }
		; 

expressao: TK_IDENTIFIER 						{ $$ = astreeCreate(ASTREE_VAR, 0, 0, 0, 0, $1); }
		| TK_IDENTIFIER '[' expressao ']'  		{ $$ = astreeCreate(ASTREE_VETOR, $3, 0, 0, 0, $1); }
		| '&' TK_IDENTIFIER 					{ $$ = astreeCreate(ASTREE_DEREFVET, 0, 0, 0, 0, $2); }
		| '*' TK_IDENTIFIER 					{ $$ = astreeCreate(ASTREE_REFVET, 0, 0, 0, 0, $2); }
		| literais 								{ $$ = $1;}
		| TK_IDENTIFIER '(' params_func ')'  	{ $$ = astreeCreate(ASTREE_FUNC, $3, 0, 0, 0, $1); }
		| '(' expressao ')'  					{ $$ = astreeCreate(ASTREE_EXPRESSION, $2, 0, 0, 0, NULL);; }
		| expressao '+' expressao 				{ $$ = astreeCreate(ASTREE_SOMA, $1, $3, 0, 0,NULL); }
		| expressao '-' expressao				{ $$ = astreeCreate(ASTREE_SUB, $1, $3, 0, 0, NULL); }
		| expressao '*' expressao				{ $$ = astreeCreate(ASTREE_MULT, $1, $3, 0, 0, NULL); }
		| expressao '/' expressao				{ $$ = astreeCreate(ASTREE_DIV, $1, $3, 0, 0, NULL); }
		| expressao OPERATOR_LE expressao		{ $$ = astreeCreate(ASTREE_LE, $1, $3, 0, 0, NULL); }
		| expressao OPERATOR_GE expressao		{ $$ = astreeCreate(ASTREE_GE, $1, $3, 0, 0, NULL); }
		| expressao OPERATOR_EQ expressao		{ $$ = astreeCreate(ASTREE_EQ, $1, $3, 0, 0, NULL); }
		| expressao OPERATOR_NE expressao		{ $$ = astreeCreate(ASTREE_NE, $1, $3, 0, 0, NULL); }
		| expressao OPERATOR_AND expressao		{ $$ = astreeCreate(ASTREE_AND, $1, $3, 0, 0, NULL); }
		| expressao OPERATOR_OR expressao		{ $$ = astreeCreate(ASTREE_OR, $1, $3, 0, 0, NULL); }
		| expressao '<' expressao				{ $$ = astreeCreate(ASTREE_LESS, $1, $3, 0, 0, NULL); }
		| expressao '>' expressao				{ $$ = astreeCreate(ASTREE_GREAT, $1, $3, 0, 0, NULL); }
		;

params_func: expressao { $$ = astreeCreate(ASTREE_PARAMFUNC, $1,0,0,0, 0);  }
			| expressao ',' params_func2 { $$ = astreeCreate(ASTREE_PARAMFUNC, $1,$3,0,0, 0); }
			| { $$ = 0; }
			;


params_func2: expressao { $$ = astreeCreate(ASTREE_PARAMFUNC,$1,0,0,0, 0); }
			| expressao ',' params_func2 { $$ = astreeCreate(ASTREE_PARAMFUNC, $1,$3,0,0, 0); }
			;


controle_fluxo: KW_IF '(' expressao ')' KW_THEN ctrlbloco { $$ = astreeCreate(ASTREE_IF, $3, $6, 0, 0, NULL); }
				| KW_IF '(' expressao ')' KW_THEN ctrlbloco KW_ELSE ctrlbloco { $$ = astreeCreate(ASTREE_IFELSE, $3, $6, $8, 0, NULL); }
				| KW_LOOP '(' expressao ')' ctrlbloco { $$ = astreeCreate(ASTREE_LOOP, $3, $5, 0, 0, NULL); }
				;
%%
#include "lex.yy.c"
int yyerror(char* str)
{
	fprintf(stderr, "[%s] [%s] at line %d\n",str ,yytext ,getLineNumber());
	exit(3);
}
