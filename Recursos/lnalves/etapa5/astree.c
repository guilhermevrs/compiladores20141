#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "astree.h"

	
ASTREE *astreeCreate( int type, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3, HASH_CELL *n )
{

	
	ASTREE *node = 0;
	
	node = (ASTREE*) calloc (1,sizeof(ASTREE));
	node->lineNumber = getLineNumber();
	node->type = type;
	node->son[0] = s0;
	node->son[1] = s1;
	node->son[2] = s2;
	node->son[3] = s3;
	
	node->symbol = n;
	node->impresso = 0;
	return node;


}


void astreePrintSingle (ASTREE *node)
{
	if (!node)
		return;
	if(node->impresso==1)
		return;
	node->impresso = 1;
	
	fprintf(stderr, "ASTREE(");
	switch (node->type)
	{	
		case ASTREE_SYMBOL: fprintf(stderr, "ASTREE_SYMBOL"); 
							if(node->symbol)
								fprintf(outputfile, " %s ", node->symbol->lexem);
							break;
		//case ASTREE_LIT_INT: fprintf(stderr, "ASTREE_LIT_INT"); break;
		case ASTREE_SOMA: fprintf(stderr, "ASTREE_SOMA");
						  astreePrintSingle (node->son[0]);
						  fprintf(outputfile, " + ");
						  astreePrintSingle (node->son[1]);
						  break;
		case ASTREE_SUB: fprintf(stderr, "ASTREE_SUB");
						 astreePrintSingle (node->son[0]);
						 fprintf(outputfile, " - ");
						 astreePrintSingle (node->son[1]);
						 break;
		case ASTREE_DIV: fprintf(stderr, "ASTREE_DIV");
						 astreePrintSingle (node->son[0]);
						 fprintf(outputfile, " / ");
						 astreePrintSingle (node->son[1]);
						 break;
		case ASTREE_MULT: fprintf(stderr, "ASTREE_MULT");
						  astreePrintSingle (node->son[0]);
						  fprintf(outputfile, " * ");
						  astreePrintSingle (node->son[1]);
						  break;
						  
		case ASTREE_CMDL: fprintf(stderr, "ASTREE_CMDL"); 
						  astreePrintSingle (node->son[0]);
						  fprintf(outputfile, ";\n");
						  astreePrintSingle (node->son[1]);
						  break;
		case ASTREE_SCALAR_ASS: fprintf(stderr, "ASTREE_SCALAR_ASS");
							    if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
							    fprintf(outputfile, "=");
						  		astreePrintSingle (node->son[0]);								
								
						        break;

		case ASTREE_VETOR_ASS: fprintf(stderr, "ASTREE_VETOR_ASS"); 
							   if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
							    fprintf(outputfile, " [");
						  		astreePrintSingle (node->son[0]);
						  		fprintf(outputfile, "] ");
						  		fprintf(outputfile, "=");
						  		astreePrintSingle (node->son[1]);
							   break;

		case ASTREE_GLIST: fprintf(stderr, "ASTREE_GLIST");
						    astreePrintSingle (node->son[0]);
						  	fprintf(outputfile, "\n ");
						  	astreePrintSingle (node->son[1]);
						   
						   break;
		case ASTREE_VARDEC: fprintf(stderr, "ASTREE_VARDEC");

							astreePrintSingle (node->son[0]);
							if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
							fprintf(outputfile, ":");
						  	astreePrintSingle (node->son[1]);
						  	fprintf(outputfile, ";\n");
						  	
							
							//astreePrintSingle (node->son[0]);
						  	//fprintf(outputfile, "* ");
						  	//astreePrintSingle (node->son[1]);
							
							break;
		
		case ASTREE_DECLOC: fprintf(stderr, "ASTREE_DECLOC");

							astreePrintSingle (node->son[0]);
							//fprintf(outputfile, ";\n");
						  	astreePrintSingle (node->son[1]);
							 break;
		
		case ASTREE_VETDEC: fprintf(stderr, "ASTREE_VETDEC");
							//vetordec: tipo TK_IDENTIFIER '[' literalvet ']' { $$ = astreeCreate(ASTREE_VETDEC,$1,$4,0,0,$2); }
							astreePrintSingle (node->son[0]);
							if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
							fprintf(outputfile, "[");
						  	astreePrintSingle (node->son[1]);
						  	fprintf(outputfile, "]");
						  	fprintf(outputfile, ";\n");
							 break;
		case ASTREE_VETDEC2: fprintf(stderr, "ASTREE_VETDEC2");
							//		| tipo TK_IDENTIFIER '[' literalvet ']' ':' initvetor { $$ = astreeCreate(ASTREE_VETDEC2,$1,$4,$7,0,$2); }
							astreePrintSingle (node->son[0]);
							if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
							fprintf(outputfile, "[");
						  	astreePrintSingle (node->son[1]);
						  	fprintf(outputfile, "] : ");
						  	astreePrintSingle (node->son[2]);
						  	fprintf(outputfile, ";\n");
							 break;
		case ASTREE_VETDEC3: fprintf(stderr, "ASTREE_VETDEC3");
							//		| tipo '$' TK_IDENTIFIER { $$ = astreeCreate(ASTREE_VETDEC3,$1,0,0,0,$3); }
							astreePrintSingle (node->son[0]);
							fprintf(outputfile, "$");
							if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
							fprintf(outputfile, ";\n");
							 break;
		case ASTREE_VETDEC4: fprintf(stderr, "ASTREE_VETDEC4");
							//		| tipo '$' TK_IDENTIFIER ':' literais { $$ = astreeCreate(ASTREE_VETDEC4,$1,$5,0,0,$3); }
							astreePrintSingle (node->son[0]);
							fprintf(outputfile, "$");
							if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
							fprintf(outputfile, " : ");
						  	astreePrintSingle (node->son[1]);
						  	fprintf(outputfile, ";\n");
							 break;
		case ASTREE_PARAM: fprintf(stderr, "ASTREE_PARAM");
							astreePrintSingle (node->son[0]);
							if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
						  	astreePrintSingle (node->son[1]);
							 break;
		
		case ASTREE_PARAM2: fprintf(stderr, "ASTREE_PARAM2");
							astreePrintSingle (node->son[0]);
							if(node->symbol)
									fprintf(outputfile, "%s, ", node->symbol->lexem);
						  	astreePrintSingle (node->son[1]);
							 break;
		
		case ASTREE_WORD: fprintf(stderr, "ASTREE_WORD");
						  fprintf(outputfile, "word ");
						  break;
		case ASTREE_BYTE: fprintf(stderr, "ASTREE_BYTE");
						  fprintf(outputfile, "byte ");
						  break;
		case ASTREE_BOOL: fprintf(stderr, "ASTREE_BOOL");
						  fprintf(outputfile, "bool ");
						  break;
		case ASTREE_FUNDEC: fprintf(stderr, "ASTREE_FUNDEC"); 
							astreePrintSingle (node->son[0]);
							if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
							fprintf(outputfile, "( ");	
						  	astreePrintSingle (node->son[1]);
							fprintf(outputfile, ") ");

							astreePrintSingle (node->son[2]);
							astreePrintSingle (node->son[3]);
							

							break;
		case ASTREE_KW_INPUT: fprintf(stderr, "ASTREE_KW_INPUT");
							fprintf(outputfile, "input ");
							if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem); 
							break;
		case ASTREE_KW_OUTPUT: fprintf(stderr, "ASTREE_KW_OUTPUT"); 
							fprintf(outputfile, "output ");
							astreePrintSingle (node->son[0]);						
							break;
		case ASTREE_KW_RETURN: fprintf(stderr, "ASTREE_KW_RETURN"); 
							fprintf(outputfile, "return ");
							astreePrintSingle (node->son[0]);				
							break;
		
		case ASTREE_IF: fprintf(stderr, "ASTREE_IF");
					    fprintf(outputfile, "if( ");
					    astreePrintSingle (node->son[0]);
						fprintf(outputfile, ") then ");
						astreePrintSingle (node->son[1]); break;
		case ASTREE_IFELSE: fprintf(stderr, "ASTREE_IFELSE");
					    fprintf(outputfile, "if( ");
					    astreePrintSingle (node->son[0]);
						fprintf(outputfile, ") then ");
						astreePrintSingle (node->son[1]);
						fprintf(outputfile, " else ");
						astreePrintSingle (node->son[2]);
						 break;
						 
		case ASTREE_LOOP: fprintf(stderr, "ASTREE_LOOP");
						  fprintf(outputfile, "loop ( ");
						  astreePrintSingle (node->son[0]);
						  fprintf(outputfile, ") ");
						  astreePrintSingle (node->son[1]); break;
		
		case ASTREE_LE: fprintf(stderr, "ASTREE_LE");
					    astreePrintSingle (node->son[0]);
						  fprintf(outputfile, "<= ");
						  astreePrintSingle (node->son[1]);
					    break;
		case ASTREE_GE: fprintf(stderr, "ASTREE_GE");
					    astreePrintSingle (node->son[0]);
						  fprintf(outputfile, ">= ");
						  astreePrintSingle (node->son[1]);
						break;
		case ASTREE_EQ: fprintf(stderr, "ASTREE_EQ");
					    astreePrintSingle (node->son[0]);
						  fprintf(outputfile, "== ");
						  astreePrintSingle (node->son[1]); break;
		case ASTREE_NE: fprintf(stderr, "ASTREE_NE");
					    astreePrintSingle (node->son[0]);
						  fprintf(outputfile, "!= ");
						  astreePrintSingle (node->son[1]); break;
		case ASTREE_AND: fprintf(stderr, "ASTREE_AND");
					    astreePrintSingle (node->son[0]);
						  fprintf(outputfile, "&& ");
						  astreePrintSingle (node->son[1]); break;
		case ASTREE_OR: fprintf(stderr, "ASTREE_OR");
					    astreePrintSingle (node->son[0]);
						  fprintf(outputfile, "|| ");
						  astreePrintSingle (node->son[1]); break;
		case ASTREE_LESS: fprintf(stderr, "ASTREE_LESS");
					    astreePrintSingle (node->son[0]);
						  fprintf(outputfile, "< ");
						  astreePrintSingle (node->son[1]); break;
		case ASTREE_GREAT: fprintf(stderr, "ASTREE_GREAT");
					    astreePrintSingle (node->son[0]);
						  fprintf(outputfile, "> ");
						  astreePrintSingle (node->son[1]); break;
		
		case ASTREE_VETOR: fprintf(stderr, "ASTREE_VETOR"); 
									if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
									astreePrintSingle (node->son[0]);
									break;
		case ASTREE_DEREFVET: fprintf(stderr, "ASTREE_DEREFVET"); 
								fprintf(outputfile, "&");
								if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);
								break;
		case ASTREE_REFVET: fprintf(stderr, "ASTREE_REFVET"); 
								fprintf(outputfile, "*");
								if(node->symbol)
									fprintf(outputfile, "%s", node->symbol->lexem);	
								break;
		case ASTREE_FUNC: fprintf(stderr, "ASTREE_FUNC"); 
								if(node->symbol)
									fprintf(outputfile, "%s (", node->symbol->lexem);
								astreePrintSingle (node->son[0]);
								fprintf(outputfile, ")");
								break;
		case ASTREE_EXPRESSION: fprintf(stderr, "ASTREE_EXPRESSION"); 
							astreePrintSingle (node->son[0]);
							break;
		
		case ASTREE_OUTPUT: fprintf(stderr, "ASTREE_OUTPUT");
					      astreePrintSingle (node->son[0]);
						   break;
		case ASTREE_OUTPUT2: fprintf(stderr, "ASTREE_OUTPUT2");
					    astreePrintSingle (node->son[0]);
						  fprintf(outputfile, ", ");
						  astreePrintSingle (node->son[1]); break;
		case ASTREE_BLOCO: 	fprintf(stderr, "ASTREE_BLOCO");
					      fprintf(outputfile, "{\n");
					      astreePrintSingle (node->son[0]);
						  fprintf(outputfile, "}\n");
						  break;	
		
		case ASTREE_CTRLBLOCO: 	fprintf(stderr, "ASTREE_CTRLBLOCO");
//					      fprintf(outputfile, "{ ");
					      astreePrintSingle (node->son[0]);
		//				  fprintf(outputfile, "} ");
						  break;
		
		case ASTREE_INITVET: fprintf(stderr, "ASTREE_INITVET"); 
						astreePrintSingle (node->son[0]);	
						break;
		case ASTREE_INITVET2: fprintf(stderr, "ASTREE_INITVET2"); 
						astreePrintSingle (node->son[0]);
						astreePrintSingle (node->son[1]);
						break;
						
		case ASTREE_PARAMFUNC: fprintf(stderr, "ASTREE_PARAMFUNC");
					      astreePrintSingle (node->son[0]);
						   break;
		case ASTREE_PARAMFUNC2: fprintf(stderr, "ASTREE_PARAMFUNC2");
					    astreePrintSingle (node->son[0]);
						  fprintf(outputfile, ", ");
						  astreePrintSingle (node->son[1]); break;

		//case ASTREE_VARDEC2: fprintf(stderr, "ASTREE_VARDEC2"); break;
		//case ASTREE_VETORDEC2: fprintf(stderr, "ASTREE_VETORDEC2"); break;
		//case ASTREE_FUNDEC2: fprintf(stderr, "ASTREE_FUNDEC2"); break;
		
		
		
		default: fprintf(stderr, "ASTREE UNKNOWN %d", node->type); break;
	}
	
	if(node->symbol)
	{
		if(node->symbol->lexem)
			fprintf(stderr, ") %s", node->symbol->lexem);
		else
			fprintf(stderr, ")\n");
	}
	else
		fprintf(stderr, ")\n");
		
	//fprintf(stderr, ")\n");

}
void astreePrintTree (ASTREE *node, int level)
{
	int i;
	astreePrintSingle(node);
	
	if(!node)
		return;
	for(i=0; i<level; i++)
		fprintf(stderr, "\t");
		
	for (i=0; i<MAX_SONS; ++i)
		if (node->son[1])
			astreePrintTree(node->son[i], level+1 );

}

