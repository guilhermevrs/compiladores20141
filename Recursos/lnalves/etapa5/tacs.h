#ifndef TACS_H
#define TACS_H

#include "hash.h"

#define TAC_SYMBOL 1
#define TAC_SOMA 2
#define TAC_SUB 3
#define TAC_MULT 4
#define TAC_DIV 5
#define TAC_VAR 6

#define TAC_LE 7
#define TAC_GE 8
#define TAC_EQ 9
#define TAC_NE 10
#define TAC_AND 11
#define TAC_OR 12
#define TAC_LESS 13
#define TAC_GREAT 14

#define TAC_IFZ 15
#define TAC_LABEL 16
#define TAC_JUMP 17

#define TAC_BEGINFUN 18
#define TAC_ENDFUN 19

#define TAC_CALL 20
#define TAC_ARG 21

#define TAC_RETURN 22
#define TAC_OUTPUT 23

#define TAC_VETW 24
#define TAC_VARDEC 25

#define TAC_VETDEC 26
#define TAC_VETDECINIT 27
#define TAC_PTRDEC 28

#define TAC_INPUT 29

#define TAC_PTRADRESS 30
#define TAC_PTRVALUE 31

#define TAC_PARAM 32

#define TAC_MOV 33

#define TAC_VETREAD 34

typedef struct tac_node
{
	int type;
	HASH_CELL *target, *op1, *op2;
	struct tac_node *prev, *next;	

}TAC;

TAC* tac_create(int type, HASH_CELL *target, HASH_CELL *op1, HASH_CELL *op2);

void tac_print_single (TAC *t);

void tac_print_list (TAC *t);

TAC* tac_join (TAC *l1, TAC *l2);

TAC* tac_reverse(TAC *last);

#endif
