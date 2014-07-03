#include "astree.h"
#include "tacs.h"
#include "genco.h"


TAC* generateCode(ASTREE *node)
{

    int i;
    TAC* code[MAX_SONS];
    TAC* result = NULL;

    for(i = 0; i< MAX_SONS; ++i)
        code[i] = 0;

    for(i = 0; i< MAX_SONS; ++i)
        if(node->son[i])
            code[i] = generateCode(node->son[i]);

    switch(node->type)
    {
        case ASTREE_DEF_SYMBOL: result = tac_create(TAC_SYMBOL,node->symbol, NULL, NULL); break;
        case ASTREE_DEF_OUTPUT: result = makeOutput(code[0], code[1]); break;
        case ASTREE_DEF_INPUT: result = tac_create(TAC_INPUT, code[0]? code[0]->target:0, 0, 0); break;

        case ASTREE_DEF_BLOCK: result = code[0]; break;
        case ASTREE_DEF_SIMPLE_COMMAND: result = code[0]; break;
        case ASTREE_DEF_COMMAND_BLOCK: result = tac_join(code[0],code[1]); break;
        case ASTREE_DEF_PROGRAM: result = tac_join(code[0], code[1]); break;
        case ASTREE_DEF_DECL: result = makeVarDec(node->symbol, code[1], code[2]);  break;
        case ASTREE_DEF_DECL_VEC: result = makeVetDec(node->symbol, code[1]); break;
        case ASTREE_DEF_DECL_VEC_INIT: result = makeVetDecInit(node->symbol, code[0], code[1], code[2]); break;
        case ASTREE_DEF_INIT_VEC: result = makeVetInit(code[0], code[1]); break;        
        case ASTREE_DEF_DECL_POINTER: result = makePtrDec(code[1], code[2]); break;
        case ASTREE_DEF_FUNC: result = makeFunc(code[0],code[1],code[2],code[3]); break;
        case ASTREE_DEF_RETURN: result = tac_join(code[0],tac_create(TAC_RETURN,code[0]? code[0]->target : 0, NULL, NULL)); break;
        case ASTREE_DEF_PARAM: result = makeParams(code[1]? code[1]->target:0,code[2]); break;
        case ASTREE_DEF_PARAM_REF: result = makeArgss(code[0], code[1]); break;
        case ASTREE_DEF_FUNC_CALL: result = makeCallFunc(code[0]? code[0]->target : 0, code[1]) ; break;
        case ASTREE_DEF_IF: result = makeIf(code[0],code[1]); break;
        case ASTREE_DEF_LOOP: result = makeLoop(code[0],code[1]); break;
        case ASTREE_DEF_IFELSE: result = makeIfElse(code[0],code[1], code[2]); break;

        case ASTREE_DEF_ATTR: result = tac_join(code[1], tac_create(TAC_MOV, code[0]? code[0]->target:0, code[1]? code[1]->target:0, 0)); break;

        case ASTREE_DEF_ATTR_VEC: result = makeAttrVec(code[0],code[1],code[2]); break;

        case ASTREE_DEF_ADD: result = makeOpt(code[0],code[1],TAC_SOMA); break;
        case ASTREE_DEF_MUL: result = makeOpt(code[0],code[1],TAC_MULT); break;
        case ASTREE_DEF_SUB: result = makeOpt(code[0],code[1],TAC_SUB); break;
        case ASTREE_DEF_DIV: result = makeOpt(code[0],code[1],TAC_DIV); break;
        case ASTREE_DEF_OP_LE: result = makeOpt(code[0],code[1],TAC_LE); break;
        case ASTREE_DEF_OP_GE: result = makeOpt(code[0],code[1],TAC_GE); break;
        case ASTREE_DEF_OP_EQ: result = makeOpt(code[0],code[1],TAC_EQ); break;
        case ASTREE_DEF_OP_NE: result = makeOpt(code[0],code[1],TAC_NE); break;
        case ASTREE_DEF_OP_AND: result = makeOpt(code[0],code[1],TAC_AND); break;
        case ASTREE_DEF_OP_OR: result = makeOpt(code[0],code[1],TAC_OR); break;
        case ASTREE_DEF_LESS: result = makeOpt(code[0],code[1],TAC_LESS); break;
        case ASTREE_DEF_GREATER: result = makeOpt(code[0],code[1],TAC_GREAT); break;
        
        default:
            result = tac_join(tac_join(tac_join(code[0],code[1]),code[2]),code[3]);
        break;
    }

    return result;

}

TAC* makeAttrVec(TAC* code0, TAC* code1, TAC* code2)
{
    TAC *nova = NULL;

    nova = tac_create(TAC_VET_WRITE, code0? code0->target: 0, code1? code1->target: 0, code2? code2->target: 0);

    nova = tac_join(code0, nova);
    nova = tac_join(code1, nova);
    nova = tac_join(code2, nova);

    return nova;

}

TAC* makeOpt( TAC* code0, TAC* code1, int type)
{
    TAC *nova = NULL;

    nova = tac_create(type, makeTemp(), code0? code0->target: 0, code1? code1->target: 0);
    nova = tac_join(code0, nova);
    nova = tac_join(code1, nova);

    return nova;

}

TAC *makeVarDec(HASH_NODE *symbol, TAC* var, TAC* literal)
{

    TAC *newTac;


    newTac = tac_create(TAC_VARDEC, var? var->target: 0, literal? literal->target: 0, 0);


    return tac_join(literal,newTac);

}

TAC* makeFunc(TAC* type, TAC* identifier, TAC* param, TAC* command)
{
    TAC *begin;
    TAC *endfunc;

    begin = tac_create(TAC_BEGINFUN, identifier? identifier->target:0, NULL, NULL);


    param = tac_join(begin, param);
    command = tac_join(param, command);

    endfunc =  tac_create(TAC_ENDFUN, identifier? identifier->target:0, NULL, NULL);

    endfunc = tac_join(command, endfunc);

    return endfunc;
}

TAC *makeVetDec(HASH_NODE *symbol, TAC* tam)
{
    
    TAC *newTac;
    
    
    newTac = tac_create(TAC_VETDEC, tam? tam->target :0, symbol, 0);
    
     
    return tac_join(tam,newTac);

}

TAC* makeVetDecInit(HASH_NODE *symbol, TAC* type, TAC* identifier, TAC* init)
{
    
    TAC *newTac;
    
    newTac = tac_create(TAC_VETDECINIT, identifier? identifier->target :0, symbol, NULL);

    init = tac_join(newTac, init);
     
    return init;

}

TAC* makeVetInit(TAC* code0, TAC* code1)
{
    TAC *nova = NULL;

    nova = tac_create(TAC_VET_READ, code0? code0->target: 0, NULL, NULL);
    
    return tac_join(nova, code1);
}

TAC *makePtrDec(TAC* symbol, TAC* literal)
{
    
    TAC *newTac;
    
    
    newTac = tac_create(TAC_PTRDEC, symbol? symbol->target :0, literal? literal->target :0, 0);
    
     
    return tac_join(literal,newTac);
}

TAC *makeParams(HASH_NODE* argumento, TAC* proximos)
{
    TAC *nova;
 
    nova = tac_create(TAC_PARAM, argumento,  NULL, NULL);

    return tac_join(nova, proximos);
}

TAC *makeArgss(TAC *param, TAC *paramlist)
{
    TAC *nova;
        
    nova = tac_create(TAC_ARG, param? param->target : 0, NULL, NULL);

    return tac_join(nova, paramlist);
}

TAC* makeOutput( TAC* code0, TAC* proximo)
{
    TAC *nova = NULL;
    
    nova = tac_create(TAC_OUTPUT, code0? code0->target : 0,  0, 0);
    
    nova = tac_join(nova, proximo);

    return nova;

}

TAC* makeLoop(TAC *code0, TAC* code1) 
{
    HASH_NODE *targetBegin, *targetEnd;
    TAC *ifz, *jmp, *labelEnd, *labelBegin;
    targetBegin = makeLabel();
    targetEnd = makeLabel();

    labelBegin = tac_create(TAC_LABEL, targetBegin, NULL, NULL);
    
    code0 = tac_join(labelBegin, code0);
    
    ifz = tac_create(TAC_IFZ, code1?code1->target:0, targetEnd, NULL);
    
    ifz->prev = code0;
    code1 = tac_join(ifz,code1);
    
    jmp = tac_create(TAC_JUMP, targetBegin, NULL, NULL);
    
    jmp->prev = code1;
     
    return jmp;
}

TAC* makeCallFunc(HASH_NODE *function, TAC *params)
{

    TAC *nova;
    
    nova = tac_create(TAC_CALL, function, NULL, NULL);   

    return tac_join(params,nova);
}

TAC* makeIf( TAC* code0, TAC* code1)
{
    TAC* nova1 = NULL;
    TAC* nova2 = NULL;

    HASH_NODE* labelFinal;

    labelFinal = makeLabel();
    
    nova1 = tac_create(TAC_IFZ, code0 ? code0->target : 0, labelFinal, 0); //se falso, pula pro label final
    
    nova1->prev = code0;
    code1 = tac_join(nova1,code1);

    nova2 = tac_create(TAC_LABEL, labelFinal, 0, 0 );

    nova2->prev = code1;

    return nova2;
}

TAC* makeIfElse(TAC* code0, TAC* code1, TAC* code2)
{
    HASH_NODE *targetElse = makeLabel();
    HASH_NODE *targetEnd = makeLabel();

    TAC * jumpElse = tac_create(TAC_IFZ, code0?code0->target:0, targetElse, 0);
    TAC * jumpEnd = tac_create(TAC_JUMP, targetEnd, 0,0);

    TAC* labelElse = tac_create(TAC_LABEL, targetElse, 0, 0);
    TAC* labelEnd = tac_create(TAC_LABEL, targetEnd, 0, 0);

    return tac_join(tac_join(tac_join(tac_join(tac_join(tac_join(code0 ,jumpElse), code1), jumpEnd), labelElse), code2), labelEnd);

}