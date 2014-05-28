/*
UFRGS - Compiladores B - Marcelo Johann - 2012/1 - Etapa 4

Alunos: Daniel Henrique Grehs e Victoria Ramos Pires.

Matrículas: 213998 e 213997.
*/

#include "astree.h"
FILE *ExitTree;

ASTREE *astCreate(int type, struct sHASH_NODE *symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3)
{
	ASTREE *newNode;
	
	newNode = (ASTREE*)calloc(1,sizeof(ASTREE));
	newNode->type = type;
	newNode->symbol = symbol;
	newNode->scc[0] = s0;
	newNode->scc[1] = s1;
	newNode->scc[2] = s2;
	newNode->scc[3] = s3;
	newNode->impresso = 0;
	newNode->lineNumber = getLineNumber();
	return newNode;
}

void *astPrintTree(ASTREE *root)
{
	int i;
	if(root==NULL) return;
	astPrintNode(root);
	for(i=0; i<MAX_NODE; i++)
	   astPrintTree(root->scc[i]);
}

void *astPrintNode(ASTREE *node)
{
	if(node==NULL) return;
	if(node->impresso==1)return;
	node->impresso = 1;
	//printf("entrou na printnode\n");
	switch(node->type)
	{	
            case AST_ADD:
		astPrintNode(node->scc[0]);		// expr     
		fprintf(ExitTree," + ");
		astPrintNode(node->scc[1]);		// expr            	
            	break;
            case AST_SUB:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," - ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_MUL:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," * ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_DIV:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," / ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_KW_INTEGER:
		fprintf(ExitTree,"integer");
		break;
            case AST_KW_FLOATING:
		fprintf(ExitTree,"floating");
		break;
            case AST_KW_BOOLEAN:
		fprintf(ExitTree,"boolean");
		break;
            case AST_KW_CHARACTER:
		fprintf(ExitTree,"character");
		break;
            case AST_KW_IF:
		fprintf(ExitTree,"if (");
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree,") then \n");
		astPrintNode(node->scc[1]);		// blocks
		break;
            case AST_KW_IF_ELSE:
		fprintf(ExitTree,"if (");
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree,") then \n");
		astPrintNode(node->scc[1]);		// blocks
		fprintf(ExitTree," else\n");
		astPrintNode(node->scc[2]);		// blocks
		break;
            case AST_KW_WHILE:
		fprintf(ExitTree,"while (");
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree,") \n");
		astPrintNode(node->scc[1]);		// blocks
		break;
            case AST_KW_DO_WHILE:
		fprintf(ExitTree,"do\n");
		astPrintNode(node->scc[0]);		// blocks
		fprintf(ExitTree,"\nwhile (");
		astPrintNode(node->scc[1]);		// expr
		fprintf(ExitTree,")\n");
		break;
            case AST_KW_INPUT:
		if(node->symbol)
			if(node->symbol->content.text)
			{
				fprintf(ExitTree,"input %s", node->symbol->content.text);
			}
		break;
            case AST_KW_OUTPUT:
		fprintf(ExitTree,"output ");
		astPrintNode(node->scc[0]);		// outp
		break;
            case AST_KW_RETURN:
		fprintf(ExitTree,"return ");
		astPrintNode(node->scc[0]);		// outp
		break;
            case AST_OPERATOR_LE:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," <= ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_OPERATOR_GE:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," >= ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_OPERATOR_EQ:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," == ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_OPERATOR_NE:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," != ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_OPERATOR_AND:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," && ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_OPERATOR_OR:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," || ");
		astPrintNode(node->scc[1]);		// expr
            	break;											
            case AST_LIT_INTEGER:
		if(node->symbol)
			if(node->symbol->content.intVal)
			{
				fprintf(ExitTree, "%d", node->symbol->content.intVal);
			}
		break;
            case AST_LIT_FLOATING:
		if(node->symbol)
			if(node->symbol->content.floatVal)
			{
				fprintf(ExitTree, "%f", node->symbol->content.floatVal);
			}
		break;
            case AST_LIT_TRUE:
		fprintf(ExitTree," true ");
		break;
            case AST_LIT_FALSE:
		fprintf(ExitTree," false ");
		break;
            case AST_LIT_CHAR:
		if(node->symbol)
			if(node->symbol->content.charVal)
			{
				fprintf(ExitTree, "%c", node->symbol->content.charVal);
			}
		break;
            case AST_LIT_STRING:
	  	fprintf (ExitTree, "\"");
	  	fprintf (ExitTree, "%s", node->symbol->content.text);
	  	fprintf (ExitTree, "\"");
	  	break;
            case AST_TK_IDENTIFIER:
		if(node->symbol)
			if(node->symbol->content.text)
			{
				fprintf(ExitTree, "%s", node->symbol->content.text);
			}
		break;
            case AST_IGUAL:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," = ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_MAIOR:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," > ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_MENOR:
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree," < ");
		astPrintNode(node->scc[1]);		// expr
            	break;
            case AST_NEG:
		fprintf(ExitTree," ! ");
		astPrintNode(node->scc[0]);		// expr
            	break;
            case AST_exprComParent:
		fprintf(ExitTree," (");
		astPrintNode(node->scc[0]);		// expr
		fprintf(ExitTree,") ");
            	break;
	    case AST_programa:
		astPrintNode(node->scc[0]); // vai p/ declaracao_glob
	    	break;
	    case AST_declaracao_glob:
		astPrintNode(node->scc[0]);
		fprintf(ExitTree,";\n");
		astPrintNode(node->scc[1]);
		break;
	    case AST_declaracao:
		fprintf(ExitTree,"declare ");
		if(node->symbol)
			if(node->symbol->content.text)
			{
				fprintf(ExitTree, "%s :", node->symbol->content.text);
				astPrintNode(node->scc[0]);	//espec_tipo
				if(node->scc[1]!=0)
					astPrintNode(node->scc[1]);	// vet
			}
		break;
	    case AST_funcao:
		if(node->symbol)
			if(node->symbol->content.text)
			{
				fprintf(ExitTree, "%s", node->symbol->content.text);
				fprintf(ExitTree,": ");
				astPrintNode(node->scc[0]);	//espec_tipo
				fprintf(ExitTree," (");
				astPrintNode(node->scc[1]);	// parametros
				fprintf(ExitTree,") ");
				astPrintNode(node->scc[2]);	// blocks
			}
		break;
	    case AST_parametros:
		astPrintNode(node->scc[0]);
		fprintf(ExitTree, ", ");
		astPrintNode(node->scc[1]);
		break;
	    case AST_vaiParaParametros:
		astPrintNode(node->scc[0]);
		break;
	    case AST_parametro:
		if(node->symbol)
			if(node->symbol->content.text)
			{
				fprintf(ExitTree, "%s", node->symbol->content.text);
			}
		fprintf(ExitTree,": ");
		astPrintNode(node->scc[0]);
		break;
	    case AST_blocks:
		astPrintNode(node->scc[0]);	//bloco ou cmd
		break;
	    case AST_bloco:
		fprintf(ExitTree,"{\n");
		astPrintNode(node->scc[0]);	//bloco
		fprintf(ExitTree,"\n}");
		break;
	    case AST_cmd:
		astPrintNode(node->scc[0]);	//declaracao ou expr ou cmd
		break;
	    case AST_outp:
		astPrintNode(node->scc[0]);	//expr
		break;
	    case AST_outp2:
		astPrintNode(node->scc[0]);	//expr ',' outp
		fprintf(ExitTree, ",");
		astPrintNode(node->scc[1]);	
		break;
	    case AST_primary_expression:
		astPrintNode(node->scc[0]);	//primary_expression ou CONSTANT
		break;
	    case AST_exprComTK_IDENTIFIER:
		if(node->symbol)
			if(node->symbol->content.text)
			{
				fprintf(ExitTree, "%s", node->symbol->content.text);
			}
		fprintf(ExitTree,"( ");
		astPrintNode(node->scc[0]);	//bloco ou cmd
		fprintf(ExitTree," )");
		break;
	    case AST_TK_IDENTIFIER_VET:
		if(node->symbol)
			if(node->symbol->content.text)
			{
				fprintf(ExitTree, "%s", node->symbol->content.text);
			}
		astPrintNode(node->scc[0]);	//vetor
		break;
	    case AST_vet:
		fprintf(ExitTree,"[");
		if(node->symbol)
			if(node->symbol->content.intVal)
			{
				fprintf(ExitTree, "%d", node->symbol->content.intVal);
			}
		fprintf(ExitTree,"]");
		break;
	    case AST_params_func:
		astPrintNode(node->scc[0]);	//primary_expression
		fprintf(ExitTree,", ");
		astPrintNode(node->scc[1]);	//params_func
		break;
	    case AST_contr_fluxo:
		astPrintNode(node->scc[0]);	//contr_fluxo
		break;
	    case AST_cmds:
		astPrintNode(node->scc[0]);	//cmd
		fprintf(ExitTree,";\n");
		astPrintNode(node->scc[1]);	//cmds
		break;
	    default: 
		printf("UNKNOWN\n");
	    	break;
	}
}

int dataTypeMap(int astType)
{
	switch (astType)
	{
		case AST_KW_INTEGER: return DATATYPE_KW_INTEGER;
		case AST_KW_FLOATING: return DATATYPE_KW_FLOATING;
		case AST_KW_CHARACTER: return DATATYPE_KW_CHARACTER;
		case AST_KW_BOOLEAN: return DATATYPE_KW_BOOLEAN;
	}
}
