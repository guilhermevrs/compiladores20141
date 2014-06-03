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
        case ASTREE_DEF_SYMBOL: result = tac_create(ASTREE_DEF_SYMBOL,node->symbol, NULL, NULL); break;
        case ASTREE_DEF_ADD: result = makeOpt(code[0],code[1],TAC_SOMA); break;
        case ASTREE_DEF_DECL: result = makeVarDec(node->symbol, code[1]);  break;
        case ASTREE_DEF_BLOCK: result = code[0]; break;
        case ASTREE_DEF_FUNC: makeFunc(node->symbol,code[1],code[2],code[3]); break;
        case ASTREE_DEF_ATTR: result = tac_join(code[0],
                        tac_create(TAC_MOV, node->symbol, code[0]? code[0]->target : 0, 0)); break;
        case ASTREE_DEF_RETURN: result = tac_join(code[0],tac_create(TAC_RETURN,code[0]? code[0]->target : 0, NULL, NULL)); break;
        case ASTREE_DEF_COMMAND_BLOCK: result = tac_join(code[0],code[1]); break;
        case ASTREE_DEF_PROGRAM: result = tac_join(code[0], code[1]); break;
        case ASTREE_DEF_SIMPLE_COMMAND: result = tac_join(code[0], code[1]); break;
        default:
            printf("\nType:%d\n", node->type);
            result = tac_join(tac_join(tac_join(code[0],code[1]),code[2]),code[3]);
        break;
    }

    return result;

}

TAC* makeOpt( TAC* code0, TAC* code1, int type)
{
    TAC *nova = NULL;

    nova = tac_create(type, makeTemp(),code0? code0->target : 0, code1? code1->target: 0);
    nova = tac_join(code0, nova);
    nova = tac_join(code1, nova);

    return nova;

}

TAC *makeVarDec(HASH_NODE *symbol, TAC* literal)
{

    TAC *newTac;


    newTac = tac_create(TAC_VARDEC, symbol, literal? literal->target :0, 0);


    return tac_join(literal,newTac);

}

TAC* makeFunc(HASH_NODE * symbol, TAC *param, TAC *declocal, TAC* bloco)
{
    TAC *begin;
    TAC *endfunc;

    begin = tac_create(TAC_BEGINFUN, symbol, NULL, NULL);


    param = tac_join(begin, param);
    declocal = tac_join(param, declocal);
    bloco = tac_join(declocal, bloco);

    endfunc =  tac_create(TAC_ENDFUN, symbol, NULL, NULL);

    endfunc = tac_join(bloco, endfunc);

    return endfunc;
}
