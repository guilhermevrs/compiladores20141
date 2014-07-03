
#ifndef GENASM_HEADER
#define GENASM_HEADER

#include "tacs.h"
#include <stdio.h>
#include "hash.h"
#include <string.h>
#include <stdlib.h>

void gen_asm(TAC *first);
void gen_code (TAC *t, FILE *outasm);
void gen_outputs(FILE *outasm, TAC *first);
void gen_decs(FILE *outasm, TAC *first);

#endif