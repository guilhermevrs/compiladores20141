/*
// UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 6
//
// Alunos: Guilherme Schwade e Guilherme Pretto.
//
// Matrículas: 192332 e 213991.
*/

#ifndef GENCO_H
#define GENCO_H

#include "tacs.h"
#include "astree.h"

TAC* generateCode(ASTREE *node);
TAC* makeOpt( TAC* code0, TAC* code1, int type);
TAC *makeVarDec(HASH_NODE *symbol, TAC* var, TAC* literal);
TAC *makeVetDec(HASH_NODE *symbol, TAC* tam);

TAC* makeVetDecInit(HASH_NODE *symbol, TAC* type, TAC* identifier, TAC* init);
TAC* makeVetInit(TAC* code0, TAC* code1);
TAC* makeAttrVec(TAC* code0, TAC* code1, TAC* code2);

TAC *makePtrDec(TAC* symbol, TAC* literal);
TAC* makeFunc(TAC* type, TAC* identifier, TAC* param, TAC* command);
TAC* makeOutput( TAC* code0, TAC* proximo);
TAC* makeCallFunc(HASH_NODE *function, TAC *params);
TAC *makeParams(HASH_NODE* argumento, TAC* proximos);
TAC *makeArgss(TAC *param, TAC *paramlist);
TAC* makeLoop(TAC *code0, TAC* code1);
TAC* makeIf( TAC* code0, TAC* code1);
TAC* makeIfElse(TAC* code0, TAC* code1, TAC* code2);


#endif