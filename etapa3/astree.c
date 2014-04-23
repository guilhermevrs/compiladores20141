/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"

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
  return node;
}

void astPrintSingle(ASTREE *node)
{
    if(node == 0)
        return;
    printf("ASTREE(");
    switch(node->type)
    {
        default: printf("DEFAULT, "); break;
    }
    if(node->symbol != 0)
    {
        printf("Text: %s, ", node->symbol->text);
        printf("Type: %d", node->symbol->type);
    }
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

void callSonsDecompile(ASTREE *root, FILE * out)
{
    int i;
    if(root == 0)
    {
        return;
    }
    for (i=0; i<MAX_SONS; ++i)
    {
        astCompile(root->son[i], out);
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
            if(root->son[2] != 0){ //caso tenha mais parametros
                fprintf(out, ", ");
                astCompile(root->son[2], out);
            }
            break;

        case ASTREE_DEF_PARAM_POINTER:
            astCompile(root->son[0], out);
            fprintf(out, "$ ");
            astCompile(root->son[1], out);
            if(root->son[2] != 0){ //caso tenha mais parametros
                fprintf(out, ", ");
                astCompile(root->son[1], out);
            }
            break;

        case ASTREE_DEF_COMMAND_BLOCK:
            callSonsDecompile(root, out);
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
                // In case it has more than one parameter
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
            if(root->son[1] != 0){
                // In case it has more than one parameter
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
            callSonsDecompile(root, out);
            if(root->son[0] == 0)
            {// Leaf: returns its value
                if (root -> symbol != 0)
                {
                    fprintf(out, "%s", root->symbol->text);
                    return;
                }
            }
            break;
    };
}

// END OF FILE
