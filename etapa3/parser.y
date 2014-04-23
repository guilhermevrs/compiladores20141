/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/


%{

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "hash.h"

%}

%union
{
  HASH_NODE *symbol;
  ASTREE *astree;
  int number;
}

%type<astree> program
%type<astree> decl_global
%type<astree> decl
%type<astree> init
%type<astree> decl_vector
%type<astree> init_vector
%type<astree> decl_pointer
%type<astree> function
%type<astree> n_param
%type<astree> n_param_2
%type<astree> param
%type<astree> command
%type<astree> block
%type<astree> command_block
%type<astree> simple_command
%type<astree> attribution
%type<astree> out
%type<astree> if
%type<astree> loop
%type<astree> identifier
%type<astree> type
%type<astree> expression
%type<astree> n_param_ref
%type<astree> n_param_ref2
%type<astree> element

%token KW_WORD		256
%token KW_BOOL		258
%token KW_BYTE		259
%token KW_IF		             261
%token KW_THEN		262
%token KW_ELSE		263
%token KW_LOOP		264
%token KW_INPUT		266
%token KW_OUTPUT	267
%token KW_RETURN	268

%token OPERATOR_LE	270
%token OPERATOR_GE	271
%token OPERATOR_EQ	272
%token OPERATOR_NE	273
%token OPERATOR_AND	274
%token OPERATOR_OR	275

%token<symbol> TK_IDENTIFIER	280
%token<symbol> LIT_INTEGER	281
%token<symbol> LIT_FALSE	283
%token<symbol> LIT_TRUE		284
%token<symbol> LIT_CHAR		285
%token<symbol> LIT_STRING	286

%token TOKEN_ERROR	290

%left OPERATOR_OR OPERATOR_AND
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'
%nonassoc '$' '&' '!'


%%

program: decl_global                     {$$ = $1;}
	| decl_global program              	 {$$ = astCreate(AST_program, 0, $1, $2, 0, 0);} //
	| function                           {$$ = $1;}
	| function program                   {$$ = astCreate(AST_program, 0, $1, $2, 0, 0);} //
	;


// Declarations

decl_global: decl                              {$$ = $1;}
	| decl_vector                              {$$ = $1;}
	| decl_pointer                             {$$ = $1;}
	;

decl: type identifier ':' init ';'	{ $$ = astCreate(AST_decl_var, $2, $1, $4, 0, 0);} //
	;

init: LIT_INTEGER				{ $$ = astCreate(AST_LIT_INTEGER,$1, 0, 0, 0, 0);}  //ok
	| LIT_FALSE					{ $$ = astCreate(AST_LIT_FALSE,$1, 0, 0, 0, 0);}	//ok
	| LIT_TRUE					{ $$ = astCreate(AST_LIT_TRUE,$1, 0, 0, 0, 0);}		//ok
	| LIT_CHAR					{ $$ = astCreate(AST_LIT_CHAR,$1, 0, 0, 0, 0);}		//ok
	| LIT_STRING				{ $$ = astCreate(AST_LIT_STRING,$1, 0, 0, 0, 0);}	//ok
	;

decl_vector: type identifier '[' LIT_INTEGER ']' ':' init_vector ';' 	{ $$ = astCreate(AST_decl_vetch,$2,$1,$4,$7, 0);} //ok
	| type identifier '[' LIT_INTEGER ']' ';'							{ $$ =  astCreate(AST_decl_vet, $2, $1, $4, 0, 0);} //ok
	;

init_vector: init                                                       {$$ =  astCreate(AST_init,0, $1, 0, 0, 0);} //
	| init init_vector                                                  {$$ =  astCreate(AST_init_vector, 0, $2,$1, 0, 0);} //
	;

decl_pointer: type '$' identifier ':' init ';'				{ $$ = astCreate(AST_decl_pointer,$3,$1,$5, 0, 0);} //
	;


//Function

function: type identifier '(' n_param ')' command ';'                   {$$ = astCreate(AST_function, $2, $1, $4, $6, 0);} //
	;

n_param:
	| param n_param_2                                                          {$$ = astCreate(AST_n_param, 0, $1, $2, 0, 0);}
	;

n_param_2:
	| ',' param n_param_2                                                      {$$ = 0;} //TODO
	;

param: type identifier                            {$$ = astCreate(AST_param, $2, $1, 0, 0, 0);}
	| type '$' identifier                         {$$ = astCreate(AST_param, $3, $1, 0, 0, 0);}
	;

// Commands
command: simple_command                     {$$ = $1;}
	| block                                 {$$ = $1;}
       ;

block: '{' command_block '}' 				{$$ = astCreate(AST_bloco, 0, $2, 0, 0, 0);}
	| '{' '}'                         		{$$ = astCreate(AST_bloco, 0, 0, 0, 0, 0);}
	;

command_block: simple_command               {$$ = $1;}
	| simple_command command_block          {$$ = astCreate(AST_command_block, 0, $2, $1, 0, 0);}
	;

//
simple_command:attribution                  {$$ = $1;}
	| if                                    {$$ = $1;}
	| loop                                  {$$ = $1;}
	| KW_INPUT identifier 					{$$ = astCreate(AST_KW_INPUT, 0, $2, 0, 0, 0);} 				//ok
	| KW_OUTPUT out 						{$$ = astCreate(AST_KW_OUTPUT,0, $2, 0, 0, 0);} 				//ok
	| KW_RETURN expression 					{$$ = astCreate(AST_KW_RETURN,0, $2, 0, 0, 0);} 				//ok
	;

attribution: identifier '=' expression 				{$$ = astCreate(AST_ATRIB_CONST, 0, $1, $3, 0, 0);} 	//ok
	| identifier '[' expression ']' '=' expression 		{$$ = astCreate(AST_ATRIB_VET, 0, $1, $3, $6, 0);}
	;

out	:expression						{$$ = $1;}
	| expression ',' out    				{$$ = astCreate(AST_outp,0, $1, $3, 0, 0);}
	;


//control flow

if	: KW_IF '(' expression ')' KW_THEN command 		{ $$ = astCreate(AST_KW_IF, 0, $3,$6, 0, 0);} //ok
	| KW_IF '(' expression ')' KW_ELSE command KW_THEN command { $$ = astCreate(AST_KW_IF_ELSE, 0, $3,$6,$8, 0);} //ok
	;

loop: KW_LOOP command '(' expression ')' 			{ $$ = astCreate(AST_KW_LOOP, 0, $2,$4, 0, 0);} //ok
	;


// types

type :KW_WORD 						{ $$ = astCreate(AST_KW_WORD, 0, 0, 0, 0, 0);} //ok
	| KW_BYTE 						{ $$ = astCreate(AST_KW_BYTE, 0, 0, 0, 0, 0);} //ok
	| KW_BOOL 						{ $$ = astCreate(AST_KW_BOOL, 0, 0, 0, 0, 0);} //ok
	;

expression: element
	| identifier '[' expression ']' 	{ $$ = astCreate(AST_exprComChavesTK_IDENTIFIER, 0, $1, $3, 0, 0);}  //ok
	| identifier '(' n_param_ref ')'	{ $$ = astCreate(AST_exprComParFuncTK_IDENTIFIER, 0, $1, $3, 0, 0);} //ok
	| expression '+' expression 		{ $$ = astCreate(AST_ADD, 0, $1, $3, 0, 0);} 			//ok
	| expression '-' expression 		{ $$ = astCreate(AST_SUB, 0, $1, $3, 0, 0);} 			//ok
	| expression '/' expression 		{ $$ = astCreate(AST_DIV, 0, $1, $3, 0, 0);} 			//ok
	| expression '*' expression 		{ $$ = astCreate(AST_MUL, 0, $1, $3, 0, 0);} 			//ok
	| expression '<' expression 		{ $$ = astCreate(AST_MENOR, 0, $1, $3, 0, 0);} 			//ok
	| expression '>' expression 		{ $$ = astCreate(AST_MAIOR, 0, $1, $3, 0, 0);} 			//ok
	| expression OPERATOR_LE expression 	{ $$ = astCreate(AST_OPERATOR_LE, 0, $1,$3, 0, 0);} //ok
	| expression OPERATOR_GE expression 	{ $$ = astCreate(AST_OPERATOR_GE, 0, $1,$3, 0, 0);} //ok
	| expression OPERATOR_EQ expression 	{ $$ = astCreate(AST_OPERATOR_EQ, 0, $1,$3, 0, 0);} //ok
	| expression OPERATOR_NE expression 	{ $$ = astCreate(AST_OPERATOR_NE, 0, $1,$3, 0, 0);} //ok
	| expression OPERATOR_AND expression 	{ $$ = astCreate(AST_OPERATOR_AND, 0, $1,$3, 0, 0);} //ok
	| expression OPERATOR_OR expression 	{ $$ = astCreate(AST_OPERATOR_OR, 0, $1,$3, 0, 0);} //ok
	| '(' expression ')' 			{ $$ = astCreate(AST_exprComParent, 0, $2, 0, 0, 0);} 		//ok
	| '!' expression			{$$=0;}
	| '&' expression			{$$=0;}
	| '$' expression			{$$=0;}
	;

n_param_ref:
	| expression n_param_ref2
	;

n_param_ref2:
	| ',' expression n_param_ref2
	;

element: identifier
	| LIT_INTEGER 	{ $$ = astCreate(AST_LIT_INTEGER,$1, 0, 0, 0, 0);} 
	| LIT_FALSE	{ $$ = astCreate(AST_LIT_FALSE,$1, 0, 0, 0, 0);} //ok
	| LIT_TRUE 	{ $$ = astCreate(AST_LIT_TRUE,$1, 0, 0, 0, 0);} //ok
	| LIT_CHAR	{ $$ = astCreate(AST_LIT_CHAR,$1, 0, 0, 0, 0);}
	| LIT_STRING	{ $$ = astCreate(AST_LIT_STRING,$1, 0, 0, 0, 0);} //ok
	;

identifier: TK_IDENTIFIER 					{ $$ = astCreate(AST_TK_IDENTIFIER,$1, 0, 0, 0, 0);} //ok
	;

%%

int yyerror (char *s)
{
	fprintf(stderr, "Error in line %d: %s.\n", getLineNumber(), s);
	exit(3);
}
