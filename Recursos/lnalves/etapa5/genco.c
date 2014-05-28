#include "astree.h"
#include "tacs.h"
#include "genco.h"


TAC* generateCode(ASTREE *node)
{
	TAC* code[MAX_SONS];
	TAC* result = NULL;
	int i;	

	if(!node)
		return NULL;

	for(i = 0; i< MAX_SONS; ++i)
		code[i] = 0;

	for(i = 0; i< MAX_SONS; ++i)
		if(node->son[i])
			code[i] = generateCode(node->son[i]);

	switch(node->type)
	{
	
		case ASTREE_SYMBOL: result = tac_create(TAC_SYMBOL,node->symbol, NULL, NULL); break;	

		case ASTREE_SOMA: result = makeOpt(code[0],code[1],TAC_SOMA); break;

		case ASTREE_SUB: result = makeOpt(code[0],code[1],TAC_SUB); break;

		case ASTREE_MULT: result = makeOpt(code[0],code[1],TAC_MULT); break;

		case ASTREE_DIV: result = makeOpt(code[0],code[1],TAC_DIV); break;
		
		case ASTREE_SCALAR_ASS: result = tac_join(code[0], 
						tac_create(TAC_MOV, node->symbol, code[0]? code[0]->target : 0, 0)); break;

		case ASTREE_VAR: result = tac_create(TAC_VAR,node->symbol, NULL, NULL); break;
	
		case ASTREE_LE: result = makeOpt(code[0],code[1],TAC_LE); break;

		case ASTREE_GE: result = makeOpt(code[0],code[1],TAC_GE); break;

		case ASTREE_EQ: result = makeOpt(code[0],code[1],TAC_EQ); break;

		case ASTREE_NE: result = makeOpt(code[0],code[1],TAC_NE); break;

		case ASTREE_AND: result = makeOpt(code[0],code[1],TAC_AND); break;

		case ASTREE_OR: result = makeOpt(code[0],code[1],TAC_OR); break;

		case ASTREE_LESS: result = makeOpt(code[0],code[1],TAC_LESS); break;

		case ASTREE_GREAT: result = makeOpt(code[0],code[1],TAC_GREAT); break;

		case ASTREE_IF: result = makeIf(code[0],code[1]); break;

		case ASTREE_IFELSE: result = makeIfElse(code[0],code[1], code[2]); break;

		case ASTREE_FUNDEC: result = makeFunc(node->symbol,code[1],code[2],code[3]); break;

		case ASTREE_FUNC: result = makeCallFunc(node->symbol, code[0]) ; break;

		case ASTREE_BLOCO: result = code[0]; break;

		case ASTREE_DECLOC: result = tac_join(code[0],code[1]); break;

		case ASTREE_PARAM: result = makeParams(node->symbol,code[1]); break;

		case ASTREE_LOOP: result = makeLoop(code[0],code[1]); break;

		case ASTREE_KW_RETURN: result = tac_join(code[0],tac_create(TAC_RETURN,code[0]? code[0]->target : 0, NULL, NULL)); break;
		
		case ASTREE_OUTPUT: result = makeOutput(code[0], code[1]); break;

		case ASTREE_OUTPUT2: result = makeOutput(code[0],code[1]); break;

		case ASTREE_VETOR_ASS: result = makeVetorAss(node->symbol, code[0],code[1]); break;

		case ASTREE_VARDEC: result = makeVarDec(node->symbol, code[1]); break;

		
		case ASTREE_VETDEC: result = makeVetDec(node->symbol, code[1]); break;
		
		case ASTREE_VETDEC2: result = makeVetDec(node->symbol ,code[1]); break; // code[2] são os valores

		case ASTREE_INITVET: result = makeVetDecInit(code[0], code[1]); break; //tac_join(code[0],code[1]); break;

		case ASTREE_INITVET2: result =  makeVetDecInit(code[0], code[1]); break; //tac_join(code[0],code[1]); break;

		case ASTREE_VETDEC3: result = makePtrDec(node->symbol, code[1]); break;
		
		case ASTREE_VETDEC4: result = makePtrDec(node->symbol, code[1]); break;

		case ASTREE_GLIST: result = tac_join(code[0], code[1]); break;

		case ASTREE_CMDL: result = tac_join(code[0],code[1]); break;
		
		case ASTREE_KW_INPUT: result = tac_create(TAC_INPUT, node->symbol, 0, 0); break;

		case ASTREE_DEREFVET: result = tac_create(TAC_PTRADRESS, node->symbol, 0, 0); break;

		case ASTREE_REFVET: result = tac_create(TAC_PTRVALUE, node->symbol, 0, 0); break;

		case ASTREE_EXPRESSION: result = code[0]; break;

		case ASTREE_CTRLBLOCO: result = code[0]; break;

		case ASTREE_PARAMFUNC: result = makeArgss(code[0], code[1]); break;

		case ASTREE_VETOR: result = makeVetorRead(node->symbol, code[0]); break;

		default:  result = tac_join(tac_join(tac_join(code[0],code[1]),code[2]),code[3]); 
				break;
	}

	//fprintf(stderr, "--\n");
	//if(node->type == ASTREE_INITVET || node->type == ASTREE_INITVET2 )
	//	tac_print_single(result); 
	
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

TAC* makeIf( TAC* code0, TAC* code1)
{
	//fprintf(stderr,"****entrou no if****\n");

	TAC* nova1 = NULL;
	TAC* nova2 = NULL;

	HASH_CELL* labelFinal;

	labelFinal = makeLabel();
	
	nova1 = tac_create(TAC_IFZ, labelFinal,code0? code0->target : 0, 0); //se falso, pula pro label final
	
	nova1->prev = code0;
	code1 = tac_join(nova1,code1);

	nova2 = tac_create(TAC_LABEL, labelFinal, 0, 0 );

	nova2->prev = code1;

	return nova2;/*(tac_join(tac_join(tac_join(code0, nova1),code1),nova2));*/

}

TAC* makeIfElse(TAC* code0, TAC* code1, TAC* code2)
{
	
	HASH_CELL *targetElse = makeLabel();
	HASH_CELL *targetEnd = makeLabel();

 	TAC * jumpElse = tac_create(TAC_IFZ, targetElse, code0?code0->target:0,0);
 	TAC * jumpEnd = tac_create(TAC_JUMP, targetEnd, 0,0);

	TAC* labelElse = tac_create(TAC_LABEL, targetElse, 0, 0);
	TAC* labelEnd = tac_create(TAC_LABEL, targetEnd, 0, 0);

	return tac_join(tac_join(tac_join(tac_join(tac_join(tac_join(code0 ,jumpElse), code1), jumpEnd), labelElse), code2), labelEnd);

}

TAC* makeFunc(HASH_CELL * symbol, TAC *param, TAC *declocal, TAC* bloco)
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

TAC* makeCallFunc(HASH_CELL *function, TAC *params)
{

	TAC *nova;
    HASH_CELL *resultado = NULL;
    
    resultado = makeTemp();
      
   	nova = tac_create(TAC_CALL, resultado, function, NULL);   

    return tac_join(params,nova);

}

TAC *makeParams(HASH_CELL *argumento, TAC *proximos)
{
    TAC *nova;
 
    nova = tac_create(TAC_PARAM, argumento,  NULL, NULL);

    return tac_join(nova, proximos);
}

TAC *makeArgss(TAC *param, TAC *paramlist)
{
    TAC *nova;
    
    
    nova = tac_create(TAC_ARG, param? param->target : NULL, NULL, NULL);

    return tac_join(nova, paramlist);
}


TAC* makeLoop(TAC *code0, TAC* code1) {
    
    
    HASH_CELL *targetBegin, *targetEnd;
    TAC *ifz, *jmp, *labelEnd, *labelBegin;
    targetBegin = makeLabel();
    targetEnd = makeLabel();

    labelBegin = tac_create(TAC_LABEL, targetBegin, NULL, NULL);
    
    code0 = tac_join(labelBegin, code0);
    
    ifz = tac_create(TAC_IFZ, targetEnd, code0?code0->target:0, NULL);
    
    ifz->prev = code0;
    code1 = tac_join(ifz,code1);
    
    jmp = tac_create(TAC_JUMP, targetBegin, NULL, NULL);
    
    jmp->prev = code1;
    
    labelEnd = tac_create(TAC_LABEL, targetEnd, NULL, NULL);
    
    labelEnd->prev = jmp;
    
    return labelEnd;
}

TAC* makeOutput( TAC* code0, TAC* proximo)
{
	TAC *nova = NULL;
	
	nova = tac_create(TAC_OUTPUT, code0? code0->target : 0,  0, 0);
	
	nova = tac_join(nova, proximo);

	return nova;

}

TAC *makeVetorAss(HASH_CELL *symbol, TAC* indice, TAC *expr)
{
	
	TAC *newTac;
    
    
    newTac = tac_create(TAC_VETW, symbol, indice? indice->target :0, expr? expr->target:0);
    
     
    return tac_join(tac_join(indice,expr),newTac);

}


TAC *makeVarDec(HASH_CELL *symbol, TAC* literal)
{
	
	TAC *newTac;
    
    
    newTac = tac_create(TAC_VARDEC, symbol, literal? literal->target :0, 0);
    
     
    return tac_join(literal,newTac);

}

TAC *makeVetDec(HASH_CELL *symbol, TAC* tam)
{
	
	TAC *newTac;
    
    
    newTac = tac_create(TAC_VETDEC, symbol, tam? tam->target :0, 0);
    
     
    return tac_join(tam,newTac);

}

TAC *makeVetDecInit(TAC* valor, TAC* proximo)
{
	
	TAC *nova;
    
    
    nova = tac_create(TAC_VETDECINIT, valor? valor->target :0, NULL, NULL);
    
     
    return tac_join(nova,proximo);

}

TAC *makePtrDec(HASH_CELL *symbol, TAC* literal)
{
	
	TAC *newTac;
    
    
    newTac = tac_create(TAC_PTRDEC, symbol, literal? literal->target :0, 0);
    
     
    return tac_join(literal,newTac);

}

TAC *makeVetorRead(HASH_CELL *symbol, TAC* indice)
{
	
	TAC *newTac;
	HASH_CELL *resultado = NULL;
    resultado = makeTemp();
    
    
    newTac = tac_create(TAC_VETREAD, resultado, symbol, indice? indice->target :0);
    
     
    return tac_join(indice,newTac);

}

