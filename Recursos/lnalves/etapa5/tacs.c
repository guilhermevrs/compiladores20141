
#include <stdlib.h>
#include <stdio.h>
#include "tacs.h"

TAC* tac_create(int type, HASH_CELL *target, HASH_CELL *op1, HASH_CELL *op2)
{
	TAC *tac = NULL;

	tac = (TAC*)calloc(1, sizeof(TAC));
	tac->type = type;
	tac->target = target;
	tac->op1 = op1;	
	tac->op2 = op2;
	tac->prev = NULL;
	tac->next = NULL;

	return tac;
}

void tac_print_single (TAC *t)
{
		
	if (!t)
		return;
	
	if (t->type == TAC_SYMBOL || t->type == TAC_VAR)
		return;
	

	fprintf(stderr, "TAC(");


	switch(t->type)
	{
		case TAC_SOMA: fprintf(stderr,"TAC_SOMA"); break;
		
		case TAC_SUB: fprintf(stderr,"TAC_SUB"); break;

		case TAC_MULT: fprintf(stderr,"TAC_MULT"); break;

		case TAC_DIV: fprintf(stderr,"TAC_DIV"); break;

		case TAC_SYMBOL: fprintf(stderr,"TAC_SYMBOL"); break;

		case TAC_MOV: fprintf(stderr,"TAC_MOV"); break;

		//case TAC_VAR: return;/*fprintf(stderr,"TAC_VAR");*/ break;

		case TAC_LE: fprintf(stderr,"TAC_LE"); break;
		case TAC_GE: fprintf(stderr,"TAC_GE"); break;
		case TAC_EQ: fprintf(stderr,"TAC_EQ"); break;
		case TAC_NE: fprintf(stderr,"TAC_NE"); break;
		case TAC_AND: fprintf(stderr,"TAC_AND"); break;
		case TAC_OR: fprintf(stderr,"TAC_OR"); break;
		case TAC_LESS: fprintf(stderr,"TAC_LESS"); break;
		case TAC_GREAT: fprintf(stderr,"TAC_GREAT"); break;

		case TAC_IFZ: fprintf(stderr,"TAC_IFZ"); break;
		
		case TAC_LABEL: fprintf(stderr,"TAC_LABEL"); break;
		
		case TAC_JUMP: fprintf(stderr,"TAC_JUMP"); break;
		
		case TAC_BEGINFUN: fprintf(stderr,"TAC_BEGINFUN"); break;
		
		case TAC_ENDFUN: fprintf(stderr,"TAC_ENDFUN"); break;

		case TAC_CALL: fprintf(stderr,"TAC_CALL"); break;

		case TAC_ARG: fprintf(stderr,"TAC_ARG"); break;

		case TAC_RETURN: fprintf(stderr,"TAC_RETURN"); break;

		case TAC_OUTPUT: fprintf(stderr,"TAC_OUTPUT"); break;

		case TAC_VETW: fprintf(stderr,"TAC_VETWRITE"); break;

		case TAC_VARDEC: fprintf(stderr,"TAC_VARDEC"); break;

		case TAC_VETDEC: fprintf(stderr,"TAC_VETDEC"); break;

		case TAC_VETDECINIT: fprintf(stderr,"TAC_VETDECINI"); break;

		case TAC_PTRDEC: fprintf(stderr, "TAC_PTRDEC"); break;

		case TAC_INPUT: fprintf(stderr, "TAC_INPUT"); break;

		case TAC_PTRADRESS: fprintf(stderr, "TAC_PTRADRESS"); break;

		case TAC_PTRVALUE: fprintf(stderr, "TAC_PTRVALUE"); break;

		case TAC_PARAM: fprintf(stderr, "TAC_PARAM"); break;

		case TAC_VETREAD: fprintf(stderr, "TAC_VETREAD"); break;
		
		default: fprintf(stderr,"UNKNOWN"); break;
	}
	
	if(t->target)
		fprintf(stderr,", %s ", t->target->lexem);
	else
		fprintf(stderr,", ");
	
	if(t->op1)
		fprintf(stderr,", %s ", t->op1->lexem);
	else
		fprintf(stderr,", ");

	if(t->op2)
		fprintf(stderr,", %s ", t->op2->lexem);
	else
		fprintf(stderr,", ");
	
	fprintf(stderr,")\n");
}

void tac_print_list (TAC *t)
{
		
	TAC* tac = NULL;
	
	for(tac = t ; tac; tac= tac->next)
		tac_print_single(tac);


}

TAC* tac_join (TAC *l1, TAC *l2)
{

	TAC* tac = NULL;

	if(!l1)
		return l2;
	if(!l2)
		return l1;
	
	

	for(tac = l2; tac->prev; tac = tac->prev);
	//tac = l2;

	//while(tac->prev) { //PROBLEM HERE! ¬¬
	//	fprintf(stderr,"oinowhile\n");
	//	tac = tac->prev;
	//	if(!tac)
	//		break;
	//}
	
	tac->prev = l1;
	//l1->next = l2;
	return l2;
	
}
/*
TAC * tacJoin(TAC *l1, TAC *l2) {
	if(!l1) return l2;
	if(!l2) return l1;

	TAC *t = l2;

	while(t->prev) {
		t = t->prev;
	}

	t->prev = l1;
	l1->next = l2;
	return l2;
}
*/
TAC* tac_reverse(TAC *last)
{
	TAC *first = NULL;
	
		

	if(!last)
		return NULL;
	
	for(first = last; first->prev; first = first->prev)
		first->prev->next = first;
	return first;



}

