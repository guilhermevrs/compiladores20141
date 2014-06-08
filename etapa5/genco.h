#ifndef GENCO_H
#define GENCO_H

#include "tacs.h"
#include "astree.h"

TAC* generateCode(ASTREE *node);
TAC* makeOpt( TAC* code0, TAC* code1, int type);
TAC *makeVarDec(HASH_NODE *symbol, TAC* var, TAC* literal);
TAC *makeVetDec(HASH_NODE *symbol, TAC* tam);
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