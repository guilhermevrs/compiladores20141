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
HASH_NODE* symbol;
};

%token KW_WORD      
%token KW_BOOL      
%token KW_BYTE      
%token KW_IF        
%token KW_THEN      
%token KW_ELSE      
%token KW_LOOP      
%token KW_INPUT     
%token KW_RETURN   
%token KW_OUTPUT    

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token<symbol> UNDEFINED   		0
%token<symbol> LIT_INTEGER   	1
%token<symbol> LIT_FLOATING  	2
%token<symbol> LIT_TRUE      	3
%token<symbol> LIT_FALSE     	4
%token<symbol> LIT_CHAR      	5
%token<symbol> LIT_STRING    	6
%token<symbol> TK_IDENTIFIER 	7

%token TOKEN_ERROR   290

%left OPERATOR_AND OPERATOR_OR
%nonassoc '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'



%%

/* .. Um programa na linguagem de e um conjunto de declarações de variáveis globais e um conjunto de funções .. */
programa 
		: declaracao_glob programa
	        |
		;

/* ..Os comandos podem ser atribuiçoes, cont. de fluxo, input, output, return ou comando vazio.. */         
cmd
		: TK_IDENTIFIER '=' expr
		| TK_IDENTIFIER '[' expr ']' '=' expr
		| KW_INPUT TK_IDENTIFIER
		| KW_OUTPUT outp
		| KW_RETURN expr
		| KW_IF '(' expr ')' KW_THEN cmd
		| KW_IF '(' expr ')' KW_THEN cmd KW_ELSE cmd
		| KW_LOOP '(' expr ')' cmd
		| bloco
		;

/* ..Outputs podem ser uma expressao, ou uma sequencia delas separadas por ;.. */

outp		: expr
		| expr ',' outp
		;

cmds
		: cmd ';' cmds
		|
		;
  
expr    
		: primary_expression
		| TK_IDENTIFIER '[' expr ']'	
		| TK_IDENTIFIER '(' params_func ')'
		| TK_IDENTIFIER '(' expr ')'
		| expr OPERATOR_LE expr
		| expr OPERATOR_GE expr
		| expr OPERATOR_EQ expr
		| expr OPERATOR_NE expr
		| expr OPERATOR_AND expr
		| expr OPERATOR_OR expr
		| expr '>' expr
		| expr '<' expr
		| expr '+' expr
		| expr '-' expr
		| expr '*' expr
		| expr '/' expr
		| '&' TK_IDENTIFIER
		| '*' TK_IDENTIFIER
		| '(' expr ')'
        	;

params_func     
		: primary_expression ',' params_func
		| primary_expression
		|
		;

/* ..As var são declaradas com a palavra de seu tipo, seguida de seu nome, dois pontos e seu valor.. */ 
declaracao_glob
		: declaracao 
		;

declaracao
		: espec_tipo  TK_IDENTIFIER ':' CONSTANT ';'
		| espec_tipo  TK_IDENTIFIER '[' LIT_INTEGER ']' ':' VETOR ';'
		| espec_tipo  TK_IDENTIFIER '[' LIT_INTEGER ']' ';'
		| espec_tipo  '$' TK_IDENTIFIER ':' CONSTANT	 ';'	
		| funcao
		;
		
declaracao_local
		: declaracao_nglob ';' declaracao_local
		|
		;

declaracao_nglob
		: espec_tipo  TK_IDENTIFIER ':' CONSTANT
		| espec_tipo  '$' TK_IDENTIFIER ':' CONSTANT
		;

/* ..Um bloco de cmd eh def entre chaves, e consiste em uma seq, possivelmente vazia, de cmd simples seguidos de ;..*/ 
bloco
		: '{' cmds  '}'
		;

/* ..Variáveis podem ser dos tipos word, bool ou byte.. */		
espec_tipo
		: KW_WORD
		| KW_BOOL
		| KW_BYTE
		;

VETOR
		: CONSTANT VETOR
        	|
       		;
/* ..Constantes podem ser dos tipos das variaveis.. */			
CONSTANT
		: LIT_INTEGER
		| LIT_TRUE
		| LIT_FALSE
		| LIT_CHAR
		| LIT_STRING
		;

primary_expression
		: TK_IDENTIFIER	
		| CONSTANT
		;

/* .. onde cada parâmetro é definido por tipo, nome e não podem! ser do tipo vetor .. */
parametro     
		: espec_tipo TK_IDENTIFIER
		;


/* .. de uma lista, possivelmente vazia, entre parênteses, de parâmetros de entrada, separados por vírgula .. */
parametros    
		: ',' parametro parametros
		|
		;

parametros2     : parametro parametros
		| 
		;	

	
/* .. O cabeçalho consiste do tipo do valor de retorno , do nome da função   .. */
funcao
		: espec_tipo TK_IDENTIFIER '(' parametros2 ')'  declaracao_local bloco
		;

%%

int yyerror( char* str)
{
	fflush(stderr);
	fprintf(stderr,"ERRO: \"%s\"\t Linha: %d\n", str, getLineNumber());
	exit(3);
}
