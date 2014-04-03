/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 1

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/


%{

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

%}

%union
{
HASH_NODE *symbol;
int number;
}


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
%token<number> LIT_INTEGER	281
%token<symbol> LIT_FALSE	283
%token<symbol> LIT_TRUE		284
%token<symbol> LIT_CHAR		285
%token<symbol> LIT_STRING	286

%token TOKEN_ERROR	290

%left OPERATOR_OR OPERATOR_AND
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'


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

decl: type identifier ':' init ';'
	;

init: LIT_INTEGER
	| LIT_FALSE
	| LIT_TRUE
	;

decl_vector: type identifier '[' LIT_INTEGER ']' ':' init_vector ';'
	| type identifier '[' LIT_INTEGER ']' ';'
	;

init_vector: init
	| init init_vector
	;

decl_pointer: type '$' identifier ':' init ';'
	;


//Function

function: type identifier '(' n_param ')' command ';'
	;

n_param: 
	| param n_param2
	;

n_param_2:
	| ',' param n_param2
	;

param: type identifier
	| type '$' identifier
	;

// Commands
command: simple_command
	| block
       ;

block: '{' command_block '}'
	;

command_block: command
	| command command_block
	;

simple_command:
	| attribution
	| if
	| loop
	| KW_INPUT identifier { printf("input\n");}
	| kw_output out { printf("output\n");}
	| kw_return expression
	;

attribution: identifier '=' expression
	| identifier '[' expression ']' '=' expression
	;

out: element
	| element ',' out
	| expression
	| expression ',' out
	;


//control flow

if: kw_if '(' expression ')' kw_then command
	| kw_if '(' expression ')' kw_else command kw_then command
	;

loop: kw_loop command '(' expression ')'
	;


// types

identifier: tk_identifier
	;

type:kw_word 
	| kw_byte
	| kw_bool
	;

expression: element
	| identifier '[' expression ']'
	| expression '+' expression
	| expression '-' expression
	| expression '/' expression
	| expression '*' expression
	| expression '<' expression
	| expression '>' expression
	| expression operator_le expression
	| expression operator_ge expression
	| expression operator_eq expression
	| expression operator_ne expression
	| expression operator_and expression
	| expression operator_or expression
	| identifier '(' n_param_ref ')'
	| '(' expression ')'
	| '!' expression
	| '&' expression
	| '$' expression
	;

n_param_ref: 
	| expression n_param_ref2
	;

n_param_ref2:
	| ',' expression n_param_ref2
	;

element: identifier
	| LIT_INTEGER
	| LIT_FALSE
	| LIT_TRUE
	| LIT_CHAR
	| LIT_STRING
	;

%%

int yyerror (char *s)
{
	fprintf(stderr, "Error in line %d: %s.\n", getLineNumber(), s);
	exit(3);
}
