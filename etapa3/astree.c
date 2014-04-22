/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
FILE *ExitTree;


ASTREE *astCreate(int type, HASH_NODE *symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3)
{
  ASTREE *node;
  node = (ASTREE*)calloc(1,sizeof(ASTREE));
  node->type = type;
  node->symbol = symbol;
  node->son[0] = s0;
  node->son[1] = s1;
  node->son[2] = s2;
  node->son[3] = s3;
  node->impresso = 0;
  return node;
}

void asPrintTree(ASTREE *root, int level)
{
  int i;
  if (root==0)
    return;
  for (i=0; i<level; ++i)
    printf("  ");
  asPrintSingle(root);
  for (i=0; i<MAX_SONS;++i)
    asPrintTree(root->son[i], 0);
}

void asPrintSingle(ASTREE *node)
{
//  if (node==0)
//    return;
//  printf("ASTREE(");
//  switch (node->type)
//  {
//    case AST_SYMBOL: printf("SYMBOL, "); break;
//    case AST_ADD: printf("ADD, "); break;
//    default: printf("UNKNOWN"); break;
//  };

  if (node->symbol !=0)
    printf("%s", node->symbol);
  printf(")");
  if(node==NULL) return;
    if(node->impresso==1)return;
    node->impresso = 1;
    switch(node->type)
    {
      /*case AST_ADD:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," + ");
	astPrintNode(node->son[1]);
        break;
      case AST_SUB:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," - ");
	astPrintNode(node->son[1]);
        break;
      case AST_MUL:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," * ");
	astPrintNode(node->son[1]);
        break;
      case AST_DIV:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," / ");
	astPrintNode(node->son[1]);
        break;
      case AST_KW_WORD:
	fprintf(ExitTree,"word");
	break;
      case AST_KW_BOOL:
	fprintf(ExitTree,"bool");
	break;
      case AST_KW_BYTE:
	fprintf(ExitTree,"byte");
	break;
      case AST_KW_IF:
	fprintf(ExitTree,"if (");
	astPrintNode(node->son[0]);
	fprintf(ExitTree,")\nthen ");
	astPrintNode(node->son[1]);
	break;
      case AST_KW_IF_ELSE:
	fprintf(ExitTree,"if (");
	astPrintNode(node->son[0]);
	fprintf(ExitTree,")\nthen ");
	astPrintNode(node->son[1]);
	fprintf(ExitTree,"\nelse ");
	astPrintNode(node->son[2]);
	break;
      case AST_KW_LOOP:
	fprintf(ExitTree,"loop (");
	astPrintNode(node->son[0]);
	fprintf(ExitTree,") \n");
	astPrintNode(node->son[1]);
	break;
      case AST_KW_INPUT:
	if(node->symbol)
	  if(node->symbol->text)
	  {
	    fprintf(ExitTree,"input %s", node->symbol->text);
	  }
	  break;
      case AST_KW_OUTPUT:
	fprintf(ExitTree,"output ");
	astPrintNode(node->son[0]);
	break;
      case AST_KW_RETURN:
	fprintf(ExitTree,"return ");
	astPrintNode(node->son[0]);
	break;
      case AST_OPERATOR_LE:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," <= ");
	astPrintNode(node->son[1]);
        break;
      case AST_OPERATOR_GE:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," >= ");
	astPrintNode(node->son[1]);
        break;
      case AST_OPERATOR_EQ:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," == ");
	astPrintNode(node->son[1]);
        break;
      case AST_OPERATOR_NE:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," != ");
	astPrintNode(node->son[1]);
        break;
      case AST_OPERATOR_AND:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," && ");
	astPrintNode(node->son[1]);
        break;
      case AST_OPERATOR_OR:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," || ");
	astPrintNode(node->son[1]);
        break;
      case AST_LIT_INTEGER:
	if(node->symbol)
	  if(node->symbol->intVal >= 0 || node->symbol->intVal < 0)
	  {
	    fprintf(ExitTree, "%d ", node->symbol->intVal);
	  }
	break;
      case AST_LIT_TRUE:
	fprintf(ExitTree," TRUE ");
	break;
      case AST_LIT_FALSE:
	fprintf(ExitTree," FALSE ");
	break;
      case AST_LIT_CHAR:
	if(node->symbol)
	  if(node->symbol->charVal)
	  {
	    fprintf(ExitTree, "'%c'", node->symbol->charVal);
	  }
	  break;
      case AST_LIT_STRING:
	fprintf (ExitTree, "\"");
	fprintf (ExitTree, "%s", node->symbol->text);
	fprintf (ExitTree, "\"");
	break;
      case AST_TK_IDENTIFIER:
	if(node->symbol)
	  if(node->symbol->text)
	    {
	      fprintf(ExitTree, "%s", node->symbol->text);
	    }
	    break;
      case AST_IGUAL:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," = ");
	astPrintNode(node->son[1]);
        break;
      case AST_MAIOR:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," > ");
	astPrintNode(node->son[1]);
        break;
      case AST_MENOR:
	astPrintNode(node->son[0]);
	fprintf(ExitTree," < ");
	astPrintNode(node->son[1]);
        break;
      case AST_NEG:
	fprintf(ExitTree," ! ");
	astPrintNode(node->son[0]);
        break;
      case AST_exprComParent:
	fprintf(ExitTree," (");
	astPrintNode(node->son[0]);
	fprintf(ExitTree,") ");
        break;



      case AST_bloco:
	fprintf(ExitTree,"{\n");
	astPrintNode(node->son[0]);
	fprintf(ExitTree,"\n}");
	break;
      case AST_outp:
	astPrintNode(node->son[0]);
	break;
      case AST_outp2:
	astPrintNode(node->son[0]);
	fprintf(ExitTree, ",");
	astPrintNode(node->son[1]);
	break;




      case AST_ATRIB_CONST:
        if(node->symbol)
	  if(node->symbol->text)
	  {
	    fprintf(ExitTree, " %s ", node->symbol->text);
	    fprintf(ExitTree, " = ");
	    astPrintNode(node->son[0]);
	  }
	break;
      case AST_ATRIB_VET:
	if(node->symbol)
	  if(node->symbol->text)
	  {
	    fprintf(ExitTree, " %s ", node->symbol->text);
	    fprintf(ExitTree, " [ ");
	    astPrintNode(node->son[0]);
	    fprintf(ExitTree, " ] = ");
	    astPrintNode(node->son[1]);
	  }
	break;
      case AST_exprComChavesTK_IDENTIFIER:
	if(node->symbol)
	  if(node->symbol->text)
	  {
	    fprintf(ExitTree, "%s", node->symbol->text);
	  }
	  fprintf(ExitTree," [");
	  astPrintNode(node->son[0]);
	  fprintf(ExitTree,"] ");
        break;
      case AST_exprComChavesTK_IDENTIFIER:
	if(node->symbol)
	  if(node->symbol->text)
	  {
	    fprintf(ExitTree, "%s", node->symbol->text);
	  }
	  fprintf(ExitTree," [");
	  astPrintNode(node->scc[0]);
	  fprintf(ExitTree,"] ");
        break;



      case AST_decl_var:
        if(node->symbol)
	  if(node->symbol->text)
	  {
	    astPrintNode(node->son[0]);
	    fprintf(ExitTree, " %s :", node->symbol->text);
	    astPrintNode(node->son[1]);
	    fprintf(ExitTree, ";\n");
	  }
	break;
      case AST_decl_vetch:
	if(node->symbol)
	  if(node->symbol->text)
	  {
	    astPrintNode(node->son[0]);
	    fprintf(ExitTree, " %s ", node->symbol->text);
	    fprintf(ExitTree, "[ ");
	    astPrintNode(node->son[1]);
	    fprintf(ExitTree, "] : ");
	    astPrintNode(node->son[2]);
	    fprintf(ExitTree, ";\n");
	  }
	break;
      case AST_decl_vet:
	if(node->symbol)
	  if(node->symbol->text)
	  {
	    astPrintNode(node->son[0]);
	    fprintf(ExitTree, " %s ", node->symbol->text);
	    fprintf(ExitTree, "[ ");
	    astPrintNode(node->son[1]);
	    fprintf(ExitTree, "] ");
	    fprintf(ExitTree, ";\n");
	  }
	break;
      case AST_decl_pointer:
	if(node->symbol)
	  if(node->symbol->text)
	  {
	    astPrintNode(node->son[0]);
	    fprintf(ExitTree, " $");
	    fprintf(ExitTree, "%s", node->symbol->text);
	    fprintf(ExitTree, " : ");
	    astPrintNode(node->son[1]);
	    fprintf(ExitTree, ";\n");
	  }
	break;

      */
      default:
	printf("UNKNOWN\n");
	break;
      }

}



// END OF FILE
