%{
//
//UFRGS - Compiladores B - Marcelo Johann - 2012/1 - Etapa 4
//
//Alunos: Daniel Henrique Grehs e Victoria Ramos Pires.
//
//Matrículas: 213998 e 213997.
//
//

#include <stdio.h>

#include <stdlib.h>
//#include "hash_table.h" pois já incluímos o astree q possue a hash
#include "astree.h"
struct astreenode *root;
#include "semantic.h"


%}  

%union
  {
  HASH_NODE *symbol;
  struct astreenode *ast;
  };

%type<ast> programa
%type<ast> declaracao_glob
%type<ast> declaracao
%type<ast> funcao
%type<ast> espec_tipo
%type<ast> parametros
%type<ast> parametro
%type<ast> blocks
%type<ast> bloco
%type<ast> cmd
%type<ast> outp
%type<ast> expr
%type<ast> expr2
%type<ast> primary_expression
%type<ast> vet
%type<ast> CONSTANT
%type<ast> params_func
%type<ast> contr_fluxo
%type<ast> cmds

%token KW_INTEGER    256
%token KW_FLOATING   257
%token KW_BOOLEAN    258
%token KW_CHARACTER  259
%token KW_DECLARE    260
%token KW_IF         261
%token KW_THEN       262
%token KW_ELSE       263
%token KW_WHILE      264
%token KW_DO         265
%token KW_INPUT      266
%token KW_RETURN     267
%token KW_OUTPUT     268

%token OPERATOR_LE   270
%token OPERATOR_GE   271
%token OPERATOR_EQ   272
%token OPERATOR_NE   273
%token OPERATOR_AND  274
%token OPERATOR_OR   275

%token<symbol> UNDEFINED   	0
%token<symbol> LIT_INTEGER   	1
%token<symbol> LIT_FLOATING  	2
%token<symbol> LIT_TRUE      	3
%token<symbol> LIT_FALSE     	4
%token<symbol> LIT_CHAR      	5
%token<symbol> LIT_STRING    	6
%token<symbol> TK_IDENTIFIER 	7

%token TOKEN_ERROR   290

%left OPERATOR_AND OPERATOR_OR
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'
%left '=' 
%left '!'

%%

/* .. Um programa na linguagem de e um conjunto de declarações de variáveis globais e um conjunto de funções .. */
programa 
		: declaracao_glob {root = $1; checkDeclaration(root); checkUndeclared(); checkUtilization(root, root);/* COLOCAR O printHashTable(); AQUI, mas precisa :/ */astPrintTree(root); }
		;


/* ..As var são declaradas com a palavra reservada “declare”, seguida de seu nome, dois pontos e seu tipo.. */ 
declaracao_glob
		: declaracao ';' declaracao_glob {$$ = astCreate(AST_declaracao_glob, 0, $1, $3, 0, 0);}
		| funcao ';' declaracao_glob      {$$ = astCreate(AST_declaracao_glob, 0, $1, $3, 0, 0);}
	    	| {$$ = 0;}
		;

declaracao
		: KW_DECLARE TK_IDENTIFIER ':' espec_tipo vet {$$ = astCreate(AST_declaracao,$2,$4,$5, 0, 0); $2->content.dataType = dataTypeMap($4->type);}
		| KW_DECLARE TK_IDENTIFIER ':' espec_tipo {$$ = astCreate(AST_declaracao,$2,$4,0, 0, 0); $2->content.dataType = dataTypeMap($4->type);}
		;

/* .. O cabeçalho consiste do nome da função, dois pontos, o tipo do valor de retorno .. */
funcao
		: TK_IDENTIFIER ':' espec_tipo  '(' parametros ')'  blocks {$$ = astCreate(AST_funcao, $1, $3, $5, $7, 0); $1->content.dataType = dataTypeMap($3->type);}
		;
		
/* ..Variáveis podem ser dos tipos integer, floating, boolean ou character.. */		
espec_tipo
		: KW_INTEGER    {$$ = astCreate(AST_KW_INTEGER, 0, 0, 0, 0, 0);}
		| KW_FLOATING   {$$ = astCreate(AST_KW_FLOATING, 0, 0, 0, 0, 0);}
		| KW_BOOLEAN    {$$ = astCreate(AST_KW_BOOLEAN, 0, 0, 0, 0, 0);}
		| KW_CHARACTER  {$$ = astCreate(AST_KW_CHARACTER, 0, 0, 0, 0, 0);}
		;

/* .. de uma lista, possivelmente vazia, entre parênteses, de parâmetros de entrada, separados por vírgula .. */
parametros    
		: parametro		   {$$ = astCreate(AST_vaiParaParametros,0, $1, 0, 0, 0);}
		| parametro ',' parametros {$$ = astCreate(AST_parametros,0, $1, $3, 0, 0);}
		| {$$ = 0;}
		;

/* .. onde cada parâmetro é definido por nome, dois pontos e tipo, e não podem! ser do tipo vetor .. */
parametro     
		: TK_IDENTIFIER ':' espec_tipo {$$ = astCreate(AST_parametro, $1, $3, 0, 0, 0); $1->content.dataType = dataTypeMap($3->type);}
		;
		
blocks
		: bloco		{$$ = astCreate(AST_blocks, 0, $1, 0, 0, 0);}
		| cmd		{$$ = astCreate(AST_blocks, 0, $1, 0, 0, 0);}
		| {$$ = 0;}
		;

/* ..Um bloco de cmd eh def entre chaves, e consiste em uma seq, possivelmente vazia, de cmd simples seguidos de ;..*/ 
bloco
		: '{' cmds  '}' {$$ = astCreate(AST_bloco, 0, $2, 0, 0, 0);}
		;
		
/* ..Os comandos podem ser atribuiçoes, cont. de fluxo, input, output, return ou comando vazio.. */         
cmd
		: declaracao		 {$$ = astCreate(AST_cmd, 0, $1, 0, 0, 0);}
		| contr_fluxo		 {$$ = astCreate(AST_contr_fluxo, 0, $1, 0, 0, 0);}
		| KW_INPUT TK_IDENTIFIER {$$ = astCreate(AST_KW_INPUT, $2, 0, 0, 0, 0);}
		| KW_OUTPUT outp	 {$$ = astCreate(AST_KW_OUTPUT,0, $2, 0, 0, 0);}
		| KW_RETURN expr	 {$$ = astCreate(AST_KW_RETURN,0, $2, 0, 0, 0);}
		| expr2 '=' expr	 {$$ = astCreate(AST_IGUAL, 0, $1,$3, 0, 0);}
		| TK_IDENTIFIER '(' params_func ')' {$$ = astCreate(AST_exprComTK_IDENTIFIER,$1, $3, 0, 0, 0);}
		;

/* ..Outputs podem ser uma expressao, ou uma sequencia delas separadas por ;.. */

outp	
		: expr		    {$$ = astCreate(AST_outp,0, $1, 0, 0, 0);}
		| expr ',' outp     {$$ = astCreate(AST_outp2,0, $1, $3, 0, 0);}
		;
		
expr    
 		: TK_IDENTIFIER {$$ = astCreate(AST_TK_IDENTIFIER,$1, 0, 0, 0, 0);}
		| LIT_INTEGER     {$$ = astCreate(AST_LIT_INTEGER,$1, 0, 0, 0, 0);}
		| LIT_FLOATING    {$$ = astCreate(AST_LIT_FLOATING,$1, 0, 0, 0, 0);}
		| LIT_TRUE	  {$$ = astCreate(AST_LIT_TRUE,$1, 0, 0, 0, 0);}
		| LIT_FALSE       {$$ = astCreate(AST_LIT_FALSE,$1, 0, 0, 0, 0);}
		| LIT_CHAR        {$$ = astCreate(AST_LIT_CHAR,$1, 0, 0, 0, 0);}
		| LIT_STRING      {$$ = astCreate(AST_LIT_STRING,$1, 0, 0, 0, 0);}
		| TK_IDENTIFIER '(' params_func ')' {$$ = astCreate(AST_exprComTK_IDENTIFIER,$1, $3, 0, 0, 0);}
		| '(' expr ')'		  {$$ = astCreate(AST_exprComParent, 0, $2, 0, 0, 0);}
		| expr '+' expr 	  {$$ = astCreate(AST_ADD, 0, $1,$3, 0, 0);}
		| expr '-' expr		  {$$ = astCreate(AST_SUB, 0, $1,$3, 0, 0);}
		| expr '*' expr		  {$$ = astCreate(AST_MUL, 0, $1,$3, 0, 0);}
		| expr '/' expr		  {$$ = astCreate(AST_DIV, 0, $1,$3, 0, 0);}
		| '!' expr		  {$$ = astCreate(AST_NEG, 0, $2, 0, 0, 0);}
		| expr OPERATOR_AND expr  {$$ = astCreate(AST_OPERATOR_AND, 0, $1,$3, 0, 0);}
		| expr OPERATOR_OR expr   {$$ = astCreate(AST_OPERATOR_OR, 0, $1,$3, 0, 0);}
		| expr OPERATOR_LE expr   {$$ = astCreate(AST_OPERATOR_LE, 0, $1,$3, 0, 0);}
		| expr OPERATOR_GE expr	  {$$ = astCreate(AST_OPERATOR_GE, 0, $1,$3, 0, 0);}
		| expr OPERATOR_EQ expr   {$$ = astCreate(AST_OPERATOR_EQ, 0, $1,$3, 0, 0);}
		| expr OPERATOR_NE expr	  {$$ = astCreate(AST_OPERATOR_NE, 0, $1,$3, 0, 0);}
		| expr '>' expr		  {$$ = astCreate(AST_MAIOR, 0, $1,$3, 0, 0);}
		| expr '<' expr           {$$ = astCreate(AST_MENOR, 0, $1,$3, 0, 0);}
		| TK_IDENTIFIER '[' expr ']'       {$$ = astCreate(AST_TK_IDENTIFIER_VET, $1, $3, 0, 0, 0);}
		;

/*..esses só podem aparecer no expr antes da oper lógica ou igualdade..*/
expr2
		: TK_IDENTIFIER 		{$$ = astCreate(AST_TK_IDENTIFIER,$1, 0, 0, 0, 0);}
		| TK_IDENTIFIER '[' expr ']'       {$$ = astCreate(AST_TK_IDENTIFIER_VET, $1, $3, 0, 0, 0);}
		;
vet
		: '[' LIT_INTEGER ']' {$$ = astCreate(AST_vet,$2, 0, 0, 0, 0);}
		;

primary_expression
		: TK_IDENTIFIER {$$ = astCreate(AST_TK_IDENTIFIER,$1, 0, 0, 0, 0);}
		| CONSTANT      {$$ = astCreate(AST_primary_expression, 0, $1,0, 0, 0);}
		;
		
/* ..Constantes podem ser dos tipos das variaveis.. */			
CONSTANT
		: LIT_INTEGER     {$$ = astCreate(AST_LIT_INTEGER,$1, 0, 0, 0, 0);}
		| LIT_FLOATING    {$$ = astCreate(AST_LIT_FLOATING,$1, 0, 0, 0, 0);}
		| LIT_TRUE	  {$$ = astCreate(AST_LIT_TRUE,$1, 0, 0, 0, 0);}
		| LIT_FALSE       {$$ = astCreate(AST_LIT_FALSE,$1, 0, 0, 0, 0);}
		| LIT_CHAR        {$$ = astCreate(AST_LIT_CHAR,$1, 0, 0, 0, 0);}
		| LIT_STRING      {$$ = astCreate(AST_LIT_STRING,$1, 0, 0, 0, 0);}
		;

params_func     
		: primary_expression ',' params_func {$$ = astCreate(AST_params_func,0, $1, $3, 0, 0);}
		| primary_expression		     {$$ = astCreate(AST_primary_expression,0, $1, 0, 0, 0);}
		| {$$ = 0;}
		;
		
contr_fluxo   
		: KW_IF '(' expr ')' KW_THEN blocks                {$$ = astCreate(AST_KW_IF, 0, $3,$6, 0, 0);}
		| KW_IF '(' expr ')' KW_THEN blocks KW_ELSE blocks {$$ = astCreate(AST_KW_IF_ELSE, 0, $3,$6,$8, 0);}
		| KW_WHILE '(' expr ')' blocks			   {$$ = astCreate(AST_KW_WHILE, 0, $3,$5, 0, 0);}
		| KW_DO blocks KW_WHILE '(' expr ')'		   {$$ = astCreate(AST_KW_DO_WHILE, 0, $2,$5, 0, 0);}
		;
				
cmds
		: cmd		  {$$ = astCreate(AST_cmd,0, $1, 0, 0, 0);}
		| cmd ';' cmds	  {$$ = astCreate(AST_cmds,0, $1, $3, 0, 0);}
		| {$$ = 0;}
		;

%%

int yyerror( char* str)
{
	fflush(stderr);
	fprintf(stderr,"ERRO: \"%s\"\t Linha: %d\n", str, getLineNumber());
	exit(3);
}
