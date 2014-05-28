//SEMANTIC ANALYSIS 2012

#include "semantic.h"
#include <stdio.h>

int guardaTypeRet=0;
ASTREE *funcAst;
int scalDecl=0;

void checkDeclaration(ASTREE *root)
{
	int i;

	if (root == 0)
		return;		

	if((root->type == AST_declaracao) || (root->type == AST_funcao))
	{
		if(root->symbol == 0)
			printf("ERRO - Declaration is missing the identifier name!!\n");
		else
		{
			if(root->symbol->content.type != SYMBOL_TK_IDENTIFIER)
				printf("ERRO - Line %d: Symbol %s already defined.\n", root->lineNumber, root->symbol->content.text);
			else
			{
				if(root->type == AST_funcao)
				{
					root->symbol->content.type = SYMBOL_FUNCTION;
					if(root->scc[1])
					{
						root->symbol->content.ast = (ASTREE*)calloc(1,sizeof(ASTREE));
						root->symbol->content.ast = root->scc[1];
					}
				}
				else
				{
					if(root->type == AST_declaracao)
					{
						if(root->scc[1]!=0)
							root->symbol->content.type = SYMBOL_VECTOR;
						else
							root->symbol->content.type = SYMBOL_VARIABLE;
					}
					else
						root->symbol->content.type = SYMBOL_VARIABLE;
				}
			}
		}
	}
	for(i=0; i < MAX_NODE; i++)
		checkDeclaration(root->scc[i]);
}

void checkVarDeclAsFunc(ASTREE *ast, char *text)
{
	int i;

	if(ast==0)
		return;

	if((ast->symbol!=0) && ((ast->type == AST_funcao) || (ast->symbol->content.type == SYMBOL_VECTOR)))
		if(strcmp(ast->symbol->content.text, text) == 0)
		{
			funcAst = ast;
			scalDecl = 1;
			return;
		}
	for(i=0; i < MAX_NODE; i++)
		checkVarDeclAsFunc(ast->scc[i], text);
}

void checkFuncCall(ASTREE *ast, char *text)
{
	int i;

	if(ast==0)
		return;

	if((ast->symbol!=0) && (ast->type == AST_funcao))
		if(strcmp(ast->symbol->content.text, text) == 0)
		{
			funcAst = ast;
			return;
		}
	for(i=0; i < MAX_NODE; i++)
		checkFuncCall(ast->scc[i], text);
}

void checkUtilization(ASTREE *root, ASTREE *rootAux)
{
	int i, result, verRet=0, operIgual=0;

	if (root == 0)
		return;
	if((root->symbol != 0) && (root->type == AST_funcao))
		guardaTypeRet = root->symbol->content.dataType;
	switch(root->type){
		case AST_KW_INPUT:
			if(root->symbol != 0)
				if (root->symbol->content.type != SYMBOL_VARIABLE)
	       				printf("ERRO - Line %d: Variable in INPUT is missing declaration!!!\n", root->lineNumber);
			break;
		case AST_exprComTK_IDENTIFIER:
			//printf("\n Variavel da chamada de funcao: %s com o tipo : %d \n", root->symbol->content.text, root->symbol->content.type);
			if(root->symbol->content.type != SYMBOL_TK_IDENTIFIER)
			{
				if(root->symbol->content.type == SYMBOL_FUNCTION)
				{
					funcAst = 0;
					checkFuncCall(rootAux, root->symbol->content.text);
					result = checkParamsFunc(funcAst->symbol->content.ast, root);
					if(result == 1)
						printf("ERRO - Line %d: Function %s containing MORE parameters than the number declared!!!\n", root->lineNumber, root->symbol->content.text);
					else
						if(result == 2)
							printf("ERRO - Line %d: Function %s containing LESS parameters than the number declared!!!\n", root->lineNumber, root->symbol->content.text);
						else
							if(result == 3)
								printf("ERRO - Line %d: Parameters of the function %s have different types or they are not declared!!!\n", root->lineNumber, root->symbol->content.text);
				}
			}
			break;
		case AST_KW_RETURN:
			if(root->scc[0]->type == AST_exprComTK_IDENTIFIER)
			{
				printf("ERROR - Line %d: Returning a function!!!\n", root->lineNumber);
				break;
			}
			if(root->scc[0]->type == AST_TK_IDENTIFIER_VET)
			{
				printf("ERROR - Line %d: Returning a vector. Sorry! This is not possible!!!\n", root->lineNumber);
			}
			else
			{
				verRet = analisaExpressao(root->scc[0], rootAux);
				if(guardaTypeRet != verRet)
				{
					switch(guardaTypeRet)
					{
						case DATATYPE_KW_INTEGER:
							if(verRet == DATATYPE_KW_FLOATING)
								printf("WARNING - Line %d: Loss of precision - Returning type (float) isn't the function type (integer)!!!\n", root->lineNumber);
							else
								printf("ERRO - Line %d: Returning type isn't the function type (integer)!!!\n", root->lineNumber);							
							break;
						case DATATYPE_KW_FLOATING:
							printf("ERRO - Line %d: Returning type isn't the function type (floating)!!!\n", root->lineNumber);
							break;
						case DATATYPE_KW_CHARACTER:
							printf("ERRO - Line %d: Returning type isn't the function type (character)!!!\n", root->lineNumber);
							break;
						case DATATYPE_KW_BOOLEAN:
							printf("ERRO - Line %d: Returning type isn't the function type (boolean)!!!\n", root->lineNumber);
							break;
					}
				}
			}
			break;
		case AST_KW_IF: // cuidar if/if_else/while/do_while
			if(root->scc[0]->scc[0] == 0)
			{
				if(root->scc[0]->type != AST_TK_IDENTIFIER)
					printf("ERRO - Line %d: IF expression containig just a literal!!!\n", root->lineNumber);
			}
			else
			{
				if((root->scc[0]->scc[1] == 0) && (root->scc[0]->symbol != 0))
				{
					if(root->scc[0]->type == AST_exprComTK_IDENTIFIER)
						printf("ERRO - Line %d: function being called into IF expression!!!\n", root->lineNumber);
				}
				else
				{
					if((root->scc[0]->scc[1] != 0) && (root->scc[0]->symbol == 0))						
						if(root->scc[0]->type == (AST_ADD || AST_SUB || AST_MUL || AST_DIV))
							printf("ERRO - Line %d: arithmetic operation into an IF expression!!!\n", root->lineNumber);
				}
			}
			break;
		case AST_KW_IF_ELSE:
			if(root->scc[0]->scc[0] == 0)
			{
				if(root->scc[0]->type != AST_TK_IDENTIFIER)
					printf("ERRO - Line %d: IF expression containig just a literal!!!\n", root->lineNumber);
			}
			else
			{
				if((root->scc[0]->scc[1] == 0) && (root->scc[0]->symbol != 0))
				{
					if(root->scc[0]->type == AST_exprComTK_IDENTIFIER)
						printf("ERRO - Line %d: function being called into IF expression!!!\n", root->lineNumber);
				}
				else
				{
					if((root->scc[0]->scc[1] != 0) && (root->scc[0]->symbol == 0))						
						if(root->scc[0]->type == (AST_ADD || AST_SUB || AST_MUL || AST_DIV))
							printf("ERRO - Line %d: arithmetic operation into an IF expression!!!\n", root->lineNumber);
				}
			}
			break;
		case AST_KW_WHILE:
			if(root->scc[0]->scc[0] != 0)
			{
				if((root->scc[0]->scc[1] == 0) && (root->scc[0]->symbol != 0))
				{
					if(root->scc[0]->type == AST_exprComTK_IDENTIFIER)
						printf("ERRO - Line %d: function being called into WHILE expression!!!\n", root->lineNumber);
				}
				else
				{
					if((root->scc[0]->scc[1] != 0) && (root->scc[0]->symbol == 0))						
						if(root->scc[0]->type == (AST_ADD || AST_SUB || AST_MUL || AST_DIV))
							printf("ERRO - Line %d: arithmetic operation into an WHILE expression!!!\n", root->lineNumber);
				}
			}
			break;
		case AST_KW_DO_WHILE:
			if(root->scc[1]->scc[0] != 0)
			{
				if((root->scc[1]->scc[1] == 0) && (root->scc[1]->symbol != 0))
				{
					if(root->scc[1]->type == AST_exprComTK_IDENTIFIER)
						printf("ERRO - Line %d: function being called into DO_WHILE expression!!!\n", root->lineNumber);
				}
				else
				{
					if((root->scc[1]->scc[1] != 0) && (root->scc[1]->symbol == 0))						
						if(root->scc[1]->type == (AST_ADD || AST_SUB || AST_MUL || AST_DIV))
							printf("ERRO - Line %d: arithmetic operation into an DO_WHILE expression!!!\n", root->lineNumber);
				}
			}
			break;
		case AST_IGUAL:
			funcAst = 0;
			scalDecl = 0;
			checkVarDeclAsFunc(rootAux, root->scc[0]->symbol->content.text);
			if(scalDecl == 1)
			{
				if(funcAst->symbol->content.type == SYMBOL_FUNCTION)
					printf("ERRO - Line %d: Variable %s is using the same name of a function!!!\n", root->lineNumber, root->scc[0]->symbol->content.text);
				else
					if(root->scc[0]->type == AST_TK_IDENTIFIER)
						printf("ERRO - Line %d: Variable %s is declared as a vector!!!\n", root->lineNumber, root->scc[0]->symbol->content.text);
			}
			if(root->scc[0]->type == AST_TK_IDENTIFIER)
			{
				if(root->scc[0]->symbol->content.dataType != 0)
				{
					operIgual = analisaExpressao(root->scc[1], rootAux);
					if(operIgual != 0)
					{
						if(root->scc[0]->symbol->content.dataType != operIgual)
						{
							if(root->scc[1]->type == AST_exprComTK_IDENTIFIER)
								if(root->scc[1]->symbol->content.type != SYMBOL_FUNCTION)
									printf("ERRO - Line %d: Variable %s is not declared as a function, but it is being used as one!!!\n", root->lineNumber, root->scc[1]->symbol->content.text);
							switch(root->scc[0]->symbol->content.dataType)
							{
								case DATATYPE_KW_INTEGER:
									if(operIgual == DATATYPE_KW_FLOATING)
										printf("WARNING - Line %d: Loss of precision - different types, putting float into integer!!!\n", root->lineNumber);
									else
										printf("ERRO - Line %d: Variables containing different types!!!\n", root->lineNumber);
									break;
								case DATATYPE_KW_FLOATING:
									if((operIgual == DATATYPE_KW_CHARACTER) || (operIgual == DATATYPE_KW_BOOLEAN))
										printf("ERRO - Line %d: Variables containing different types!!!\n", root->lineNumber);
									break;
								case DATATYPE_KW_CHARACTER:
									if(operIgual != DATATYPE_KW_BOOLEAN)
										printf("ERRO - Line %d: Variables containing different types!!!\n", root->lineNumber);
									else
										printf("ERRO - Line %d: Variable does not match!!!\n", root->lineNumber);
									break;
								case DATATYPE_KW_BOOLEAN:
									printf("ERRO - Line %d: Variable does not match!!!\n", root->lineNumber);
									break;
							}
						}
						else
							if(root->scc[1]->type == AST_exprComTK_IDENTIFIER)
								if(root->scc[1]->symbol->content.type != SYMBOL_FUNCTION)
									printf("ERRO - Line %d: Variable %s is not declared as a function, but it is being used as one!!!\n", root->lineNumber, root->scc[1]->symbol->content.text);
					}
				}
			}
			else
			{
				if(root->scc[0]->symbol->content.dataType != 0)
				{
					operIgual = analisaExpressao(root->scc[0]->scc[0], rootAux);
					if(operIgual != 0)
					{
						if(operIgual != DATATYPE_KW_INTEGER)
						{
							if(operIgual == DATATYPE_KW_FLOATING)
								printf("WARNING - Line %d: Loss of precision - float in vector!!!\n", root->lineNumber);
							else
								printf("ERRO - Line %d: Vector containing wrong parameters!!!\n", root->lineNumber);
						}
						operIgual = analisaExpressao(root->scc[1], rootAux);
						if(root->scc[0]->symbol->content.dataType != operIgual)
						{
							if(root->scc[1]->type == AST_exprComTK_IDENTIFIER)
								if(root->scc[1]->symbol->content.type != SYMBOL_FUNCTION)
									printf("ERRO - Line %d: Variable %s is not declared as a function, but it is being used as one!!!\n", root->lineNumber, root->scc[1]->symbol->content.text);
							switch(root->scc[0]->symbol->content.dataType)
							{
								case DATATYPE_KW_INTEGER:
									if(operIgual == DATATYPE_KW_FLOATING)
										printf("WARNING - Line %d: Loss of precision - different types, putting float into integer!!!\n", root->lineNumber);
									else
										printf("ERRO - Line %d: Variables containing different types!!!\n", root->lineNumber);
									break;
								case DATATYPE_KW_FLOATING:
									if((operIgual == DATATYPE_KW_CHARACTER) || (operIgual == DATATYPE_KW_BOOLEAN))
										printf("ERRO - Line %d: Variables containing different types!!!\n", root->lineNumber);
									break;
								case DATATYPE_KW_CHARACTER:
									if(operIgual != DATATYPE_KW_BOOLEAN)
										printf("ERRO - Line %d: Variables containing different types!!!\n", root->lineNumber);
									else
										printf("ERRO - Line %d: Variable does not match!!!\n", root->lineNumber);
									break;
								case DATATYPE_KW_BOOLEAN:
									printf("ERRO - Line %d: Variable does not match!!!\n", root->lineNumber);
									break;
							}
						}
						else
							if(root->scc[1]->type == AST_exprComTK_IDENTIFIER)
								if(root->scc[1]->symbol->content.type != SYMBOL_FUNCTION)
									printf("ERRO - Line %d: Variable %s is not declared as a function, but it is being used as one!!!\n", root->lineNumber, root->scc[1]->symbol->content.text);
					}
				}
			}
			break;
		default:
			break;
	}
	for(i=0; i < MAX_NODE; i++)
			checkUtilization(root->scc[i], rootAux);
}

int analisaExpressao(ASTREE *ast, ASTREE *rootAux)
{
	int help, verified, expr1, expr2;
	
	if(ast != 0)
	{
		switch(ast->type)
		{
			case AST_TK_IDENTIFIER:
				funcAst = 0;
				scalDecl = 0;
				checkVarDeclAsFunc(rootAux, ast->symbol->content.text);
				if(scalDecl == 1)
				{
					if(funcAst->symbol->content.type == SYMBOL_FUNCTION)
						printf("ERRO - Line %d: Variable %s is using the same name of a function!!!\n", ast->lineNumber, ast->symbol->content.text);
					else
						printf("ERRO - Line %d: Variable %s is declared as a vector!!!\n", ast->lineNumber, ast->symbol->content.text);
				}
				help = ast->symbol->content.dataType;
				break;
			case AST_LIT_INTEGER:
				help = DATATYPE_KW_INTEGER;
				break;
			case AST_LIT_FLOATING:
				help = DATATYPE_KW_FLOATING;
				break;
			case AST_LIT_TRUE:
				help = DATATYPE_KW_BOOLEAN;
				break;
			case AST_LIT_FALSE:
				help = DATATYPE_KW_BOOLEAN;
				break;
			case AST_LIT_CHAR:
				help = DATATYPE_KW_CHARACTER;
				break;
			case AST_exprComTK_IDENTIFIER:
				if(ast->symbol->content.dataType == 0)
				{
					help = 0;
				}
				else
					help = ast->symbol->content.dataType;
				break;
			case AST_exprComParent:
				help = analisaExpressao(ast->scc[0], rootAux);
				break;
			case AST_ADD:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_SUB:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_MUL:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_DIV:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_NEG:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				if(expr1 != 0)
					help = expr1;
				else
					help = 0;
				break;
			case AST_OPERATOR_AND:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_OPERATOR_OR:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_OPERATOR_LE:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_OPERATOR_GE:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_OPERATOR_EQ:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_OPERATOR_NE:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_MAIOR:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_MENOR:
				expr1 = analisaExpressao(ast->scc[0], rootAux);
				expr2 = analisaExpressao(ast->scc[1], rootAux);
				verified = checkOperationTypes(expr1, expr2);
				help = checkResultOperTypes(verified, expr1, expr2, ast->lineNumber);
				break;
			case AST_TK_IDENTIFIER_VET:
				funcAst = 0;
				scalDecl = 0;
				checkVarDeclAsFunc(rootAux, ast->symbol->content.text);
				if(scalDecl == 1)
				{
					if(funcAst->symbol->content.type == SYMBOL_FUNCTION)
						printf("ERRO - Line %d: Variable %s is using the same name of a function!!!\n", ast->lineNumber, ast->symbol->content.text);
				}
				if(ast->symbol->content.dataType != 0)
					help = ast->symbol->content.dataType;
				else
					help = 0;
				break;
			default:
				help = 0;
				break;			
		}
	}
	return help;
}

int checkOperationTypes(int expr1, int expr2)
{
	if((expr1 != 0) && (expr2 != 0))
	{
		if(expr1 != expr2)
		{
			if((expr1 == DATATYPE_KW_BOOLEAN) || (expr2 == DATATYPE_KW_BOOLEAN))
			{
				return 1;
			}
			if((expr1 == DATATYPE_KW_CHARACTER) || (expr2 == DATATYPE_KW_CHARACTER))
			{
				return 2;
			}
			if((expr1 == DATATYPE_KW_INTEGER) || (expr2 == DATATYPE_KW_INTEGER))
			{
				if((expr1 == DATATYPE_KW_FLOATING) || (expr2 == DATATYPE_KW_FLOATING))
					return 3;
			}
			else
			{
				if((expr1 == DATATYPE_KW_INTEGER) || (expr2 == DATATYPE_KW_INTEGER))
					return 3;
			}
		}
		else
		{
			return 4;
		}
	}
	else
	{
		return 0;
	}
}

int checkResultOperTypes(int verified, int expr1, int expr2, int lineNumber)
{
	int help;

	if(verified == 0)
	{
		printf("ERRO - Line %d: Undeclared variables operation!!!\n", lineNumber);
		help = 0;
	}
	else
	{
		if(verified == 1)
		{
			printf("WARNING - Line %d: boolean variable in the operation!!!\n", lineNumber);
		}
		else
		{
			if(verified == 2)
			{
				printf("WARNING - Line %d: character variable in the operation!!!\n", lineNumber);
			}
			if(verified == 3)
				printf("WARNING - Line %d: operation between integer and float variable!!!\n", lineNumber);
		}
		if(expr1 >= expr2)
			help = expr1;
		else
			help = expr2;
	}
	return help;
}

int checkParamsFunc(ASTREE *ast, ASTREE *filho)
{
	int cont = 0;
	ASTREE *nodeFilho = 0;

	nodeFilho = filho->scc[0];

	do{

	if(ast == 0)
	{
		if(nodeFilho != 0)
		{
			cont = 1;
			return cont;
		}
		else
		{
			cont = 0;
			return cont;
		}
	}
	else
	{
		if(nodeFilho == 0)
		{
			cont = 2;
			return cont;
		}
		else
		{
			switch(ast->scc[0]->symbol->content.dataType)
			{
				case DATATYPE_KW_INTEGER:
					if(nodeFilho->scc[0]->scc[0] != 0)
					{
						if(nodeFilho->scc[0]->scc[0]->type != AST_LIT_INTEGER)
						{
							cont = 3;
							return cont;
						}
					}
					else
					{
						if(nodeFilho->scc[0]->symbol->content.dataType != DATATYPE_KW_INTEGER)
						{
							cont = 3;
							return cont;
						}
					}	
					break;
				case DATATYPE_KW_FLOATING:
					if(nodeFilho->scc[0]->scc[0] != 0)
					{
						if(nodeFilho->scc[0]->scc[0]->type != AST_LIT_FLOATING)
						{
							cont = 3;
							return cont;
						}
					}
					else
					{
						if(nodeFilho->scc[0]->symbol->content.dataType != DATATYPE_KW_FLOATING)
						{
							cont = 3;
							return cont;
						}
					}
					break;
				case DATATYPE_KW_CHARACTER:
					if(nodeFilho->scc[0]->scc[0] != 0)
					{
						if(nodeFilho->scc[0]->scc[0]->type != AST_LIT_CHAR)
						{
							cont = 3;
							return cont;
						}
					}
					else
					{
						if(nodeFilho->scc[0]->symbol->content.dataType != DATATYPE_KW_CHARACTER)
						{
							cont = 3;
							return cont;
						}
					}
					break;
				case DATATYPE_KW_BOOLEAN:
					if(nodeFilho->scc[0]->scc[0] != 0)
					{
						if((nodeFilho->scc[0]->scc[0]->type != AST_LIT_TRUE) && (nodeFilho->scc[0]->scc[0]->type != AST_LIT_FALSE))
						{
							cont = 3;
							return cont;
						}
					}
					else
					{
						if(nodeFilho->scc[0]->symbol->content.dataType != DATATYPE_KW_BOOLEAN)
						{
							cont = 3;
							return cont;
						}
					}
					break;
				default:
					break;
			}
		}
	}
	ast = ast->scc[1];
	nodeFilho = nodeFilho->scc[1];
	}while(1);

}

void checkUndeclared()
{
	int address, result;
	HASH_NODE *node;

	for(address=1;address < MY_PRIME_NR; address++)
		if(hashTable[address])
			for(node=hashTable[address]; node!=0; node=node->next)
				if(node->content.type == SYMBOL_TK_IDENTIFIER)
						printf("ERRO - Line %d: Expression %s is missing declaration!!!\n", node->content.lineNumber, node->content.text);
}
