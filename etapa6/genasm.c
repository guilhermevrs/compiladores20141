
#include "genasm.h"
#include "astree.h"
#include "y.tab.h"
FILE *outasm;

int aux_beg_func = 0;
int aux_end_func = 0;
int aux_output = 0;
int nextArg = 0;
int haveArgs = 0;
int vet_aux = 0;

void gen_code (TAC *t, FILE *outasm)
{
	if (!t)
		return;
// FALTA O LOOP 
// FALTA DVISAO
	int aux;

	switch (t->type)
	{

		case TAC_BEGINFUN: 
			if (!strcmp(t->target->text,"main"))
					fprintf(outasm,	"\n\t.section	.rodata\n");
			fprintf(outasm, 
			"\t.globl	%s\n"
			"%s:\n"
			".LFB%d:\n"
			"\tpushq	%%rbp\n"
			"\tmovq	%%rsp, %%rbp\n",
			t->target->text, t->target->text, aux_beg_func);
			aux_beg_func++;

			if(haveArgs)
			{
				if(nextArg == 1)
					fprintf(outasm,
					"\tmovl	%%edi, %%edx\n");
				else if (nextArg ==2)
					fprintf(outasm,
					"\tmovl	%%esi, %%eax\n");
			}
			break;

		case TAC_ENDFUN: 
			fprintf(outasm, 
					"\tleave\n"
					"\tret\n"
					".LFE%d:\n"
					"\t.size	%s,	.-%s\n",
					aux_end_func,t->target->text, t->target->text);
					aux_end_func++;
					haveArgs = 0;
			break;	

		case TAC_ARG:
			haveArgs = 1;
			if(nextArg == 0)
			{
				nextArg = 1;
				fprintf(outasm, 
					"\tmovl	%s(%%rip), %%edi\n"
					,t->target->text);
				break;	
			}
			if(nextArg == 1)
			{
				nextArg = 2;
				fprintf(outasm, 
					"\tmovl	%s(%%rip), %%esi\n"
					,t->target->text);
				break;	
			}
			if(nextArg == 2)
			{
				nextArg = 3;
				fprintf(outasm, 
					"\tmovl	%s(%%rip), %%edx\n"
					,t->target->text);
				break;	
			}
			if(nextArg == 3)
			{
				nextArg = 0;
				fprintf(outasm, 
					"\tmovl	%s(%%rip), %%ecx\n"
					,t->target->text);
				break;	
			}		
	
		case TAC_RETURN:
			if (t->target->type == SYMBOL_VARIABLE)
				fprintf(outasm, 
					"\tmovl	%s(%%rip),%%eax\n"
					,t->target->text);
			else if (t->target->type == 2)
				fprintf(outasm, 
					"\tmovl	$%s,%%eax\n"
					,t->target->text);
			break;	

		case TAC_SOMA: 
			fprintf(outasm,	
				"\tmovl %s(%%rip), %%edx\n" 
				"\tmovl %s(%%rip), %%eax\n "
				"\taddl %%edx, %%eax\n"
				"\n", 
				t->op1->text,t->op2->text);
			break;

		case TAC_SUB: 
			fprintf(outasm,	
				"\tmovl %s(%%rip), %%edx\n" 
				"\tmovl %s(%%rip), %%eax\n"
				"\tsubl %%edx, %%eax\n"
				"\n",
				t->op1->text,t->op2->text);
				break;

		case TAC_MULT: 
			fprintf(outasm,	
				"\tmovl %s(%%rip), %%edx\n" 
				"\tmovl %s(%%rip), %%eax\n"
				"\tmull %%edx, %%eax\n"
				"\n",
				t->op1->text,t->op2->text);
				break;

		case TAC_DIV: 
			fprintf(outasm,	
				"\tmovl	%s(%%rip), %%eax\n"
				"\tmovl	%s(%%rip), %%edx\n"
				"\tmovl	%%edx, -4(%%rbp)\n"
				"\tmovl	%%eax, %%edx\n"
				"\tsarl	$31, %%edx\n"
				"\tidivl	-4(%%rbp)\n"
				"\n",
				t->op1->text,t->op2->text);
				break;
	
		case TAC_GREAT: 
			fprintf(outasm,	
				"\tmovl	%s(%%rip), %%edx\n"
				"\tmovl	%s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsetg	%%al\n"
				"\tmovzbl	%%al, %%eax\n"
				"\n",
				t->op1->text,t->op2->text);
				break;

		case TAC_LESS: 
			fprintf(outasm,	
				"\tmovl	%s(%%rip), %%edx\n"
				"\tmovl	%s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsetl	%%al\n"
				"\tmovzbl	%%al, %%eax\n"
				"\n",
				t->op1->text,t->op2->text);
				break;					

		case TAC_GE: 
			fprintf(outasm,	
				"\tmovl	%s(%%rip), %%edx\n"
				"\tmovl	%s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsetge	%%al\n"
				"\tmovzbl	%%al, %%eax\n"
				"\n",
				t->op1->text,t->op2->text);
				break;

		case TAC_NE: 
			fprintf(outasm,	
				"\tmovl	%s(%%rip), %%edx\n"
				"\tmovl	%s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsetne	%%al\n"
				"\tmovzbl	%%al, %%eax\n"
				"\n",
				t->op1->text,t->op2->text);
				break;

		case TAC_EQ: 
			fprintf(outasm,	
				"\tmovl	%s(%%rip), %%edx\n"
				"\tmovl	%s(%%rip), %%eax\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsete	%%al\n"
				"\tmovzbl	%%al, %%eax\n"
				"\n",
				t->op1->text,t->op2->text);
				break;

		case TAC_AND: 
			fprintf(outasm, 
				"\tmovl	%s(%%rip), %%edx\n"
				"\tmovl	%s(%%rip), %%eax\n"
				"\tand	%%eax, %%edx\n"
				"\tsete	%s(%%rip)\n"
				"\n",
				t->op1->text, t->op2->text, t->target->text);
				break; 		

		case TAC_OR: 
			fprintf(outasm, 
				"\tmovl	%s(%%rip), %%edx\n"
				"\tmovl	%s(%%rip), %%eax\n"
				"\tor	%%eax, %%edx\n"
				"\tmovl	$0, %%edx\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tsetnz	%s(%%rip)\n"
				"\n",
				t->op1->text, t->op2->text, t->target->text);
				break; 	

		case TAC_IFZ: 
			fprintf(outasm, 
				"\tmovl	%s(%%rip), %%eax\n"
				"\tmovl	$1, %%edx\n"
				"\tcmpl	%%eax, %%edx\n"
				"\tjnz\t%s\n",
				t->op1->text,t->target->text);
				break;

		case TAC_JUMP: 
			fprintf(outasm, 
				"\tjmp\t%s\n"
				"\n",
				t->target->text);
				break;

		case TAC_LABEL: 
			fprintf(outasm, 
				"%s:\n",
				t->target->text);
				break;

		case TAC_OUTPUT: 
				if (t->target->type == LIT_STRING)
				{
						fprintf(outasm, 
						"\tmovl	$.LC%d, %%edi\n"
						"\tcall	puts\n"
						"\n", aux_output);		
				}
				else
				{
					fprintf(outasm, 
					"\tmovl	%s(%%rip), %%eax\n"
					"\tmovl	%%eax, %%esi\n"
					"\tmovl	$.LC%d, %%edi\n"
					"\tmovl	$0, %%eax\n"
					"\tcall	printf\n"
					"\n",
					t->target->text,aux_output);
				}
				aux_output++;
				break;	

		case TAC_INPUT: 
			fprintf(outasm,
				"\tmovl	$%s, %%esi\n"
				"\tmovl	$.LC%d, %%edi\n"
				"\tmovl	$0, %%eax\n"
				"\tcall	__isoc99_scanf\n"
				"\n",
				t->target->text, aux_output);
				aux_output++;
				break;

		case TAC_MOV: 
			if (t->op1->type == LIT_INTEGER){
				fprintf(outasm,
					"\tmovl\t$%s, %s(%%rip)\n"
					"\n", 
					t->op1->text, t->target->text);
			}
			else
			{ 
				fprintf(outasm,
					"\tmovl\t%s(%%rip), %%eax\n"
					"\tmovl	%%eax, %s(%%rip)\n"
					"\n",
					t->op1->text, t->target->text);
			}
			break;

		case TAC_VET_WRITE: 

		case TAC_CALL:
			/*fprintf(outasm, 
					"\tcall\t%s\n"
					"\tmovl	%%eax, (%%rip)\n",
					t->op1->text);
			break;*/

		default: break;
	}

}

void gen_outputs(FILE *outasm, TAC *first)
{
	if (!first)
		return;

	TAC *tac = 0;
	int i=0;
	for (tac = first; tac; tac=tac->next) {
		if (tac->type == TAC_OUTPUT){
			if (tac->target->type == LIT_STRING)
			{
				fprintf(outasm, 
					"\n.LC%d:\n"
					"\t.string	%s\n", 
					i, tac->target->text);		
			}
			else
			{
				fprintf(outasm, 
					"\n.LC%d:\n"
					"\t.string	\"%%d\"\n", 
					i, tac->target->text);		 
			}
			i++;
		}
		else
			if (tac->type == TAC_INPUT)
			{

				fprintf(outasm, 
					"\n.LC%d:\n"
					"\t.string	\"%%d\"\n", 
					i, tac->target->text);	
				i++;
					
			}
	}
}

void gen_decs(FILE *outasm, TAC *first){
	if (!first)
		return;

	TAC *tac = 0;
	for (tac = first; tac; tac=tac->next) 
	{ 
		if(tac->op1)
			if( !strcmp(tac->op1->text,"TRUE") || !strcmp(tac->op1->text,"true") )
				strcpy(tac->op1->text, "1");
			else if( !strcmp(tac->op1->text,"FALSE") || !strcmp(tac->op1->text,"false") )
				strcpy(tac->op1->text, "0");

		if (tac->type == TAC_VARDEC)
		{ 
			fprintf(outasm,
					"\n%s: \n"
					"\t.long	%s\n", 
					tac->target? tac->target->text:0 , tac->op1? tac->op1->text:0);
		}
		else if (tac->type == TAC_PARAM)
			fprintf(outasm, 
				"\n%s: \n"	
				"\t.long	0\n",
				tac->target->text);

		else if (tac->type == TAC_VETDEC)
		{
			fprintf(outasm,"\n%s: \n",tac->target->text);
				for(vet_aux = 0; vet_aux < atoi(tac->op1->text) ; vet_aux++)	
					fprintf(outasm,"\t.long	0\n");
								
		}
		else if (tac->type == TAC_VETDECINIT)
		{
			fprintf(outasm,"\n%s: \n",tac->target->text);
		}
		else if (tac->type == TAC_VET_READ)
		{
			fprintf(outasm,"\t.long %s\n",tac->target->text);
		}
	}
}


void gen_asm(TAC *first){
	TAC *tac = 0;
	outasm = fopen ("output.s", "w");

	fprintf(outasm,	"\n\t.data\n");

	gen_decs(outasm, first);

	gen_outputs(outasm, first);

	gen_declarations(outasm,&hashtable);

	for (tac = first; tac; tac=tac->next) 
		gen_code(tac,outasm);

}
