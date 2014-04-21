/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/


%{

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"

%}

%union
{
  HASH_NODE *symbol;
  ASTREE *astree;
  int number;
}

%type<ast> program
%type<ast> decl_global
%type<ast> decl
%type<ast> init
%type<ast> decl_vector
%type<ast> init_vector
%type<ast> decl_pointer
%type<ast> function
%type<ast> n_param
%type<ast> n_param_2
%type<ast> param
%type<ast> command
%type<ast> block
%type<ast> command_block
%type<ast> simple_command
%type<ast> attribution
%type<ast> out
%type<ast> if
%type<ast> loop
%type<ast> identifier
%type<ast> type
%type<ast> expression
%type<ast> n_param_ref
%type<ast> n_param_ref2
%type<ast> element

%token KW_WORD		256
%token KW_BOOL		258
%token KW_BYTE		259
%token KW_IF		261
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

%type <astree> expression;

%%

program: decl_global		
	| decl_global program	
	| function		
	| function program	
	;


// Declarations

decl_global: decl		
	| decl_vector		
	| decl_pointer		
	;

decl: type identifier ':' init ';'	{ $$ = astCreate(AST_decl_var,$2,$1,$4, 0, 0);}
	;

init	: LIT_INTEGER			{ $$ = astCreate(AST_LIT_INTEGER,$1, 0, 0, 0, 0);}
	| LIT_FALSE			{ $$ = astCreate(AST_LIT_FALSE,$1, 0, 0, 0, 0);}
	| LIT_TRUE			{ $$ = astCreate(AST_LIT_TRUE,$1, 0, 0, 0, 0);}
	| LIT_CHAR			{ $$ = astCreate(AST_LIT_CHAR,$1, 0, 0, 0, 0);}
	| LIT_STRING			{ $$ = astCreate(AST_LIT_STRING,$1, 0, 0, 0, 0);}
	;

decl_vector: type identifier '[' LIT_INTEGER ']' ':' init_vector ';' 	{ $$ = astCreate(AST_decl_vetch,$2,$1,$4, $7, 0);}
	| type identifier '[' LIT_INTEGER ']' ';'			{ $$ = astCreate(AST_decl_vet,$2,$1,$4, 0, 0);}
	;

init_vector: init
	| init init_vector
	;

decl_pointer: type '$' identifier ':' init ';'				{ $$ = astCreate(AST_decl_pointer,$3,$1,$5, 0, 0);}
	;


//Function

function: type identifier '(' n_param ')' command ';'
	;

n_param: 
	| param n_param_2
	;

n_param_2:
	| ',' param n_param_2
	;

param: type identifier
	| type '$' identifier
	;

// Commands
command: simple_command
	| block
       ;

block: '{' command_block '}' {$$ = astCreate(AST_bloco, 0, $2, 0, 0, 0);}
	| '{' '}'
	;

command_block: simple_command
	| simple_command command_block
	;

//
simple_command:attribution
	| if
	| loop
	| KW_INPUT identifier 					{$$ = astCreate(AST_KW_INPUT, $2, 0, 0, 0, 0);}
	| KW_OUTPUT out 					{$$ = astCreate(AST_KW_OUTPUT,0, $2, 0, 0, 0);}
	| KW_RETURN expression 					{$$ = astCreate(AST_KW_RETURN,0, $2, 0, 0, 0);}
	;

attribution: identifier '=' expression 				{$$ = astCreate(AST_ATRIB_CONST, $1, $3, 0, 0, 0);}
	| identifier '[' expression ']' '=' expression 		{$$ = astCreate(AST_ATRIB_VET, $1, $3, $6, 0, 0);}
	;

out	:expression						{$$ = astCreate(AST_outp,0, $1, 0, 0, 0);}
	| expression ',' out    				{$$ = astCreate(AST_outp2,0, $1, $3, 0, 0);}
	;


//control flow

if	: KW_IF '(' expression ')' KW_THEN command 		{ $$ = astCreate(AST_KW_IF, 0, $3,$6, 0, 0);}
	| KW_IF '(' expression ')' KW_ELSE command KW_THEN command { $$ = astCreate(AST_KW_IF_ELSE, 0, $3,$6,$8, 0);}
	;

loop: KW_LOOP command '(' expression ')' 			{ $$ = astCreate(AST_KW_LOOP, 0, $3,$5, 0, 0);}
	;


// types

identifier: TK_IDENTIFIER 					{ $$ = astCreate(AST_TK_IDENTIFIER,$1, 0, 0, 0, 0);}
	;

type	:KW_WORD 						{ $$ = astCreate(AST_KW_WORD, 0, 0, 0, 0, 0);}
	| KW_BYTE 						{ $$ = astCreate(AST_KW_BYTE, 0, 0, 0, 0, 0);}
	| KW_BOOL 						{ $$ = astCreate(AST_KW_BOOL, 0, 0, 0, 0, 0);}
	;

expression: element
	| identifier '[' expression ']' 	{ $$ = astCreate(AST_exprComChavesTK_IDENTIFIER,$1, $3, 0, 0, 0);}
	| identifier '(' n_param_ref ')'	{ $$ = astCreate(AST_exprComParFuncTK_IDENTIFIER,$1, $3, 0, 0, 0);}
	| expression '+' expression 		{ $$ = astCreate(AST_ADD, 0, $1, $3, 0, 0,);}
	| expression '-' expression 		{ $$ = astCreate(AST_SUB, 0, $1, $3, 0, 0,);}
	| expression '/' expression 		{ $$ = astCreate(AST_DIV, 0, $1, $3, 0, 0,);}
	| expression '*' expression 		{ $$ = astCreate(AST_MUL, 0, $1, $3, 0, 0,);}
	| expression '<' expression 		{ $$ = astCreate(AST_MENOR, 0, $1, $3, 0, 0,);}
	| expression '>' expression 		{ $$ = astCreate(AST_MAIOR, 0, $1, $3, 0, 0,);}
	| expression OPERATOR_LE expression 	{ $$ = astCreate(AST_OPERATOR_LE, 0, $1,$3, 0, 0);}
	| expression OPERATOR_GE expression 	{ $$ = astCreate(AST_OPERATOR_GE, 0, $1,$3, 0, 0);}
	| expression OPERATOR_EQ expression 	{ $$ = astCreate(AST_OPERATOR_EQ, 0, $1,$3, 0, 0);}
	| expression OPERATOR_NE expression 	{ $$ = astCreate(AST_OPERATOR_NE, 0, $1,$3, 0, 0);}
	| expression OPERATOR_AND expression 	{ $$ = astCreate(AST_OPERATOR_AND, 0, $1,$3, 0, 0);}
	| expression OPERATOR_OR expression 	{ $$ = astCreate(AST_OPERATOR_OR, 0, $1,$3, 0, 0);}
	| '(' expression ')' 			{ $$ = astCreate(AST_exprComParent, 0, $2, 0, 0, 0);}
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
	| LIT_FALSE	{ $$ = astCreate(AST_LIT_FALSE,$1, 0, 0, 0, 0);}
	| LIT_TRUE 	{ $$ = astCreate(AST_LIT_TRUE,$1, 0, 0, 0, 0);}
	| LIT_CHAR	{ $$ = astCreate(AST_LIT_CHAR,$1, 0, 0, 0, 0);}
	| LIT_STRING	{ $$ = astCreate(AST_LIT_STRING,$1, 0, 0, 0, 0);}
	;

%%

int yyerror (char *s)
{
	fprintf(stderr, "Error in line %d: %s.\n", getLineNumber(), s);
	exit(3);
}
