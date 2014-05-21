/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"

int pointer = 0, ilegalExp = 0;

ASTREE *astCreate(int type, HASH_NODE *symbol, ASTREE *s0, ASTREE *s1, ASTREE *s2, ASTREE *s3)
{

  ASTREE *node;
  node = (ASTREE*)calloc(1,sizeof(ASTREE));
  node->type = type;
  node->lineNumber = getLineNumber();

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
    switch (node->type)
    {
        case ASTREE_DEF_SYMBOL:    printf("SYMBOL, "); break; //Leaf
        case ASTREE_DEF_ADD:       printf("ADD, ");    break; //ok
        case ASTREE_DEF_SUB:       printf("SUB, ");    break; //ok
        case ASTREE_DEF_MUL:       printf("MUL, ");    break; //ok
        case ASTREE_DEF_LESS:      printf("LESS, ");   break; //ok
        case ASTREE_DEF_GREATER:   printf("GREATER, ");    break; //ok
        case ASTREE_DEF_OP_LE:     printf("OP_LE, ");  break; //ok
        case ASTREE_DEF_OP_GE:     printf("OP_GE, ");  break; //ok
        case ASTREE_DEF_OP_EQ:     printf("OP_EQ, ");  break; //ok
        case ASTREE_DEF_OP_NE:     printf("OP_NE, ");  break; //ok
        case ASTREE_DEF_OP_AND:    printf("OP_AND, "); break; //ok
        case ASTREE_DEF_OP_OR:     printf("OP_OR, ");  break; //ok
        case ASTREE_DEF_INPUT:     printf("INPUT, ");  break; //ok
        case ASTREE_DEF_OUTPUT:    printf("OUTPUT, "); break; //ok
        case ASTREE_DEF_RETURN:    printf("RETURN, "); break; //ok
        case ASTREE_DEF_IF:        printf("IF,");      break; //ok
        case ASTREE_DEF_IFELSE:    printf("IFELSE, "); break; //ok
        case ASTREE_DEF_LOOP:      printf("LOOP, ");   break; //ok
        case ASTREE_DEF_FUNC_CALL:     printf("FUNC_CALL, ");  break; //ok
        case ASTREE_DEF_REF:       printf("REF, ");    break; //ok
        case ASTREE_DEF_DEREF:     printf("DEREF, ");  break; //ok
        case ASTREE_DEF_DECL:      printf("DECL, ");   break; //ok
        case ASTREE_DEF_DECL_VEC:  printf("DECL_VEC, ");   break; //ok
        case ASTREE_DEF_DECL_VEC_INIT: printf("VEC_INI, ");    break; //ok
        case ASTREE_DEF_INIT_VEC:  printf("INIT_VEC, ");   break; //ok
        case ASTREE_DEF_DECL_POINTER:  printf("DECL_POINT, "); break; //ok
        case ASTREE_DEF_VEC_ACCESS:    printf("VEC_ACCESS, "); break; //ok
        case ASTREE_DEF_FUNC:      printf("FUNC, ");   break; //ok
        case ASTREE_DEF_PARAM:     printf("PARAM, ");  break; //ok
        case ASTREE_DEF_PARAM_POINTER: printf("PARAM_POINT, ");break; //ok
        case ASTREE_DEF_PARAM_REF:     printf("PARAM_REF, ");  break; //ok
        case ASTREE_DEF_COMMAND_BLOCK: printf("COMM_BLOCK, "); break; //ok
        case ASTREE_DEF_OUT_LST:   printf("OUT_LST, ");    break; //ok
        case ASTREE_DEF_ATTR:      printf("ATTR, ");   break; //ok
        case ASTREE_DEF_ATTR_VEC:  printf("ATTR_VEC, ");   break; //ok
        case ASTREE_DEF_PROGRAM:   printf("PROGRAM, ");    break; //default
        case ASTREE_DEF_SIMPLE_COMMAND:printf("S_COMMAND, ");  break; //ok
        case ASTREE_DEF_BLOCK:     printf("BLOCK, ");  break; //ok
        default:        printf("DEFAULT, ");    break;

    };
    if(node->symbol != 0)
    {
        printf("Text: %s, ", node->symbol->text);
        printf("Type: %d)", node->symbol->type);
    }
}

void astPrintTree(ASTREE *root, int level)
{
    int i;

    if (root == 0)
    {
        return;
    }
    printf("\n");
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

void internalCompile(ASTREE *root, FILE * out)
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
            internalCompile(root, out);
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

int dataTypeMap(int astType)
{
    switch (astType)
    {
        case ASTREE_DEF_KWWORD: return DATATYPE_WORD;
        case ASTREE_DEF_KWBOOL: return DATATYPE_BOOL;
        case ASTREE_DEF_KWBYTE: return DATATYPE_BYTE;
    }
}

// SEMANTIC ACTIONS/CHECKS

void astTreeCheck(ASTREE *node)
{
    if(node == 0)
        return;


    switch(node->type)
    {
        case ASTREE_DEF_DECL:
        node->symbol->dataType = DATATYPE_VARIABLE;
        break;
        case ASTREE_DEF_DECL_VEC:
        node->symbol->dataType = DATATYPE_VECTOR;
        break;
        case ASTREE_DEF_DECL_VEC_INIT:
        node->symbol->dataType = DATATYPE_VECTOR;
        break;
        case ASTREE_DEF_DECL_POINTER:
        node->symbol->dataType = DATATYPE_POINTER;
        break;
        case ASTREE_DEF_FUNC:
        node->symbol->dataType = DATATYPE_FUNCTION;
        break;
        case ASTREE_DEF_PARAM:
        node->symbol->dataType = DATATYPE_PARAM;
        break;
    }



    if(node->type == ASTREE_DEF_DECL||
        node->type == ASTREE_DEF_DECL_VEC ||
        node->type == ASTREE_DEF_DECL_VEC_INIT||
        node->type == ASTREE_DEF_DECL_POINTER ||
        node->type == ASTREE_DEF_FUNC ||
        node->type == ASTREE_DEF_PARAM)
    {
        if(node->son[1]->symbol == 0) {
            if(node->type == ASTREE_DEF_DECL)
                printf("E DECL \n");
            printf("Line %d: Declaration is missing the identifier name.\n", node->lineNumber);
        }
        else
        {
            if(node->symbol->dataType != DATATYPE_UNDEFINED)
                printf("Line %d: Symbol %s already defined.\n", node->lineNumber, node->symbol->text);
        }
    }
    astTreeCheck(node->son[0]);
    astTreeCheck(node->son[1]);
    astTreeCheck(node->son[2]);
    astTreeCheck(node->son[3]);
}

int expressionAnalyzes(ASTREE *ast, ASTREE *rootAux)
{
    int help, verified, expr1, expr2;
    int expFlag = 0;
    
    if(ast != 0)
    {
        switch(ast->type)
        {
            case ASTREE_DEF_ADD:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                if(pointer == 1)
                        expFlag = 1;
                pointer = 0;
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                if(expFlag == 1 && pointer == 1)
                    ilegalExp = 1;
                else if (expFlag == 1)
                {
                    pointer = 1;
                }
                expFlag = 0;
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                break;
        }
    }
    return help;
}

int operationTypesCheck(int expr1, int expr2)
{
    if((expr1 != 0) && (expr2 != 0))
    {
        if(expr1 != expr2)
        {
            if((expr1 == DATATYPE_BOOL) || (expr2 == DATATYPE_BOOL))
            {
                return 1;
            }
            if((expr1 == DATATYPE_WORD) || (expr2 == DATATYPE_WORD))
            {
                return 2;
            }
            if((expr1 == DATATYPE_BYTE) || (expr2 == DATATYPE_BYTE))
            {
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

int resultOperTypesCheck(int verified, int expr1, int expr2, int lineNumber)
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
                printf("WARNING - Line %d: word variable in the operation!!!\n", lineNumber);
            }
            if(verified == 3)
            {
                printf("WARNING - Line %d: byte variable in the operation!!!\n", lineNumber);
            }
        }
        if(expr1 >= expr2)
            help = expr1;
        else
            help = expr2;
    }
    return help;
}

// END OF FILE
