#include <stdlib.h>
#include "semantic.h"

void checkDeclarations(ASTREE *root){
	if(root == 0) return;
	
	int i;

	if(root->type == ASTREE_VARDEC || root->type == ASTREE_VETDEC || root->type == ASTREE_FUNDEC || 
	   root->type == ASTREE_PARAM || root->type == ASTREE_VETDEC2 || root->type == ASTREE_VETDEC3 ||
	   root->type == ASTREE_VETDEC4)
	{

		if(root->symbol == 0) {
			printf("Line %d: Declaration is missing the identifier name.\n", root->lineNumber);
		} else {
			if (root->symbol->type != SYMBOL_IDENTIFIER)
				printf("Line %d: Symbol %s already defined.\n", root->lineNumber, root->symbol->lexem);
			if (root->type == ASTREE_VARDEC) root->symbol->type = SYMBOL_VARIABLE;
			if (root->type == ASTREE_VETDEC) root->symbol->type = SYMBOL_VECTOR;
			if (root->type == ASTREE_VETDEC2) root->symbol->type = SYMBOL_VECTOR;
			if (root->type == ASTREE_VETDEC3) root->symbol->type = SYMBOL_POINTER;
			if (root->type == ASTREE_VETDEC4) root->symbol->type = SYMBOL_POINTER;
			if (root->type == ASTREE_FUNDEC) root->symbol->type = SYMBOL_FUNCTION;
			if (root->type == ASTREE_PARAM) root->symbol->type = SYMBOL_PARAM;
		}
	}

	for (i = 0; i < MAX_SONS; ++i) {
		checkDeclarations(root->son[i]);
	}
}

void checkRightSideAssType(ASTREE *root, int type)
{
	if(root == NULL) return;

	int i;
	
		if(root->type == ASTREE_VAR)
		{
			if(root->symbol->type != type)
			{
				printf("Line %d: Invalid pointer usage.\n", root->lineNumber);
				return;
			}
		}


	for(i=0;i<MAX_SONS; ++i)
		checkRightSideAssType(root->son[i], type);
}

void checkUtilization(ASTREE *root){
	if(root == 0) return;
	
	int i;

/*-----------------------------------------------------------------------*/	
	if(root->type == ASTREE_VAR || root->type == ASTREE_SCALAR_ASS )
	{
		if(root->symbol->type != SYMBOL_VARIABLE && root->symbol->type != SYMBOL_POINTER)
		{
			if (root->symbol->type == SYMBOL_VECTOR)
			{
				printf("Line %d: Declared vector %s being used as scalar type.\n", root->lineNumber, root->symbol->lexem);
			}
			else if(root->symbol->type == SYMBOL_FUNCTION)
			{
				printf("Line %d: Declared function %s being used as scalar type.\n", root->lineNumber, root->symbol->lexem);
			}
			else if(root->symbol->type == SYMBOL_POINTER)
			{
				printf("Line %d: Declared pointer %s being used as scalar type.\n", root->lineNumber, root->symbol->lexem);
			}	
			else if (root->symbol->type != SYMBOL_VARIABLE && root->symbol->type != SYMBOL_PARAM)
			{
				printf("Line %d: Variable %s not declared.\n", root->lineNumber, root->symbol->lexem);
			}
		}
		else
		if(root->type == ASTREE_SCALAR_ASS && root->symbol->type == SYMBOL_VARIABLE)
		{
			//SE FOR DO TIPO a = *pt
			if(root->son[0]->type == ASTREE_REFVET)
			{
				if(root->son[0]->symbol->type != SYMBOL_POINTER)
					printf("Line %d: Invalid pointer reference. \n", root->son[0]->lineNumber, root->son[0]->symbol->lexem);
			} 
			else if(root->son[0]->type == ASTREE_DEREFVET)
			{
				printf("Line %d: Invalid pointer reference. \n", root->son[0]->lineNumber, root->son[0]->symbol->lexem);
			}
			else if(root->son[0]->type == ASTREE_VAR)
			{
				if(root->son[0]->symbol->type == SYMBOL_POINTER)
					printf("Line %d: Declared pointer %s being used as scalar type. \n", root->son[0]->lineNumber, root->son[0]->symbol->lexem);
			}
			else
				checkRightSideAssType(root, root->symbol->type);
			
		}
			
		else
		if(root->type == ASTREE_SCALAR_ASS && root->symbol->type == SYMBOL_POINTER)
		{	
			//Se for do tipo pt = &a 
			if(root->son[0]->type == ASTREE_DEREFVET)
			{
				if(root->son[0]->symbol->type != SYMBOL_VARIABLE)
					printf("Line %d: Invalid pointer reference. \n", root->son[0]->lineNumber, root->son[0]->symbol->lexem);
			}
			else if(root->son[0]->type == ASTREE_REFVET)
			{
				printf("Line %d: Invalid pointer reference. \n", root->son[0]->lineNumber, root->son[0]->symbol->lexem);
			}
			else if(root->son[0]->type == ASTREE_VAR)
			{
				if(root->son[0]->symbol->type == SYMBOL_VARIABLE)
					printf("Line %d: Declared scalar %s being used as pointer type. \n", root->son[0]->lineNumber, root->son[0]->symbol->lexem);
			}
		}
	}
/*-----------------------------------------------------------------------*/	
	// Make sure only declared vectors are being used as vectors
	else if(root->type == ASTREE_VETOR || root->type == ASTREE_VETOR_ASS){
		if (root->symbol->type == SYMBOL_VARIABLE || root->symbol->type == SYMBOL_PARAM)
		{
			printf("Line %d: Declared variable %s being used as vector type.\n", root->lineNumber, root->symbol->lexem);
		} else if (root->symbol->type == SYMBOL_FUNCTION) 
		{	
			printf("Line %d: Declared function %s being used as vector type.\n", root->lineNumber, root->symbol->lexem);
		}
			else if(root->symbol->type == SYMBOL_POINTER)
		{
			printf("Line %d: Declared pointer %s being used as vector type.\n", root->lineNumber, root->symbol->lexem);
		}	
		 else if (root->symbol->type != SYMBOL_VECTOR)
		{
			printf("Line %d: Vector %s not declared.\n", root->lineNumber, root->symbol->lexem);
		}
	}
/*-----------------------------------------------------------------------*/	
	// Make sure only declared functions are being used as functions
	else if(root->type == ASTREE_FUNC)
	{
		if (root->symbol->type == SYMBOL_VARIABLE || root->symbol->type == SYMBOL_PARAM)
		{
			printf("Line %d: Declared variable %s being used as function type.\n", root->lineNumber, root->symbol->lexem);
		}
		else if (root->symbol->type == SYMBOL_VECTOR)
		{
			printf("Line %d: Declared vector %s being used as function type.\n", root->lineNumber, root->symbol->lexem);
		}
		else if(root->symbol->type == SYMBOL_POINTER)
		{
			printf("Line %d: Declared pointer %s being used as function type.\n", root->lineNumber, root->symbol->lexem);
		}	
		else if (root->symbol->type != SYMBOL_FUNCTION)
		{
			printf("Line %d: Function %s not declared.\n", root->lineNumber, root->symbol->lexem);
		}
		else if (root->symbol->type == SYMBOL_FUNCTION)
		{
			checkFunctionCallParameters(root);
		}
	}


	for (i = 0; i < MAX_SONS; ++i)
	{
		checkUtilization(root->son[i]);
	}
}

void checkDataTypes(ASTREE *root)
{
	if(root == 0) return;
	
	int i;

	/*if(root->type == ASTREE_SOMA)
	{
		if(root->son[0]->type == ASTREE_VAR)
		{
			if(root->son[0]->symbol->dataType == SYMBOL_POINTER)
			{
				if(root->son[1]->)
			}
	}*/


	// Make sure the arithmetic expressions have the correct operators types
	if(root->type == ASTREE_SOMA || root->type == ASTREE_SUB || root->type == ASTREE_MULT || root->type == ASTREE_DIV)
	{
		if(root->son[0]->type != ASTREE_SOMA &&	root->son[0]->type != ASTREE_SUB && root->son[0]->type != ASTREE_MULT && root->son[0]->type != ASTREE_DIV)
		{
			if(root->son[0]->type == ASTREE_VAR ||	root->son[0]->type == ASTREE_VETOR || root->son[0]->type == ASTREE_SYMBOL)
			{
				if(root->son[0]->symbol->dataType != ASTREE_WORD && root->son[0]->symbol->dataType != ASTREE_BYTE)
				{
					printf("Line %d: Operator %s is of an invalid type for arithmetic expression.\n", root->lineNumber, root->son[0]->symbol->lexem);
				}
				if(root->type != ASTREE_SOMA && root->son[0]->symbol->type == SYMBOL_POINTER)
					printf("Line %d: Invalid pointer usage.\n", root->son[0]->lineNumber);
				else
				if(root->type == ASTREE_SOMA && root->son[0]->symbol->type == SYMBOL_POINTER)
				{
					if(root->son[1]->type != ASTREE_SYMBOL)
						printf("Line %d: Invalid pointer usage.\n", root->son[0]->lineNumber);
				}
			}
			else if(root->son[0]->type == ASTREE_EXPRESSION) 
				 if(root->son[0]->son[0]->type == ASTREE_VAR ||	root->son[0]->son[0]->type == ASTREE_VETOR || root->son[0]->son[0]->type == ASTREE_SYMBOL)
				 {
				 	if(root->son[0]->son[0]->symbol->dataType != ASTREE_WORD && root->son[0]->son[0]->symbol->dataType != ASTREE_BYTE)
					{
					printf("Line %d: Operator %s is of an invalid type for arithmetic expression.\n", root->lineNumber, root->son[0]->son[0]->symbol->lexem);
					}
				 }
		}

		if(root->son[1]->type != ASTREE_SOMA &&	root->son[1]->type != ASTREE_SUB && root->son[1]->type != ASTREE_MULT && root->son[1]->type != ASTREE_DIV)
		{
			if(root->son[1]->type == ASTREE_VAR ||	root->son[1]->type == ASTREE_VETOR || root->son[1]->type == ASTREE_SYMBOL)
			{
				if(root->son[1]->symbol->dataType != ASTREE_WORD && root->son[1]->symbol->dataType != ASTREE_BYTE)
				{
					printf("Line %d: Operator %s is of an invalid type for arithmetic expression.\n", root->lineNumber, root->son[1]->symbol->lexem);
				}
				if(root->type != ASTREE_SOMA && root->son[1]->symbol->type == SYMBOL_POINTER)
					printf("Line %d: Invalid pointer usage.\n", root->son[1]->lineNumber);
				else
				if(root->type == ASTREE_SOMA && root->son[1]->symbol->type == SYMBOL_POINTER)
				{
					if(root->son[0]->type != ASTREE_SYMBOL)
						printf("Line %d: Invalid pointer usage.\n", root->son[0]->lineNumber);
				}
			}
			else if(root->son[1]->type == ASTREE_EXPRESSION) 
				 if(root->son[1]->son[0]->type == ASTREE_VAR ||	root->son[1]->son[0]->type == ASTREE_VETOR || root->son[1]->son[0]->type == ASTREE_SYMBOL)
				 {
				 	if(root->son[1]->son[0]->symbol->dataType != ASTREE_WORD && root->son[1]->son[0]->symbol->dataType != ASTREE_BYTE)
					{
					printf("Line %d: Operator %s is of an invalid type for arithmetic expression.\n", root->lineNumber, root->son[1]->son[0]->symbol->lexem);
					}
				 }
		}
	}


	
	// Make sure the relational expressions have the correct operators types
	else if(root->type == ASTREE_LESS || root->type == ASTREE_GREAT || root->type == ASTREE_LE || root->type == ASTREE_GE)
	{
		if(root->son[0]->type != ASTREE_SOMA &&	root->son[0]->type != ASTREE_SUB && root->son[0]->type != ASTREE_MULT && root->son[0]->type != ASTREE_DIV)
		{
			if(root->son[0]->type == ASTREE_VAR ||	root->son[0]->type == ASTREE_VETOR || root->son[0]->type == ASTREE_SYMBOL)
			{
				if(root->son[0]->symbol->dataType != ASTREE_WORD && root->son[0]->symbol->dataType != ASTREE_BYTE)
				{
					printf("Line %d: Operator %s is of an invalid type for relational expression.\n", root->lineNumber, root->son[0]->symbol->lexem);
				}
				if(root->son[0]->symbol->type == SYMBOL_POINTER)
					printf("Line %d: Invalid pointer usage.\n", root->son[0]->lineNumber);
			}
			else if(root->son[0]->type == ASTREE_EXPRESSION) 
				 if(root->son[0]->son[0]->type == ASTREE_VAR ||	root->son[0]->son[0]->type == ASTREE_VETOR || root->son[0]->son[0]->type == ASTREE_SYMBOL)
				 {
				 	if(root->son[0]->son[0]->symbol->dataType != ASTREE_BOOL)
					{
					printf("Line %d: Operator %s is of an invalid type for relational expression.\n", root->lineNumber, root->son[0]->son[0]->symbol->lexem);
					}
				 }
		}

		if(root->son[1]->type != ASTREE_SOMA &&	root->son[1]->type != ASTREE_SUB && root->son[1]->type != ASTREE_MULT && root->son[1]->type != ASTREE_DIV)
		{
			if(root->son[1]->type == ASTREE_VAR ||	root->son[1]->type == ASTREE_VETOR || root->son[1]->type == ASTREE_SYMBOL)
			{
				if(root->son[1]->symbol->dataType != ASTREE_WORD && root->son[1]->symbol->dataType != ASTREE_BYTE)
				{
					printf("Line %d: Operator %s is of an invalid type for relational expression.\n", root->lineNumber, root->son[1]->symbol->lexem);
				}
				if(root->son[1]->symbol->type == SYMBOL_POINTER)
					printf("Line %d: Invalid pointer usage.\n", root->son[1]->lineNumber);
			}
			else if(root->son[1]->type == ASTREE_EXPRESSION) 
				 if(root->son[1]->son[0]->type == ASTREE_VAR ||	root->son[1]->son[0]->type == ASTREE_VETOR || root->son[1]->son[0]->type == ASTREE_SYMBOL)
				 {
				 	if(root->son[1]->son[0]->symbol->dataType != ASTREE_BOOL)
					{
					printf("Line %d: Operator %s is of an invalid type for relational expression.\n", root->lineNumber, root->son[1]->son[0]->symbol->lexem);
					}
				 }
		}
	}
	
	// Make sure the logical expressions have the correct operators types
	else if(root->type == ASTREE_AND || root->type == ASTREE_OR) {
		if(root->son[0]->type != ASTREE_LESS &&
			root->son[0]->type != ASTREE_GREAT &&
			root->son[0]->type != ASTREE_LE &&
			root->son[0]->type != ASTREE_GE &&
			root->son[0]->type != ASTREE_EQ &&
			root->son[0]->type != ASTREE_NE &&
			root->son[0]->type != ASTREE_AND &&
			root->son[0]->type != ASTREE_OR &&
			root->son[0]->type != ASTREE_EXPRESSION) {
			if(root->son[0]->type == ASTREE_VAR ||
				root->son[0]->type == ASTREE_VETOR ||
				root->son[0]->type == ASTREE_SYMBOL) {
				if(root->son[0]->symbol->dataType != ASTREE_BOOL) {
					printf("Line %d: Operator %s is of an invalid type for logical expression.\n", root->lineNumber, root->son[0]->symbol->lexem);
				}
				if(root->son[0]->symbol->type == SYMBOL_POINTER)
					printf("Line %d: Invalid pointer usage.\n", root->son[0]->lineNumber);
			}
			else printf("Line %d: Logical expression contains an invalid operator type.\n", root->lineNumber);
		}

		if(root->son[0]->type != ASTREE_LESS &&
			root->son[0]->type != ASTREE_GREAT &&
			root->son[0]->type != ASTREE_LE &&
			root->son[0]->type != ASTREE_GE &&
			root->son[0]->type != ASTREE_EQ &&
			root->son[0]->type != ASTREE_NE &&
			root->son[0]->type != ASTREE_AND &&
			root->son[0]->type != ASTREE_OR &&
			root->son[0]->type != ASTREE_EXPRESSION) {
			if(root->son[1]->type == ASTREE_VAR ||
				root->son[1]->type == ASTREE_VETOR ||
				root->son[1]->type == ASTREE_SYMBOL) {
				if(root->son[1]->symbol->dataType != ASTREE_BOOL) {
					printf("Line %d: Operator %s is of an invalid type for logical expression.\n", root->lineNumber, root->son[1]->symbol->lexem);
				}
				if(root->son[1]->symbol->type == SYMBOL_POINTER)
					printf("Line %d: Invalid pointer usage.\n", root->son[1]->lineNumber);
			}
			else printf("Line %d: Logical expression contains an invalid operator type.\n", root->lineNumber);
		}
	}



	// Make sure the vector index is of the correct type
	else if(root->type == ASTREE_VETOR ||	root->type == ASTREE_VETOR_ASS)
	{
		if(root->son[0]->type != ASTREE_SOMA &&	root->son[0]->type != ASTREE_SUB && root->son[0]->type != ASTREE_MULT && root->son[0]->type != ASTREE_DIV)
		{
			if(root->son[0]->type == ASTREE_VAR ||	root->son[0]->type == ASTREE_VETOR || root->son[0]->type == ASTREE_SYMBOL)
			{
				if(root->son[0]->symbol->dataType != ASTREE_WORD && root->son[0]->symbol->dataType != ASTREE_BYTE)
				{
					printf("Line %d: Vector index %s is of an invalid type.\n", root->lineNumber, root->son[0]->symbol->lexem);
				}
				if(root->son[0]->symbol->type == SYMBOL_POINTER)
					printf("Line %d: Invalid pointer usage.\n", root->son[0]->lineNumber);
			}
			else if(root->son[0]->type != ASTREE_EXPRESSION)
				printf("Line %d: Vector index is of an invalid type.\n", root->lineNumber);
		}
	}

	else if(root->type == ASTREE_SCALAR_ASS || root->type == ASTREE_VETOR_ASS)
	{
		if(root->son[0]->symbol)
		{
			if((root->son[0]->symbol->dataType == ASTREE_WORD || root->son[0]->symbol->dataType == ASTREE_BYTE)
				&& (root->symbol->dataType != ASTREE_WORD && root->symbol->dataType != ASTREE_BYTE))
				printf("Line %d: Assigment of different types. \n", root->lineNumber);

			if(root->son[0]->symbol->dataType == ASTREE_BOOL && root->symbol->dataType != ASTREE_BOOL)
				printf("Line %d: Assigment of different types. \n", root->lineNumber);
		}
		else
			checkRightSideAss(root, root);
	}

	else if(root->type == ASTREE_FUNDEC)
	{
		checkFunctionReturn(root, root);
	}
	
	for (i = 0; i < MAX_SONS; ++i)
	{
		checkDataTypes(root->son[i]);
	}
}

void checkRightSideAss(ASTREE *root, ASTREE *aux)
{
	if(root == NULL || aux == NULL) return;

	int i;
	
		//SE FOR UM OPERADOR LÓGICO
		if(aux->type == ASTREE_LESS ||
			aux->type == ASTREE_GREAT ||
			aux->type == ASTREE_LE ||
			aux->type == ASTREE_GE ||
			aux->type == ASTREE_EQ ||
			aux->type == ASTREE_NE ||
			aux->type == ASTREE_AND ||
			aux->type == ASTREE_OR)
			{
				if(root->symbol->dataType != ASTREE_BOOL)
				{ 
					fprintf(stderr, "Line %d: Assigment of different types. \n", aux->lineNumber);
					return;
				}		
			}
		if(aux->type == ASTREE_SOMA ||
			aux->type == ASTREE_SUB ||
			aux->type == ASTREE_MULT ||
			aux->type == ASTREE_DIV)
			{
			
				if(root->symbol->dataType != ASTREE_WORD && root->symbol->dataType != ASTREE_BYTE)
				{
					fprintf(stderr, "Line %d: Assigment of different types. \n", aux->lineNumber);
					return;
				}

			}


	for(i=0;i<MAX_SONS; ++i)
		checkRightSideAss(root, aux->son[i]);
}

void checkFunctionReturn(ASTREE *root, ASTREE *aux)
{
	if(root == NULL || aux == NULL) return;

	int i;
	if(aux->type == ASTREE_KW_RETURN)
	{
		//SE FOR UMA VARIAVEL, UM VETOR OU UMA FUNÇÃO
		if(aux->son[0]->type == ASTREE_VAR || 
		   aux->son[0]->type == ASTREE_VETOR || 
		   aux->son[0]->type == ASTREE_FUNC)
			{

				if(((aux->son[0]->symbol->dataType == ASTREE_WORD || aux->son[0]->symbol->dataType == ASTREE_BYTE)
					 && (root->symbol->dataType != ASTREE_WORD && root->symbol->dataType != ASTREE_BYTE))
					|| aux->son[0]->symbol->dataType == ASTREE_BOOL && root->symbol->dataType != ASTREE_BOOL)
				{ 
					fprintf(stderr, "Line %d: Invalid return type. \n", aux->son[0]->lineNumber);
					return;
				}
			}
		//SE FOR UM OPERADOR LÓGICO
		if(aux->son[0]->type == ASTREE_LESS ||
			aux->son[0]->type == ASTREE_GREAT ||
			aux->son[0]->type == ASTREE_LE ||
			aux->son[0]->type == ASTREE_GE ||
			aux->son[0]->type == ASTREE_EQ ||
			aux->son[0]->type == ASTREE_NE ||
			aux->son[0]->type == ASTREE_AND ||
			aux->son[0]->type == ASTREE_OR)
			{
				if(root->symbol->dataType != ASTREE_BOOL)
				{ 
					fprintf(stderr, "Line %d: Invalid return type. \n", aux->son[0]->lineNumber);
					return;
				}		
			}
		if(aux->son[0]->type == ASTREE_SOMA ||
			aux->son[0]->type == ASTREE_SUB ||
			aux->son[0]->type == ASTREE_MULT ||
			aux->son[0]->type == ASTREE_DIV)
			{
			
				if(root->symbol->dataType != ASTREE_WORD && root->symbol->dataType != ASTREE_BYTE)
				{
					fprintf(stderr, "Line %d: Invalid return type. \n", aux->son[0]->lineNumber);
					return;
				}

			}

	}

	for(i=0;i<MAX_SONS; ++i)
		checkFunctionReturn(root, aux->son[i]);

}

void checkFunctionCallParameters(ASTREE *root)
{
	if(root == 0) return;

	int i;

	if(root->type == ASTREE_FUNC)
		 checkListParams(root->symbol->funcParam, root->son[0], root);

}

void checkListParams(ASTREE *declParams, ASTREE *callParams, ASTREE *root)
{

	if(declParams == NULL && callParams == NULL) return;
	if(declParams == NULL && callParams != NULL || declParams != NULL && callParams == NULL)
	{ 
		printf("Line %d: Function call %s invalid number of parameters.\n", root->lineNumber, root->symbol->lexem);
		return;
	}
	int parameterType = checkExpressionType(callParams->son[0]);

	if(declParams->symbol->dataType == ASTREE_BOOL && parameterType != ASTREE_BOOL)
	{
		printf("Line %d: Function call %s invalid parameter type.\n", root->lineNumber, root->symbol->lexem);
		return;
	}
	else if ((declParams->symbol->dataType == ASTREE_WORD || declParams->symbol->dataType == ASTREE_BYTE)
			  && parameterType != ASTREE_WORD && parameterType != ASTREE_BYTE)
	{
		printf("Line %d: Function call %s invalid parameter type.\n", root->lineNumber, root->symbol->lexem);
		return;
	}
	
	checkListParams(declParams->son[1], callParams->son[1], root);
}

int checkExpressionType(ASTREE *expression)
{
	int dataType1, dataType2;
	if(expression == 0) return -1;
	else
	{
		if(expression->symbol != 0)
			return expression->symbol->dataType;
		else
		{

			if(expression->type == ASTREE_LE || expression->type == ASTREE_GE || expression->type == ASTREE_EQ ||
				expression->type == ASTREE_NE || expression->type == ASTREE_AND || expression->type == ASTREE_OR ||
				expression->type == ASTREE_LESS || expression->type == ASTREE_GREAT) 
				return ASTREE_BOOL;

			dataType1 = checkExpressionType(expression->son[0]);
			dataType2 = checkExpressionType(expression->son[1]);
			if(dataType1 == ASTREE_WORD || dataType2 == ASTREE_WORD)
				return ASTREE_WORD;
			if(dataType1 == ASTREE_BYTE || dataType2 == ASTREE_BYTE)
				return ASTREE_BYTE;
			else
				return ASTREE_BOOL;
		} 

	}

} 
