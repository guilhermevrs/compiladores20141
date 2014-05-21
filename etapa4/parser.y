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

ASTREE *Tree;
extern HASH_TABLE Table;
int error = 0;

%}

%token KW_WORD      256
%token KW_BOOL      258
%token KW_BYTE      259
%token KW_IF        261
%token KW_THEN      262
%token KW_ELSE      263
%token KW_LOOP      264
%token KW_INPUT     266
%token KW_OUTPUT    267
%token KW_RETURN    268

%token OPERATOR_LE  270
%token OPERATOR_GE  271
%token OPERATOR_EQ  272
%token OPERATOR_NE  273
%token OPERATOR_AND 274
%token OPERATOR_OR  275

%token<symbol> TK_IDENTIFIER    280
%token<symbol> LIT_INTEGER  281
%token<symbol> LIT_FALSE    283
%token<symbol> LIT_TRUE     284
%token<symbol> LIT_CHAR     285
%token<symbol> LIT_STRING   286

%token TOKEN_ERROR      290

%union
{
    HASH_NODE *symbol;
    ASTREE *astreeObject;
}

%left OPERATOR_OR OPERATOR_AND
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'
%nonassoc '&' '$' '!'

%type<astreeObject> element
%type<astreeObject> identifier
%type<astreeObject> n_param_ref
%type<astreeObject> n_param_ref2
%type<astreeObject> expression
%type<astreeObject> type
%type<astreeObject> out
%type<astreeObject> attribution
%type<astreeObject> simple_command
%type<astreeObject> command_block
%type<astreeObject> command
%type<astreeObject> param
%type<astreeObject> n_param
%type<astreeObject> function
%type<astreeObject> decl_pointer
%type<astreeObject> init_vector
%type<astreeObject> decl_vector
%type<astreeObject> init decl
%type<astreeObject> decl_global
%type<astreeObject> program
%type<astreeObject> inicio


%%

inicio: program { $$ = $1; Tree = $$; error += astTreeCheckDeclaration(Tree); error += astTreeCheckUndeclared(&Table); error += astCheckNature(Tree,Tree); return error;}
    ;

program: decl_global { $$ = $1; }
    | decl_global program { $$ = astCreate (ASTREE_DEF_PROGRAM,0,$1,$2,0,0); }
    | function { $$ = $1; }
    | function program { $$ = astCreate (ASTREE_DEF_PROGRAM,0,$1,$2,0,0); }
    ;

decl_global: decl { $$ = $1; }
    | decl_vector { $$ = $1; }
    | decl_pointer { $$ = $1; }
    ;

decl: type identifier ':' init ';' { $$ = astCreate (ASTREE_DEF_DECL,0,$1,$2,$4,0);  }
    ;

init: LIT_INTEGER { $$ = astCreate (ASTREE_DEF_SYMBOL,$1,0,0,0,0); }
    | LIT_FALSE { $$ = astCreate (ASTREE_DEF_SYMBOL,$1,0,0,0,0); }
    | LIT_TRUE { $$ = astCreate (ASTREE_DEF_SYMBOL,$1,0,0,0,0); }
    | LIT_CHAR { $$ = astCreate (ASTREE_DEF_SYMBOL,$1,0,0,0,0); }
    ;

decl_vector: type identifier '[' LIT_INTEGER ']' ':' init_vector ';' { $$ = astCreate (ASTREE_DEF_DECL_VEC_INIT,$4,$1,$2,$7,0); }
    | type identifier '[' LIT_INTEGER ']' ';' { $$ = astCreate (ASTREE_DEF_DECL_VEC,$4,$1,$2,0,0); }
    ;

init_vector: init { $$ = $1; }
    | init init_vector { $$ = astCreate (ASTREE_DEF_INIT_VEC,0,$1,$2,0,0); }
    ;

decl_pointer: type '$' identifier ':' init ';' { $$ = astCreate (ASTREE_DEF_DECL_POINTER,0,$1,$3,$5,0); }
    ;


// FUNCTION

function: type identifier '(' n_param ')' command ';' { $$ = astCreate (ASTREE_DEF_FUNC,0,$1,$2,$4,$6); }
    ;

n_param: { $$ = 0; }
    | type identifier param { $$ = astCreate (ASTREE_DEF_PARAM,0,$1,$2,$3,0); }
    ;

param: { $$ = 0; }
    | ',' type identifier param { $$ = astCreate (ASTREE_DEF_PARAM,0,$2,$3,$4,0); }
    | ',' type '$' identifier param { $$ = astCreate (ASTREE_DEF_PARAM_POINTER,0,$2,$4,$5,0); }
    ;

command: simple_command { $$ = astCreate (ASTREE_DEF_SIMPLE_COMMAND,0,$1,0,0,0); }// { $$ = $1; }
    | '{' command_block '}' { $$ = astCreate (ASTREE_DEF_BLOCK,0,$2,0,0,0); } // { $$ = $2; }
    ;

command_block: { $$ = 0; }
    | command command_block { $$ = astCreate (ASTREE_DEF_COMMAND_BLOCK,0,$1,$2,0,0); }
    ;

simple_command: attribution { $$ = $1; }
    | KW_IF '(' expression ')' KW_THEN command { $$ = astCreate (ASTREE_DEF_IF,0,$3,$6,0,0); }
    | KW_IF '(' expression ')' KW_ELSE command KW_THEN command { $$ = astCreate (ASTREE_DEF_IFELSE,0,$3,$6,$8,0); }
    | KW_LOOP command '(' expression ')' { $$ = astCreate (ASTREE_DEF_LOOP,0,$2,$4,0,0); }
    | KW_INPUT identifier { $$ = astCreate (ASTREE_DEF_INPUT,0,$2,0,0,0); }
    | KW_OUTPUT out { $$ = astCreate (ASTREE_DEF_OUTPUT,0,$2,0,0,0); }
    | KW_RETURN expression { $$ = astCreate (ASTREE_DEF_RETURN,0,$2,0,0,0); }
    ;

attribution: identifier '=' expression { $$ = astCreate (ASTREE_DEF_ATTR,0,$1,$3,0,0); }
    | identifier '[' expression ']' '=' expression { $$ = astCreate (ASTREE_DEF_ATTR_VEC,0,$1,$3,$6,0); }
    ;

out: expression { $$ = $1; }
    | expression ',' out { $$ = astCreate (ASTREE_DEF_OUT_LST,0,$1,$3,0,0); }
    ;


type:KW_WORD { $$ = astCreate(ASTREE_DEF_KWWORD,0,0,0,0,0); }
    | KW_BYTE { $$ = astCreate(ASTREE_DEF_KWBYTE,0,0,0,0,0); }
    | KW_BOOL { $$ = astCreate(ASTREE_DEF_KWBOOL,0,0,0,0,0); }
    ;

expression: element { $$ = $1; }
    | identifier '[' expression ']'{ $$ = astCreate(ASTREE_DEF_VEC_ACCESS,0,$1,$3,0,0); }
    | identifier '(' n_param_ref ')' { $$ = astCreate(ASTREE_DEF_FUNC_CALL,0,$1,$3,0,0); }
    | expression '+' expression { $$ = astCreate(ASTREE_DEF_ADD,0,$1,$3,0,0); }
    | expression '-' expression { $$ = astCreate(ASTREE_DEF_SUB,0,$1,$3,0,0); }
    | expression '/' expression { $$ = astCreate(ASTREE_DEF_DIV,0,$1,$3,0,0); }
    | expression '*' expression { $$ = astCreate(ASTREE_DEF_MUL,0,$1,$3,0,0); }
    | expression '<' expression { $$ = astCreate(ASTREE_DEF_LESS,0,$1,$3,0,0); }
    | expression '>' expression { $$ = astCreate(ASTREE_DEF_GREATER,0,$1,$3,0,0); }
    | expression OPERATOR_LE expression { $$ = astCreate(ASTREE_DEF_OP_LE,0,$1,$3,0,0); }
    | expression OPERATOR_GE expression { $$ = astCreate(ASTREE_DEF_OP_GE,0,$1,$3,0,0); }
    | expression OPERATOR_EQ expression { $$ = astCreate(ASTREE_DEF_OP_EQ,0,$1,$3,0,0); }
    | expression OPERATOR_NE expression { $$ = astCreate(ASTREE_DEF_OP_NE,0,$1,$3,0,0); }
    | expression OPERATOR_AND expression { $$ = astCreate(ASTREE_DEF_OP_AND,0,$1,$3,0,0); }
    | expression OPERATOR_OR expression { $$ = astCreate(ASTREE_DEF_OP_OR,0,$1,$3,0,0); }
    | '(' expression ')' { $$ = $2; }
    | '&' expression { $$ = astCreate(ASTREE_DEF_REF,0,$2,0,0,0); }
    | '$' expression { $$ = astCreate(ASTREE_DEF_DEREF,0,$2,0,0,0); }
    ;

n_param_ref: { $$ = 0; }
    | expression n_param_ref2 { $$ = astCreate(ASTREE_DEF_PARAM_REF,0,$1,$2,0,0); }
    ;

n_param_ref2: { $$ = 0; }
    | ',' expression n_param_ref2 { $$ = astCreate(ASTREE_DEF_PARAM_REF,0,$2,$3,0,0); }
    ;

identifier: TK_IDENTIFIER { $$ = astCreate (ASTREE_DEF_SYMBOL,$1,0,0,0,0); }
    ;

element: identifier { $$ = $1; }
    | LIT_INTEGER { $$ = astCreate (ASTREE_DEF_SYMBOL,$1,0,0,0,0); }
    | LIT_FALSE { $$ = astCreate (ASTREE_DEF_SYMBOL,$1,0,0,0,0); }
    | LIT_TRUE { $$ = astCreate (ASTREE_DEF_SYMBOL,$1,0,0,0,0); }
    | LIT_CHAR { $$ = astCreate (ASTREE_DEF_SYMBOL,$1,0,0,0,0); }
    | LIT_STRING { $$ = astCreate (ASTREE_DEF_SYMBOL,$1,0,0,0,0); }
    ;

%%

int yyerror (char *s)
{
    fprintf(stderr, "Error in line %d: %s.\n", getLineNumber(), s);
    exit(3);
}
