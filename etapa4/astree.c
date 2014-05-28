/*
// UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 4
//
// Alunos: Guilherme Schwade e Guilherme Pretto.
//
// Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "astree.h"

int myFuncType = 0;
int thereIsReturn = 0;

ASTREE * astCreate(int type, HASH_NODE *symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3, int lineNumber)
{
	ASTREE *node;
	node = (ASTREE*) calloc (1, sizeof(ASTREE));
	node->type = type;
	node->symbol = symbol;
	node->son[0] = s0;
	node->son[1] = s1;
	node->son[2] = s2;
	node->son[3] = s3;
	node->lineNumber = lineNumber;
	return node;
}

void astPrintSingle(ASTREE *node)
{
	if (node == 0)
	{
		return;
	}

	printf("ASTREE(");
	switch (node->type)
	{
		case ASTREE_DEF_SYMBOL:				printf("SYMBOL, ");		break; //Leaf
		case ASTREE_DEF_ADD:				printf("ADD, ");			break; //ok
		case ASTREE_DEF_SUB:				printf("SUB, ");			break; //ok
		case ASTREE_DEF_MUL: 				printf("MUL, ");			break; //ok
		case ASTREE_DEF_LESS: 				printf("LESS, ");			break; //ok
		case ASTREE_DEF_GREATER: 			printf("GREATER, ");		break; //ok
		case ASTREE_DEF_OP_LE:				printf("OP_LE, ");		break; //ok
		case ASTREE_DEF_OP_GE:				printf("OP_GE, ");		break; //ok
		case ASTREE_DEF_OP_EQ:				printf("OP_EQ, ");		break; //ok
		case ASTREE_DEF_OP_NE:				printf("OP_NE, ");		break; //ok
		case ASTREE_DEF_OP_AND:				printf("OP_AND, ");		break; //ok
		case ASTREE_DEF_OP_OR:				printf("OP_OR, ");		break; //ok
		case ASTREE_DEF_INPUT: 				printf("INPUT, ");		break; //ok
		case ASTREE_DEF_OUTPUT: 			printf("OUTPUT, ");		break; //ok
		case ASTREE_DEF_RETURN: 			printf("RETURN, ");		break; //ok
		case ASTREE_DEF_IF:					printf("IF,");				break; //ok
		case ASTREE_DEF_IFELSE: 			printf("IFELSE, ");		break; //ok
		case ASTREE_DEF_LOOP: 				printf("LOOP, ");			break; //ok
		case ASTREE_DEF_FUNC_CALL: 			printf("FUNC_CALL, ");	break; //ok
		case ASTREE_DEF_REF:				printf("REF, ");			break; //ok
		case ASTREE_DEF_DEREF:				printf("DEREF, ");		break; //ok
		case ASTREE_DEF_DECL:				printf("DECL, ");			break; //ok
		case ASTREE_DEF_DECL_VEC: 			printf("DECL_VEC, ");	break; //ok
		case ASTREE_DEF_DECL_VEC_INIT:		printf("VEC_INI, ");		break; //ok
		case ASTREE_DEF_INIT_VEC:			printf("INIT_VEC, ");	break; //ok
		case ASTREE_DEF_DECL_POINTER: 		printf("DECL_POINT, ");	break; //ok
		case ASTREE_DEF_VEC_ACCESS: 		printf("VEC_ACCESS, ");	break; //ok
		case ASTREE_DEF_FUNC:	 			printf("FUNC, ");			break; //ok
		case ASTREE_DEF_PARAM:	 			printf("PARAM, ");		break; //ok
		case ASTREE_DEF_PARAM_POINTER:		printf("PARAM_POINT, ");break; //ok
		case ASTREE_DEF_PARAM_REF: 			printf("PARAM_REF, ");	break; //ok
		case ASTREE_DEF_COMMAND_BLOCK:		printf("COMM_BLOCK, ");	break; //ok
		case ASTREE_DEF_OUT_LST:			printf("OUT_LST, ");		break; //ok
		case ASTREE_DEF_ATTR:	 			printf("ATTR, ");			break; //ok
		case ASTREE_DEF_ATTR_VEC: 			printf("ATTR_VEC, ");	break; //ok
		case ASTREE_DEF_PROGRAM: 			printf("PROGRAM, ");		break; //default
		case ASTREE_DEF_SIMPLE_COMMAND:		printf("S_COMMAND, ");	break; //ok
		case ASTREE_DEF_BLOCK:				printf("BLOCK, ");		break; //ok
		default: 							printf("DEFAULT, "); 	break;

	};

	if (node-> symbol != 0)
	{
		printf("Text: %s, ", node -> symbol -> text);
		printf("Type: %d", node -> symbol -> type);
	}
	printf(")\n");

}

void astPrintTree(ASTREE *root, int level)
{
	int i;

	if (root == 0)
	{
		return;
	}
	for (i=0; i<level; ++i)
	{
		printf("  ");
	}
	astPrintSingle(root);
	for (i=0; i<MAX_SONS; ++i)
	{
		astPrintTree(root->son[i], level+1);
	}

}

void searchNode(ASTREE *root, ASTREE *returnNode, char *text)
{
	int i;

	if (root == 0)
	{
		return;
	}
	if(&root->symbol->text == &text){
		returnNode = root;	
	}
	for (i=0; i<MAX_SONS; ++i)
	{
		searchNode(root->son[i], returnNode, text);
	}
	
}

// Semantic

void astSetDeclaration(ASTREE *node, int *errors)
{
	int i;

	if (node == 0)
	{
		return;
	}

	if (node->type == ASTREE_DEF_DECL
	||  node->type == ASTREE_DEF_DECL_VEC
	||  node->type == ASTREE_DEF_DECL_VEC_INIT
	||  node->type == ASTREE_DEF_DECL_POINTER
	||  node->type == ASTREE_DEF_FUNC)
	{
		if (node->son[1]->symbol->type != SYMBOL_IDENTIFIER)
		{
			printf("LINE: %d - Redeclared variable (%s)\n", node->son[1]->lineNumber, node->son[1]->symbol->text);
			*errors = *errors + 1;
		}

		// Set a pointer to the node in the declaration in the HASH
		node->son[1]->symbol->decl = node;

		// Set the variable type in the Hash Table
		switch (node->son[0]->type)
		{
			case ASTREE_DEF_KWWORD: node->son[1]->symbol->datatype = DATATYPE_WORD; break;
			case ASTREE_DEF_KWBYTE: node->son[1]->symbol->datatype = DATATYPE_BYTE; break;
			case ASTREE_DEF_KWBOOL: node->son[1]->symbol->datatype = DATATYPE_BOOL; break;
			default: printf("-- ERROR --\n"); exit(10);		
		}

		// Look for a specific type of node
		switch (node->type)
		{
			case ASTREE_DEF_DECL:
				node->son[1]->symbol->type = SYMBOL_VARIABLE;
				switch (node->son[0]->type)
				{
					case ASTREE_DEF_KWWORD: 
						if(isBool(node->son[2]->symbol->text))
						{
							printf("LINE: %d - Variable wrong initialized (%s)\n", node->son[1]->lineNumber, node->son[1]->symbol->text);
							*errors = *errors + 1;
						}
						break;

					case ASTREE_DEF_KWBYTE:  
						if(isBool(node->son[2]->symbol->text))
						{
							printf("LINE: %d - Variable wrong initialized (%s)\n", node->son[1]->lineNumber, node->son[1]->symbol->text);
							*errors = *errors + 1;
						}
						break;

					case ASTREE_DEF_KWBOOL: 
						if(!isBool(node->son[2]->symbol->text))
						{
							printf("LINE: %d - Variable wrong initialized (%s)\n", node->son[1]->lineNumber, node->son[1]->symbol->text);
							*errors = *errors + 1;
						}
						break;

					default: printf("-- ERROR --\n"); exit(10);		
				}
				break;
			case ASTREE_DEF_DECL_VEC:
				node->son[1]->symbol->type = SYMBOL_VECTOR;
				break;
			case ASTREE_DEF_DECL_VEC_INIT:
				node->son[1]->symbol->type = SYMBOL_VECTORINIT; 
				break;
			case ASTREE_DEF_DECL_POINTER:	
				node->son[1]->symbol->type = SYMBOL_POINTER;
				break;
			case ASTREE_DEF_FUNC:
				node->son[1]->symbol->type = SYMBOL_FUNCTION;
				astSetParamDeclaration(node->son[2], errors); 
				break;
			default: printf("-- ERROR --\n"); exit(10);
		}
	}
	

	for (i=0; i<MAX_SONS; ++i)
	{
		astSetDeclaration(node->son[i], errors);
	}
}

void astSetParamDeclaration(ASTREE *node, int *errors)
{

	while (node)
	{
		if (node->son[1]->symbol->type != SYMBOL_IDENTIFIER)
		{
			printf("LINE: %d - Redeclared variable < %s > as a parameter\n", node->son[1]->lineNumber, node->son[1]->symbol->text);
			*errors = *errors + 1;
		}
		else
		{
			node->son[1]->symbol->type = SYMBOL_VARIABLE;
			switch (node->son[0]->type)
			{
				case ASTREE_DEF_KWWORD: node->son[1]->symbol->datatype = DATATYPE_WORD; break;
				case ASTREE_DEF_KWBYTE: node->son[1]->symbol->datatype = DATATYPE_BYTE; break;
				case ASTREE_DEF_KWBOOL: node->son[1]->symbol->datatype = DATATYPE_BOOL; break;
				default: printf("-- ERROR --\n"); exit(10);
			}
		}

		node = node->son[2];
	}
}


void astCheckNature(ASTREE *node, int *errors)
{
	ASTREE *rootTree = node;
	int i;

	if (node == 0)
	{
		return;
	}

	switch (node->type)
	{
		case ASTREE_DEF_SYMBOL:
			switch (node->symbol->type)
			{
				case SYMBOL_LIT_INTEGER:node->datatype = ASTREE_DEF_LIT_INTEGER;	break;
				case SYMBOL_LIT_TRUE: 	node->datatype = ASTREE_DEF_BOOL; 			break;
				case SYMBOL_LIT_FALSE: 	node->datatype = ASTREE_DEF_BOOL; 			break;
				case SYMBOL_LIT_CHAR:   node->datatype = ASTREE_DEF_LIT_CHAR; 		break;
				case SYMBOL_LIT_STRING: node->datatype = ASTREE_DEF_LIT_STRING; 	break;
				case SYMBOL_POINTER:		node->datatype = ASTREE_DEF_POINTER; 		break;
				case SYMBOL_IDENTIFIER:
				case SYMBOL_VECTOR:
				case SYMBOL_VECTORINIT:
				case SYMBOL_FUNCTION:
				case SYMBOL_VARIABLE:	
					switch (node->symbol->datatype)
					{
						case DATATYPE_BOOL: node->datatype = ASTREE_DEF_BOOL; break;
						case DATATYPE_BYTE: node->datatype = ASTREE_DEF_BYTE; break;
						case DATATYPE_WORD: node->datatype = ASTREE_DEF_WORD; break;
					}
					break;
				default: break;
			}	
			break;
		
		case ASTREE_DEF_DECL:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			astCheckNature(node->son[2], errors);
			break;

		case ASTREE_DEF_DECL_POINTER: 	
			node->son[1]->datatype = ASTREE_DEF_POINTER;
			break;

		case ASTREE_DEF_ADD:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			
			if ((node->son[0]->datatype == ASTREE_DEF_POINTER) || (node->son[1]->datatype == ASTREE_DEF_POINTER))
			{
				if((node->son[0]->datatype == ASTREE_DEF_POINTER) && (node->son[1]->datatype == ASTREE_DEF_POINTER))
				{

					printf("LINE: %d - DD two pointers\n", node->son[1]->lineNumber);
					*errors = *errors + 1;
				}
				else
				{
					node->datatype = ASTREE_DEF_POINTER;
					node->lineNumber = node->son[0]->lineNumber;		
				}
			}
			else
			{ 
				if (((node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER) && 
					  (node->son[0]->datatype != ASTREE_DEF_LIT_CHAR) && 
					  (node->son[0]->datatype != ASTREE_DEF_WORD) &&
					  (node->son[0]->datatype != ASTREE_DEF_BYTE)) ||
					 ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && 
					  (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR) && 
					  (node->son[1]->datatype != ASTREE_DEF_WORD) && 
					  (node->son[1]->datatype != ASTREE_DEF_BYTE)))
				{
					printf("LINE: %d - ADD with undefined types or variables\n", node->son[1]->lineNumber);
					*errors = *errors + 1;
				}
				else
				{
					node->datatype = node->son[0]->datatype;
					node->lineNumber = node->son[0]->lineNumber;
				}
			}
			break;

		case ASTREE_DEF_SUB:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);

			if ((node->son[0]->datatype == ASTREE_DEF_POINTER) || (node->son[1]->datatype == ASTREE_DEF_POINTER))
			{
				if((node->son[0]->datatype == ASTREE_DEF_POINTER) && (node->son[1]->datatype == ASTREE_DEF_POINTER))
				{

					printf("LINE: %d - DD two pointers\n", node->son[1]->lineNumber);
					*errors = *errors + 1;
				}
				else
				{
					node->datatype = ASTREE_DEF_POINTER;
					node->lineNumber = node->son[0]->lineNumber;		
				}
			}
			else
			{ 
				if (((node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER) && 
					  (node->son[0]->datatype != ASTREE_DEF_LIT_CHAR) && 
					  (node->son[0]->datatype != ASTREE_DEF_WORD) &&
					  (node->son[0]->datatype != ASTREE_DEF_BYTE)) ||
					 ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && 
					  (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR) && 
					  (node->son[1]->datatype != ASTREE_DEF_WORD) && 
					  (node->son[1]->datatype != ASTREE_DEF_BYTE)))
				{
					printf("LINE: %d - SUB with undefined types or variables\n", node->son[1]->lineNumber);
					*errors = *errors + 1;
				}
				else
				{
					node->datatype = node->son[0]->datatype;
					node->lineNumber = node->son[0]->lineNumber;
				}
			}
			break;
				
		case ASTREE_DEF_MUL:
		case ASTREE_DEF_DIV:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			if ((node->son[0]->datatype == ASTREE_DEF_POINTER) || (node->son[1]->datatype == ASTREE_DEF_POINTER))
			{
				if(node->son[0]->type == 2)
				{
					printf("LINE: %d - OPERATION with pointer < %s >\n", node->son[1]->lineNumber, node->son[1]->symbol->text);
					*errors = *errors + 1;
				}
				else
				{
					printf("LINE: %d - OPERATION with pointer < %s %s >\n", node->son[1]->lineNumber, node->son[0]->symbol->text, node->son[1]->symbol->text);
					*errors = *errors + 1;
				}
			}
			else
			{
				if (((node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER) && 
					  (node->son[0]->datatype != ASTREE_DEF_LIT_CHAR) &&
					  (node->son[0]->datatype != ASTREE_DEF_WORD) && 
					  (node->son[0]->datatype != ASTREE_DEF_BYTE)) || 
					 ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && 
					  (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR) &&
					  (node->son[1]->datatype != ASTREE_DEF_WORD) && 
					  (node->son[1]->datatype != ASTREE_DEF_BYTE)))
				{
					printf("LINE: %d - OPERANDS with different types or undefined variables < %s %s >\n", node->son[1]->lineNumber, node->son[0]->symbol->text, node->son[1]->symbol->text);
					*errors = *errors + 1;
				}
				else
				{
					node->datatype = node->son[0]->datatype;
					node->lineNumber = node->son[0]->lineNumber;			
				}
			}
			break;

		case ASTREE_DEF_LESS:
		case ASTREE_DEF_GREATER:
		case ASTREE_DEF_OP_LE:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			node->lineNumber = node->son[0]->lineNumber;
			if ((node->son[0]->datatype != node->son[1]->datatype) && 
				 ((node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[0]->datatype != ASTREE_DEF_LIT_CHAR)) && 
				 ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR)))
			{
				printf("LINE: %d - OPERANDS with different types < %s %s >\n", node->son[1]->lineNumber, node->son[0]->symbol->text, node->son[1]->symbol->text);
				*errors = *errors + 1;
			}
			else
			{
				node->datatype = ASTREE_DEF_BOOL;		
			}
			break;

		case ASTREE_DEF_OP_GE:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			node->lineNumber = node->son[0]->lineNumber;
			if ((node->son[0]->datatype != node->son[1]->datatype) && 
				 ((node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[0]->datatype != ASTREE_DEF_LIT_CHAR)) && 
				 ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR)))
			{
				printf("LINE: %d - OPERANDS with different types < %s %s >\n", node->son[1]->lineNumber, node->son[0]->symbol->text, node->son[1]->symbol->text);
				*errors = *errors + 1;
			}
			else
			{
				node->datatype = ASTREE_DEF_BOOL;		
			}
			break;

		case ASTREE_DEF_OP_EQ:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			node->lineNumber = node->son[0]->lineNumber;
			if ((node->son[0]->datatype != node->son[1]->datatype) && 
				 ((node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[0]->datatype != ASTREE_DEF_LIT_CHAR)) && 
				 ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR)))
			{
				printf("LINE: %d - OPERANDS with different types < %s %s >\n", node->son[1]->lineNumber, node->son[0]->symbol->text, node->son[1]->symbol->text);
				*errors = *errors + 1;
			}
			else
			{
				node->datatype = ASTREE_DEF_BOOL;		
			}
			break;

		case ASTREE_DEF_OP_NE:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			node->lineNumber = node->son[0]->lineNumber;
			if ((node->son[0]->datatype != node->son[1]->datatype) && 
				 ((node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[0]->datatype != ASTREE_DEF_LIT_CHAR)) && 
				 ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR)))
			{
				printf("LINE: %d - OPERANDS with different types < %s %s >\n", node->son[1]->lineNumber, node->son[0]->symbol->text, node->son[1]->symbol->text);
				*errors = *errors + 1;
			}
			else
			{
				node->datatype = ASTREE_DEF_BOOL;		
			}
			break;

		case ASTREE_DEF_OP_AND:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			node->lineNumber = node->son[0]->lineNumber;
			if ((node->son[0]->datatype != node->son[1]->datatype) && 
				 ((node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[0]->datatype != ASTREE_DEF_LIT_CHAR)) && 
				 ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR)))
			{
				printf("LINE: %d - OPERANDS with different types < %s %s >\n", node->son[1]->lineNumber, node->son[0]->symbol->text, node->son[1]->symbol->text);
				*errors = *errors + 1;
			}
			else
			{
				node->datatype = ASTREE_DEF_BOOL;		
			}
			break;

		case ASTREE_DEF_OP_OR:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			node->lineNumber = node->son[0]->lineNumber;
			if ((node->son[0]->datatype != node->son[1]->datatype) && 
				 ((node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[0]->datatype != ASTREE_DEF_LIT_CHAR)) && 
				 ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && 
				  (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR)))
			{
				printf("LINE: %d - OPERANDS with different types < %s %s >\n", node->son[1]->lineNumber, node->son[0]->symbol->text, node->son[1]->symbol->text);
				*errors = *errors + 1;
			}
			else
			{
				node->datatype = ASTREE_DEF_BOOL;		
			}
			break;
	
		case ASTREE_DEF_IF:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			if (node->son[0]->datatype != ASTREE_DEF_BOOL)
			{
				printf("LINE: %d - IF cond < %s > not Bool\n", node->son[0]->lineNumber, node->son[0]->symbol->text);
				*errors = *errors + 1;
			}
			node->datatype =  node->son[1]->datatype;
			node->lineNumber = node->son[1]->lineNumber;			
			break;

		case ASTREE_DEF_IFELSE:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			astCheckNature(node->son[2], errors);
			if (node->son[0]->datatype != ASTREE_DEF_BOOL)
			{
				printf("LINE: %d - IFELSE condition not Bool\n", node->son[0]->lineNumber);
				*errors = *errors + 1;
			}
			if (node->son[1]->datatype == ASTREE_DEF_WORD || 
				 node->son[1]->datatype == ASTREE_DEF_BYTE || 
				 node->son[1]->datatype == ASTREE_DEF_BOOL || 
				 node->son[1]->datatype == ASTREE_DEF_LIT_INTEGER || 
				 node->son[1]->datatype == ASTREE_DEF_LIT_CHAR)
			{
				node->datatype =  node->son[1]->datatype;
			}
			else
			{
				if (node->son[2]->datatype == ASTREE_DEF_WORD || 
					 node->son[2]->datatype == ASTREE_DEF_BYTE || 
					 node->son[2]->datatype == ASTREE_DEF_BOOL || 
					 node->son[2]->datatype == ASTREE_DEF_LIT_INTEGER || 
					 node->son[2]->datatype == ASTREE_DEF_LIT_CHAR )
				{
					node->datatype = node->son[2]->datatype;
				}
				else
				{
					node->datatype = node->son[1]->datatype;
				}
			}
			node->lineNumber = node->son[1]->lineNumber;	
			break;

		case ASTREE_DEF_LOOP:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			node->lineNumber = node->son[0]->lineNumber;
			if (node->son[1]->datatype != ASTREE_DEF_BOOL)
			{
				printf("LINE: %d - LOOP cond < %d > not Bool\n", node->son[0]->lineNumber, node->son[1]->datatype);
				*errors = *errors + 1;
			}
			else
			{
				node->datatype = node->son[0]->datatype;		
			}
			break;

		case ASTREE_DEF_INPUT:
			astCheckNature(node->son[0], errors);
			if (node->son[0]->symbol->type != SYMBOL_VARIABLE)
			{
				printf("LINE: %d - INPUT not a variable\n", node->son[0]->lineNumber);
				*errors = *errors + 1;
			}
			else
			{
				node->datatype =  node->son[0]->datatype;
				node->lineNumber = node->son[0]->lineNumber;			
			}
			break;

		case ASTREE_DEF_OUTPUT:
			astCheckNature(node->son[0], errors);
			node->datatype =  node->son[0]->datatype;
			node->lineNumber = node->son[0]->lineNumber;			
			break;

		case ASTREE_DEF_OUT_LST:
			astCheckNature(node->son[0], errors);
			break;

		case ASTREE_DEF_FUNC:
			thereIsReturn = 0;
			astCheckNature(node->son[0], errors);
			switch (node->son[0]->type)
			{	
				case ASTREE_DEF_KWWORD: myFuncType = ASTREE_DEF_WORD; break;
				case ASTREE_DEF_KWBYTE: myFuncType = ASTREE_DEF_BYTE; break;
				case ASTREE_DEF_KWBOOL: myFuncType = ASTREE_DEF_BOOL; break;
			}
			astCheckNature(node->son[1], errors);
			astCheckNature(node->son[2], errors);
			astCheckNature(node->son[3], errors);
			if (!thereIsReturn)
			{
				printf("LINE: %d - FUNCTION < %s > has no return\n", node->son[0]->lineNumber, node->son[1]->symbol->text);
				*errors = *errors + 1;
			}
			node->datatype =  node->son[0]->datatype;
			node->lineNumber = node->son[0]->lineNumber;	
			break;
			
		case ASTREE_DEF_COMMAND_BLOCK:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			if(node->son[1] != 0)
			{
				if (node->son[1]->datatype == ASTREE_DEF_WORD || 
					 node->son[1]->datatype == ASTREE_DEF_BYTE || 
					 node->son[1]->datatype == ASTREE_DEF_BOOL || 
					 node->son[1]->datatype == ASTREE_DEF_LIT_INTEGER || 
					 node->son[1]->datatype == ASTREE_DEF_LIT_CHAR)
				{
					node->datatype =  node->son[1]->datatype;
				}
				else
				{ 
					node->datatype = node->son[0]->datatype;
				}
				node->lineNumber = node->son[1]->lineNumber;	
			}
			else
			{
				if (node->son[0] != 0)
				{
					node->datatype =  node->son[0]->datatype;
					node->lineNumber = node->son[0]->lineNumber;
				}
			}
			break;
		
		case ASTREE_DEF_SIMPLE_COMMAND:
		case ASTREE_DEF_BLOCK:
			astCheckNature(node->son[0], errors);
			if(node->son[0] != 0)
			{
				node->datatype =  node->son[0]->datatype;
				node->lineNumber = node->son[0]->lineNumber;
			}
			break;

		case ASTREE_DEF_RETURN:
			astCheckNature(node->son[0], errors);
			if((myFuncType == ASTREE_DEF_BOOL && node->son[0]->datatype != ASTREE_DEF_BOOL) ||
				((myFuncType == ASTREE_DEF_BYTE || myFuncType == ASTREE_DEF_WORD) && 
				 (node->son[0]->datatype != ASTREE_DEF_BYTE && node->son[0]->datatype != ASTREE_DEF_WORD &&
				  node->son[0]->datatype != ASTREE_DEF_LIT_CHAR && node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER)))
			{
				printf("LINE: %d - RETURN not correct type %d\n", node->son[0]->lineNumber, node->son[0]->datatype);
				*errors = *errors + 1;
			}
			thereIsReturn = 1;
			node->datatype = ASTREE_DEF_RETURN;
			node->lineNumber = node->son[0]->lineNumber;
			break;

		case ASTREE_DEF_VEC_ACCESS:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			if (((node->son[0]->datatype != ASTREE_DEF_BOOL) && 
				  (node->son[0]->datatype != ASTREE_DEF_BYTE) && 
				  (node->son[0]->datatype != ASTREE_DEF_WORD)) ||
				 ((node->son[0]->symbol->type != SYMBOL_VECTOR) &&
				  (node->son[0]->symbol->type != SYMBOL_VECTORINIT)))
			{
				printf("LINE: %d - VEC_ACCESS not correct type\n", node->son[0]->lineNumber);
				*errors = *errors + 1;
			}
			else
			{
				if ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && 
					 (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR) && 
					 (node->son[1]->datatype != ASTREE_DEF_WORD) && 
					 (node->son[1]->datatype != ASTREE_DEF_BYTE))
				{
					printf("LINE: %d - VEC_ACCESS not correct index\n", node->son[0]->lineNumber);
					*errors = *errors + 1;
				}
				else
				{
					node->datatype = node->son[0]->datatype;
					node->lineNumber = node->son[0]->lineNumber;
				}		
			}
			break;

		case ASTREE_DEF_FUNC_CALL:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			if (node->son[0]->symbol->type != SYMBOL_FUNCTION)
			{
				printf("LINE: %d - FUNC_CALL < %s > is not function\n", node->son[0]->lineNumber, node->son[0]->symbol->text);
				*errors = *errors + 1;
			}
			else 
			{
				ASTREE *nodeArgList;
				ASTREE *nodeParamList;
				nodeArgList = node->son[1];
				nodeParamList = node->son[0]->symbol->decl->son[2];
				while (nodeArgList && nodeParamList)
				{
					astCheckNature(nodeArgList->son[0], errors);
					if (!((nodeArgList->son[0]->datatype == ASTREE_DEF_BOOL && 
							 nodeParamList->son[1]->datatype == ASTREE_DEF_BOOL) || 
							((nodeArgList->son[0]->datatype == ASTREE_DEF_LIT_INTEGER ||
							  nodeArgList->son[0]->datatype == ASTREE_DEF_LIT_CHAR || 
							  nodeArgList->son[0]->datatype == ASTREE_DEF_WORD ||
							  nodeArgList->son[0]->datatype == ASTREE_DEF_BYTE) &&
							 (nodeParamList->son[1]->datatype == ASTREE_DEF_WORD || 
							  nodeParamList->son[1]->datatype == ASTREE_DEF_BYTE)))) 
					{
						printf("LINE: %d - FUNC_CALL < %s > mismatch datatypes (%d %d)\n", nodeArgList->son[0]->lineNumber, node->son[0]->symbol->text, nodeArgList->son[0]->datatype, nodeParamList->son[1]->datatype);
						*errors = *errors + 1;
					}
					nodeArgList = nodeArgList->son[1];
					nodeParamList = nodeParamList->son[2];
				}
				if (nodeArgList || nodeParamList)
				{
					printf("LINE: %d - FUNC_CALL wrong param number\n", node->son[0]->lineNumber);
					*errors = *errors + 1;
				}
				else
				{			
					node->datatype = node->son[0]->datatype;
					node->lineNumber = node->son[0]->lineNumber;
				}
			}
			break;

		case ASTREE_DEF_REF:
			astCheckNature(node->son[0], errors);
			node->datatype = ASTREE_DEF_POINTER;
			node->son[0]->datatype = ASTREE_DEF_POINTER;
			node->lineNumber = node->son[0]->lineNumber;	
			break;

		case ASTREE_DEF_DEREF:
			astCheckNature(node->son[0], errors);
			node->datatype = ASTREE_DEF_LIT_INTEGER;
			node->son[0]->datatype = ASTREE_DEF_POINTER;
			node->lineNumber = node->son[0]->lineNumber;	
			break;

		case ASTREE_DEF_PARAM:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			astCheckNature(node->son[2], errors);
			break;
			
		case ASTREE_DEF_PARAM_POINTER:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			astCheckNature(node->son[2], errors);
			break;

		case ASTREE_DEF_ATTR:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			if(node->son[0]->symbol->type == SYMBOL_FUNCTION)
			{
				printf("LINE: %d - ATTRIBUTION can`t use function in the left side\n", node->son[0]->lineNumber);
				*errors = *errors + 1;
			}
			else
			{ 
				if (node->son[1]->type == ASTREE_DEF_SYMBOL)
				{
					if ((node->son[1]->symbol->type == SYMBOL_VECTOR || 
						  node->son[1]->symbol->type == SYMBOL_VECTORINIT) && 
						 (node->son[1]->type != ASTREE_DEF_VEC_ACCESS))
					{
						printf("LINE: %d - ATTRIBUTION vector without index < %s = %s >\n", node->son[1]->lineNumber, node->son[0]->symbol->text, node->son[1]->symbol->text);
						*errors = *errors + 1;
					}
					else
					{ 
						if ((node->son[0]->datatype != ASTREE_DEF_POINTER && 
							  node->son[1]->datatype == ASTREE_DEF_POINTER) || 
							 (node->son[0]->datatype == ASTREE_DEF_POINTER && 
							  node->son[1]->datatype != ASTREE_DEF_POINTER))
						{
							printf("LINE: %d - ATTRIBUTION with different types (pointer)\n", node->son[0]->lineNumber);
							*errors = *errors + 1;
						}
						else 
						{
							if(node->son[1]->symbol->type == SYMBOL_FUNCTION)
							{
								printf("LINE: %d - ATTRIBUTION missing bracket in function\n", node->son[0]->lineNumber);
								*errors = *errors + 1;
							}
						}
					}
				}
				else 
				{
					if ((node->son[0]->datatype != ASTREE_DEF_POINTER && node->son[1]->datatype == ASTREE_DEF_POINTER) ||
						 (node->son[0]->datatype == ASTREE_DEF_POINTER && node->son[1]->datatype != ASTREE_DEF_POINTER) || 
						 (node->son[0]->datatype == ASTREE_DEF_BOOL && node->son[1]->datatype != ASTREE_DEF_BOOL) || 
						 (node->son[0]->datatype != ASTREE_DEF_BOOL && node->son[1]->datatype == ASTREE_DEF_BOOL))	
					{
						printf("LINE: %d - ATTRIBUTION with different types\n", node->son[0]->lineNumber);
						*errors = *errors + 1;
					}
					else
					{
						if (node->son[1]->datatype == ASTREE_DEF_LIT_STRING)
						{
							printf("LINE: %d - ATTRIBUTION with string < %s >\n", node->son[1]->lineNumber, node->son[1]->symbol->text);
							*errors = *errors + 1;
						}
						else
						{
							node->datatype = node->son[0]->datatype;
							node->lineNumber = node->son[0]->lineNumber;
						}	
					}
				}
			}
			break;

		case ASTREE_DEF_ATTR_VEC:
			astCheckNature(node->son[0], errors);
			astCheckNature(node->son[1], errors);
			astCheckNature(node->son[2], errors);
			// Check Index
			if ((node->son[1]->datatype != ASTREE_DEF_LIT_INTEGER) && (node->son[1]->datatype != ASTREE_DEF_LIT_CHAR))
			{
				printf("LINE: %d - Vector index is not int or char\n", node->son[1]->lineNumber);
				*errors = *errors + 1;
			}
			// Check value
			else 
			{
				if (((node->son[0]->datatype != ASTREE_DEF_LIT_INTEGER) && (node->son[0]->datatype != ASTREE_DEF_LIT_CHAR) 						&& (node->son[0]->datatype != ASTREE_DEF_WORD) && (node->son[0]->datatype != ASTREE_DEF_BYTE)) || 
					 ((node->son[2]->datatype != ASTREE_DEF_LIT_INTEGER) && (node->son[2]->datatype != ASTREE_DEF_LIT_CHAR) 						&& (node->son[2]->datatype != ASTREE_DEF_WORD) && (node->son[2]->datatype != ASTREE_DEF_BYTE)))
				{
					printf("LINE: %d - Vector attribution with different types (%s %d %s)\n", node->son[1]->lineNumber, node->son[0]->symbol->text, node->type, node->son[2]->symbol->text);
					*errors = *errors + 1;
				}
				else
				{
					node->datatype = node->son[0]->datatype;
					node->lineNumber = node->son[0]->lineNumber;			
				}
			}
			break;

		default:
			for (i=0; i<MAX_SONS; ++i)
			{
				astCheckNature(node->son[i], errors);
			}
			break;
	}
	
}

void internalCompile(ASTREE *root, FILE * out)
{
	int i;
	if (root == 0)
	{
		return;
	}
	for (i=0; i<MAX_SONS; ++i)
	{
		astCompile(root->son[i], out);
	}
}

int isNumber(char *input)
{
	int i;	
	for(i =0; input[i] != '\0'; i++)
	{
		if(isalpha(input[i]))
			return 0;	
	}
	return 1;
}

int isBool(char *input)
{
	int i,size;
	size =0;	
	for(i =0; input[i] != '\0'; i++)
	{
		size++;	
	}
	if(size >= 4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void astCompile(ASTREE *root, FILE * out)
{
	int i;
	
	if(root == 0)
	{
		return;
	}

		
	switch (root->type)
	{
		case ASTREE_DEF_DECL:
			astCompile(root->son[0], out);			
			astCompile(root->son[1], out);
			fprintf(out, ":");
			astCompile(root->son[2], out);
			fprintf(out, ";\n");
			break;

		case ASTREE_DEF_DECL_VEC:
			astCompile(root->son[0], out);
			astCompile(root->son[1], out);
			fprintf(out, "[%s", root->symbol->text);
			fprintf(out, "];\n");
			break;

		case ASTREE_DEF_DECL_VEC_INIT:
			astCompile(root->son[0], out);
			astCompile(root->son[1], out);
			fprintf(out, "[%s", root->symbol->text);
			fprintf(out, "]:");
			astCompile(root->son[2], out);
			fprintf(out, ";\n");
			break;

		case ASTREE_DEF_INIT_VEC:
			astCompile(root->son[0], out);
			fprintf(out, " ");
			astCompile(root->son[1], out);
			break;

		case ASTREE_DEF_DECL_POINTER:
			astCompile(root->son[0], out);
			fprintf(out, "$");
			astCompile(root->son[1], out);
			fprintf(out, ":");
			astCompile(root->son[2], out);
			fprintf(out, ";\n");			
			break;

		case ASTREE_DEF_FUNC:	
			astCompile(root->son[0], out);
			astCompile(root->son[1], out);
			fprintf(out,"(");
			astCompile(root->son[2], out);
			fprintf(out,")\n");	
			astCompile(root->son[3], out);
			fprintf(out,";\n");
			break;

		case ASTREE_DEF_PARAM:
			astCompile(root->son[0], out);
			astCompile(root->son[1], out);
			if(root->son[2] != 0)
			{
				fprintf(out, ", ");
				astCompile(root->son[2], out);
			}
			break;

		case ASTREE_DEF_PARAM_POINTER:
			astCompile(root->son[0], out);
			fprintf(out, "$ ");
			astCompile(root->son[1], out);
			if(root->son[2] != 0)
			{ 
				fprintf(out, ", ");
				astCompile(root->son[1], out);
			}
			break;

		case ASTREE_DEF_COMMAND_BLOCK:	
			internalCompile(root, out);
			break;

		case ASTREE_DEF_BLOCK:	
			fprintf(out, "{\n");
			astCompile(root->son[0], out);
			fprintf(out, "}\n");
			break;
		
		case ASTREE_DEF_SIMPLE_COMMAND:	
			astCompile(root->son[0], out);
			break;

		case ASTREE_DEF_OUTPUT:
			fprintf(out, "output ");
			astCompile(root->son[0], out);
			fprintf(out, "\n");	
			break;

		case ASTREE_DEF_LOOP:	
			fprintf(out, "loop\n");
			astCompile(root->son[0], out);	
			fprintf(out, "(");
			astCompile(root->son[1], out);	
			fprintf(out, ")\n");
			break;

		case ASTREE_DEF_ATTR:	
			astCompile(root->son[0], out); 	
			fprintf(out, " = ");
			astCompile(root->son[1], out);
			fprintf(out, "\n");	
			break;

		case ASTREE_DEF_ATTR_VEC:	
			astCompile(root->son[0], out); 	
			fprintf(out, "[");
			astCompile(root->son[1], out);
			fprintf(out, "]");
			fprintf(out, " = ");
			astCompile(root->son[2], out);
			fprintf(out, "\n");	
			break;

		case ASTREE_DEF_VEC_ACCESS:	
			astCompile(root->son[0], out); 	
			fprintf(out, "[");
			astCompile(root->son[1], out);
			fprintf(out, "]");	
			break;

		case ASTREE_DEF_FUNC_CALL:
			astCompile(root->son[0], out);
			fprintf(out, "(");
			astCompile(root->son[1], out);
			fprintf(out, ")\n");		
			break;

		case ASTREE_DEF_PARAM_REF:
			astCompile(root->son[0], out);
			if(root->son[1] != 0){
				fprintf(out, ", ");
				astCompile(root->son[1], out);
			}
			break;

		case ASTREE_DEF_ADD:		
			astCompile(root->son[0], out);
			fprintf(out, "+");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_SUB:		
			astCompile(root->son[0], out);
			fprintf(out, "-");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_MUL:		
			astCompile(root->son[0], out);
			fprintf(out, "*");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_LESS:		
			astCompile(root->son[0], out);
			fprintf(out, "<");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_GREATER:		
			astCompile(root->son[0], out);
			fprintf(out, ">");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_OP_LE:		
			astCompile(root->son[0], out);
			fprintf(out, "<=");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_OP_GE:		
			astCompile(root->son[0], out);
			fprintf(out, ">=");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_OP_EQ:		
			astCompile(root->son[0], out);
			fprintf(out, "==");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_OP_NE:		
			astCompile(root->son[0], out);
			fprintf(out, "!=");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_OP_AND:		
			astCompile(root->son[0], out);
			fprintf(out, "&&");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_OP_OR:		
			astCompile(root->son[0], out);
			fprintf(out, "||");
			astCompile(root->son[1], out);	
			break;

		case ASTREE_DEF_OUT_LST:
			astCompile(root->son[0], out);
			if(root->son[1] != 0)
			{
				fprintf(out, ",");
				astCompile(root->son[1], out);
			}	
			break;

		case ASTREE_DEF_INPUT: 	
			fprintf(out, "input ");
			astCompile(root->son[0], out);
			fprintf(out, "\n");
			break;

		case ASTREE_DEF_IFELSE: 	
			fprintf(out, "\nif (");
			astCompile(root->son[0], out);
			fprintf(out, ") else ");
			astCompile(root->son[1], out);
			fprintf(out, " then ");
			astCompile(root->son[2], out);
			fprintf(out, "\n");
			break;
 
		case ASTREE_DEF_RETURN: 	
			fprintf(out, "return ");
			astCompile(root->son[0], out);
			fprintf(out, "\n");
			break;

		case ASTREE_DEF_IF:
			fprintf(out, "\nif (");
			astCompile(root->son[0], out);
			fprintf(out, ") then ");
			astCompile(root->son[1], out);
			fprintf(out, "\n");
			break;

		case ASTREE_DEF_KWWORD:
			fprintf(out, "word ");
			break;

		case ASTREE_DEF_KWBOOL:
			fprintf(out, "bool ");
			break;

		case ASTREE_DEF_KWBYTE:
			fprintf(out, "byte ");
			break;

		case ASTREE_DEF_REF:
			fprintf(out, "&");
			astCompile(root->son[0], out);
			fprintf(out, "\n");
			break;
		
		case ASTREE_DEF_DEREF:
			fprintf(out, "$");
			astCompile(root->son[0], out);
			fprintf(out, "\n");
			break;

		default:
			internalCompile(root, out);
			if(root->son[0] == 0)
			{
				if (root -> symbol != 0)
				{
					fprintf(out, "%s", root->symbol->text);
					return;
				}
			}
			break;
	};
}