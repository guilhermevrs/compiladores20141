#ifndef GENCO_H
#define GENCO_H

#include "tacs.h"
#include "astree.h"

TAC* generateCode(ASTREE *node);
TAC* makeOpt( TAC* code0, TAC* code1, int type);
TAC *makeVarDec(HASH_NODE *symbol, TAC* literal);
TAC* makeFunc(HASH_NODE * symbol, TAC *param, TAC *declocal, TAC* bloco);

#endif