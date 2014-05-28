#ifndef GENCO_H
#define GENCO_H

#include "tacs.h"
#include "astree.h"

TAC* generateCode(ASTREE *node);

TAC* makeOpt( TAC* code0, TAC* code1, int type);

TAC* makeIf( TAC* code0, TAC* code1);

TAC* makeIfElse(TAC* code0, TAC* code1, TAC* code2);

TAC* makeFunc(HASH_CELL * symbol, TAC *param, TAC *declocal, TAC* bloco);

TAC* makeCallFunc(HASH_CELL *function, TAC *params);

TAC *makeParams(HASH_CELL *function, TAC *proximos);

TAC* makeLoop(TAC *code0, TAC* code1);

TAC* makeOutput( TAC* code0, TAC* proximo);

TAC *makeVetorAss(HASH_CELL *symbol, TAC* indice, TAC *expr);

TAC *makeVarDec(HASH_CELL *symbol, TAC* literal);

TAC *makeVetDec(HASH_CELL *symbol, TAC* tam);

TAC *makeVetDecInit(TAC* valor, TAC* proximo);

TAC *makePtrDec(HASH_CELL *symbol, TAC* literal);

TAC *makeArgss(TAC *param, TAC *paramlist);

TAC *makeVetorRead(HASH_CELL *symbol, TAC* indice);

#endif
