#include "tacs.h"

TAC* tac_create(int type, HASH_NODE *target, HASH_NODE *op1, HASH_NODE *op2)
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

TAC* tac_join (TAC *l1, TAC *l2)
{

    TAC* tac = NULL;

    if(!l1)
        return l2;
    if(!l2)
        return l1;

    for(tac = l2; tac->prev; tac = tac->prev);
    tac->prev = l1;
    return l2;
}

void tac_print_single (TAC *t)
{

    if (!t)
        return;

    if (t->type == TAC_SYMBOL || t->type == TAC_VAR)
        return;


    printf( "TAC(");


    switch(t->type)
    {
        case TAC_VARDEC: printf("TAC_VARDEC"); break;
        case TAC_VETDEC: printf("TAC_VETDEC"); break;
        case TAC_PTRDEC: printf( "TAC_PTRDEC"); break;

        case TAC_BEGINFUN: printf("TAC_BEGINFUN"); break;
        case TAC_ENDFUN: printf("TAC_ENDFUN"); break;
        case TAC_RETURN: printf("TAC_RETURN"); break;
        case TAC_INPUT: printf( "TAC_INPUT"); break;
        case TAC_OUTPUT: printf("TAC_OUTPUT"); break;
        case TAC_MOV: printf("TAC_MOV"); break;
        case TAC_SOMA: printf("TAC_SOMA"); break;
        case TAC_MULT: printf("TAC_MULT"); break;
        case TAC_SUB: printf("TAC_SUB"); break;
        case TAC_DIV: printf("TAC_DIV"); break;
        case TAC_PARAM: printf( "TAC_PARAM"); break;
        case TAC_ARG: printf("TAC_ARG"); break;       
        case TAC_IFZ: printf("TAC_IFZ"); break;
        case TAC_CALL: printf("TAC_CALL"); break;
        case TAC_LABEL: printf("TAC_LABEL"); break;
        case TAC_JUMP: printf("TAC_JUMP"); break;

        case TAC_SYMBOL: printf("TAC_SYMBOL"); break;
        case TAC_LE: printf("TAC_LE"); break;
        case TAC_GE: printf("TAC_GE"); break;
        case TAC_EQ: printf("TAC_EQ"); break;
        case TAC_NE: printf("TAC_NE"); break;
        case TAC_AND: printf("TAC_AND"); break;
        case TAC_OR: printf("TAC_OR"); break;
        case TAC_LESS: printf("TAC_LESS"); break;
        case TAC_GREAT: printf("TAC_GREAT"); break;

        default: printf("UNKNOWN"); break;
    }

    if(t->target)
        printf(", %s ", t->target->text);
    else
        printf(", ");

    if(t->op1)
        printf(", %s ", t->op1->text);
    else
        printf(", ");

    if(t->op2)
        printf(", %s ", t->op2->text);
    else
        printf(", ");

    printf(")\n");
}

void tac_print_list (TAC *t)
{

    TAC* tac = NULL;

    for(tac = t ; tac; tac= tac->next)
        tac_print_single(tac);
}

TAC* tac_reverse(TAC *last)
{
    TAC *first = NULL;

    if(!last){
        return NULL;
    }

    for(first = last; first->prev; first = first->prev)
        first->prev->next = first;
    return first;

}