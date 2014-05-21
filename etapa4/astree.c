/*
UFRGS - Compiladores B - Marcelo Johann - 2014/1 - Etapa 3

Alunos: Guilherme Schwade e Guilherme Pretto.

Matrículas: 192332 e 213991.
*/

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"

int guardaTypeRet=0;
ASTREE *funcAst;
int scalDecl=0, pointer = 0, ilegalExp = 0;

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
int astTreeCheckDeclaration(ASTREE *root)
{
    int i, hasError = 0;

    if(root == 0) return hasError;

    if(root->type == ASTREE_DEF_DECL||
    root->type == ASTREE_DEF_DECL_VEC ||
    root->type == ASTREE_DEF_DECL_VEC_INIT||
    root->type == ASTREE_DEF_DECL_POINTER ||
    root->type == ASTREE_DEF_FUNC ||
    root->type == ASTREE_DEF_PARAM)
    {
        if(root->son[1]->symbol == 0) {
            printf("Line %d: Declaration is missing the identifier name.\n", root->lineNumber);
            hasError = 1;
        } else {
            if (root->son[1]->symbol->type != SYMBOL_IDENTIFIER){
                printf("Line %d: Symbol %s already defined.\n", root->lineNumber, root->son[1]->symbol->text);
                hasError = 1;
            }
            else if (root->type == ASTREE_DEF_DECL) root->son[1]->symbol->type = DATATYPE_VARIABLE;
            else if (root->type == ASTREE_DEF_DECL_VEC) root->son[1]->symbol->type = DATATYPE_VECTOR;
            else if (root->type == ASTREE_DEF_DECL_VEC_INIT) root->son[1]->symbol->type = DATATYPE_VECTOR;
            else if (root->type == ASTREE_DEF_DECL_POINTER) root->son[1]->symbol->type = DATATYPE_POINTER;
            else if (root->type == ASTREE_DEF_FUNC) root->son[1]->symbol->type = DATATYPE_FUNCTION;
            else if (root->type == ASTREE_DEF_PARAM) root->son[1]->symbol->type = DATATYPE_PARAM;
        }
    }

    hasError += astTreeCheckDeclaration(root->son[0]);
    hasError += astTreeCheckDeclaration(root->son[1]);
    hasError += astTreeCheckDeclaration(root->son[2]);
    hasError += astTreeCheckDeclaration(root->son[3]);

    return (hasError > 0) ? 1 : 0;
}

int astTreeCheckUndeclared(HASH_TABLE *Table)
{
    int address, result = 0;
    HASH_NODE *node;

    for(address=1;address < HASH_SIZE; address++)
        if(Table->node[address])
            for(node=Table->node[address]; node!=0; node=node->next)
                if(node->type == SYMBOL_IDENTIFIER){
                    printf("ERRO - Line %d: Expression %s is missing declaration!!!\n", node->lineNumber, node->text);
                    result = 1;
                }

    return result;
}





void astCheckNature(ASTREE *node,ASTREE *rootAux)
{
    int i,result, verRet=0, operIgual=0 , ePointer = 0, nPointer = 0;
    
    if(node==NULL) return;
    
    if((node->symbol != 0) && (node->type == ASTREE_DEF_FUNC))
    {
        guardaTypeRet = node->symbol->dataType; 
    }

    
    switch (node->type) 
    {
        case ASTREE_DEF_INPUT:
            if(node->son[0]->symbol->type != SYMBOL_SCALAR)
            {
                fprintf(stderr,"Semantic Error: Variable %s in INPUT is missing declaration at line %d \n",node->son[0]->symbol->text,node->lineNumber);
            }
            break;

        case ASTREE_DEF_RETURN:
            if(node->son[0]->type == ASTREE_DEF_FUNC_CALL)
            {
                printf("ERROR - Line %d: Returning a function!!!\n", node->lineNumber);
                return;
            }
            if(node->son[0]->type == ASTREE_DEF_VEC_ACCESS)
            {
                printf("ERROR - Line %d: Returning a vector. Sorry! This is not possible!!!\n", node->lineNumber);
            }
            else
            {
                verRet = expressionAnalyzes(node->son[0], rootAux);
                ePointer = pointer;
                pointer = 0;
                nPointer = ilegalExp;
                ilegalExp = 0;
                if(guardaTypeRet != verRet)
                {
                    switch(guardaTypeRet)
                    {
                        case DATATYPE_WORD:
                            printf("ERROR - Line %d: Returning type isn't the function type (word)!!!\n", node->lineNumber);
                            break;
                        case DATATYPE_BYTE:
                            printf("ERROR - at line %d: Returning type isn't the function type (byte).\n", node->lineNumber);
                            break;
                        case DATATYPE_BOOL:
                            printf("ERROR - at line %d: Returning type isn't the function type (bool).\n", node->lineNumber);
                            break;
                    }
                }
            }
            break;

        case ASTREE_DEF_IF:
            if(node->son[0]->son[0] == 0)
            {
                if(node->son[0]->type != ASTREE_DEF_SYMBOL)
                    printf("ERROR - at line %d: IF expression containig just a literal.\n", node->lineNumber);
            }
            else
            {
                if((node->son[0]->son[1] == 0) && (node->son[0]->symbol != 0))
                {
                    if(node->son[0]->type == ASTREE_DEF_FUNC_CALL)
                        printf("ERROR - at line %d: function being called into IF expression.\n", node->lineNumber);
                }
                else
                {
                    if((node->son[0]->son[1] != 0) && (node->son[0]->symbol == 0))
                        if(node->son[0]->type == (ASTREE_DEF_ADD || ASTREE_DEF_SUB || ASTREE_DEF_MUL || ASTREE_DEF_DIV))
                            printf("ERROR - at line %d: arithmetic operation into an IF expression.\n", node->lineNumber);
                }
            }
            break;

            case ASTREE_DEF_IFELSE:
                if(node->son[0]->son[0] == 0)
                {
                    if(node->son[0]->type != ASTREE_DEF_SYMBOL)
                        printf("ERROR - at line %d: IF expression containig just a literal.\n", node->lineNumber);
                }
                else
                {
                    if((node->son[0]->son[1] == 0) && (node->son[0]->symbol != 0))
                    {
                        if(node->son[0]->type ==  ASTREE_DEF_FUNC_CALL)
                            printf("ERROR - at line %d: function being called into IF expression.\n", node->lineNumber);
                    }
                    else
                    {
                        if((node->son[0]->son[1] != 0) && (node->son[0]->symbol == 0))
                            if(node->son[0]->type == (ASTREE_DEF_ADD || ASTREE_DEF_SUB || ASTREE_DEF_MUL || ASTREE_DEF_DIV))
                                printf("ERROR - at line %d: arithmetic operation into an IF expression.\n", node->lineNumber);
                    }
                }
                break;

            case ASTREE_DEF_LOOP:
                if(node->son[0]->son[0] != 0)
                {
                    if((node->son[0]->son[1] == 0) && (node->son[0]->symbol != 0))
                    {
                        if(node->son[0]->type == ASTREE_DEF_FUNC_CALL)
                            printf("ERROR - at line %d: function being called into LOOP expression.\n", node->lineNumber);
                    }
                    else
                    {
                        if((node->son[0]->son[1] != 0) && (node->son[0]->symbol == 0))
                            if(node->son[0]->type == (ASTREE_DEF_ADD || ASTREE_DEF_SUB || ASTREE_DEF_MUL || ASTREE_DEF_DIV))
                                printf("ERROR - at line %d: arithmetic operation into an LOOP expression.\n", node->lineNumber);
                    }
                }
                break;

            /*case ASTREE_DEF_FUNC_CALL:
                if(node->symbol->type != SYMBOL_IDENTIFIER)
                {
                    if(node->symbol->type == DATATYPE_FUNCTION)
                    {
                        funcAst = 0;                    
                        funcCallCheck(rootAux, node->symbol->text);
                        result = paramsFuncCheck(funcAst->symbol->ast, node);
                        if(result == 1)
                            printf("ERROR - at line %d: Function %s containing MORE parameters than the number declared.\n", node->lineNumber, node->symbol->text);
                        else
                            if(result == 2)
                                 printf("ERROR - at line %d: Function %s containing LESS parameters than the number declared.\n", node->lineNumber, node->symbol->text);
                            else
                                if(result == 3)
                                    printf("ERROR - at line %d: Parameters of the function %s have different types or they are not declared.\n", node->lineNumber, node->symbol->text);
                    }
                }
                break;*/

        case (ASTREE_DEF_ATTR):
            funcAst = 0;
            scalDecl = 0;
            if (node->son[0]->symbol != NULL){
                varDeclAsFuncCheck(rootAux, node->son[0]->symbol->text);
            }
            if(scalDecl == 1)
            {
                if(funcAst->symbol->type == DATATYPE_FUNCTION)
                    printf("ERROR - at line %d: Variable %s is using the same name of a function.\n", node->lineNumber, node->son[0]->symbol->text);
                else
                    if(node->son[0]->type == ASTREE_DEF_SYMBOL)
                        printf("ERROR - at line %d: Variable %s is declared as a vector.\n", node->lineNumber, node->son[0]->symbol->text);
            }
            if(scalDecl == 2)
            {
                if(node->son[0]->type != ASTREE_DEF_SYMBOL)
                    printf("ERROR - at line %d: Variable %s is declared as a scalar.\n", node->lineNumber, node->son[0]->symbol->text);
            }
            if(node->son[0]->type == ASTREE_DEF_SYMBOL)
            {
                if(node->son[0]->symbol->dataType != 0)
                {   
                    operIgual = expressionAnalyzes(node->son[1], rootAux);
                    ePointer = pointer;
                    pointer = 0;
                    nPointer = ilegalExp;
                    ilegalExp = 0;
                    if(operIgual != 0)
                    {
                        if(nPointer == 1)
                        {
                            printf("ERROR - at line %d: Ilegal expression with pointer.\n", node->lineNumber);
                        }
                        if((node->son[0]->symbol->type == DATATYPE_POINTER) && (ePointer != 1))
                        {
                            printf("ERROR - at line %d: Variable %s is a pointer and can only receive expressions with pointer.\n", node->lineNumber, node->son[0]->symbol->text);

                        }
                        if((node->son[0]->symbol->type != DATATYPE_POINTER) && (ePointer == 1))
                        {
                            printf("ERROR - at line %d: Variable %s is not a pointer and cannot receive expressions with pointer.\n", node->lineNumber, node->son[0]->symbol->text);
                        }
                        if((node->son[0]->symbol->type != DATATYPE_POINTER) && (ePointer != 1))
                        {
                            if(node->son[0]->symbol->dataType != operIgual)
                            {
                                if(node->son[1]->type == ASTREE_DEF_FUNC_CALL)
                                    if(node->son[1]->symbol->type != DATATYPE_FUNCTION)
                                        printf("ERROR - at line %d: Variable %s is not declared as a function, but it is being used as one.\n", node->lineNumber, node->son[1]->symbol->text);
                                switch(node->son[0]->symbol->dataType)
                                {
                                    case DATATYPE_WORD:
                                        if(operIgual == DATATYPE_BOOL)
                                            printf("ERROR - at line %d: Variables containing different types.\n", node->lineNumber);
                                        break;
                                    case DATATYPE_BOOL:
                                        if((operIgual == DATATYPE_WORD) || (operIgual == DATATYPE_BYTE))
                                            printf("ERROR - at line %d: Variables containing different types.\n", node->lineNumber);
                                        break;
                                    case DATATYPE_BYTE:
                                        if(operIgual == DATATYPE_BOOL)
                                            printf("ERROR - at line %d: Variables containing different types.\n", node->lineNumber);
                                        break;
                                }
                            }
                            else
                                if(node->son[1]->type == ASTREE_DEF_FUNC_CALL)
                                    if(node->son[1]->symbol->type != DATATYPE_FUNCTION)
                                        printf("ERROR - at line %d: Variable %s is not declared as a function, but it is being used as one.\n", node->lineNumber, node->son[1]->symbol->text);
                        }
                    }
                }
            }
            else
            {
                if(node->son[0]->symbol->dataType != 0)
                {
                    operIgual = expressionAnalyzes(node->son[0]->son[0], rootAux);
                    pointer = 0;
                    nPointer = ilegalExp;
                    ilegalExp = 0;
                    if(operIgual != 0)
                    {
                        if(operIgual != DATATYPE_WORD)
                        {
                                printf("ERROR - at line %d: Vector containing wrong parameters.\n", node->lineNumber);
                        }
                        operIgual = expressionAnalyzes(node->son[1], rootAux);
                        ePointer = pointer;
                        pointer = 0;
                        nPointer = ilegalExp;
                        ilegalExp = 0;
                        if(nPointer == 1)
                        {
                            printf("ERROR - at line %d: Ilegal expression with pointer.\n", node->lineNumber);
                        }
                        if((node->son[0]->symbol->type != DATATYPE_POINTER) && (ePointer == 1))
                        {
                            printf("ERROR - at line %d: Variable %s is not a pointer and cannot receive expressions with pointer.\n", node->lineNumber, node->son[0]->symbol->text);
                        }
                        if(node->son[0]->symbol->dataType != operIgual)
                        {
                            if(node->son[1]->type == ASTREE_DEF_FUNC_CALL)
                                if(node->son[1]->symbol->type != DATATYPE_FUNCTION)
                                    printf("ERRO - Line %d: Variable %s is not declared as a function, but it is being used as one!!!\n", node->lineNumber, node->son[1]->symbol->text);                          
                            if((node->son[0]->symbol->type != DATATYPE_POINTER) && (ePointer != 1))
                                            {
                                switch(node->son[0]->symbol->dataType)
                                {
                                    case DATATYPE_WORD:
                                        if(operIgual == DATATYPE_BOOL)
                                            printf("ERROR - at line %d: Variables containing different types.\n", node->lineNumber);
                                        break;
                                    case DATATYPE_BOOL:
                                        if((operIgual == DATATYPE_WORD) || (operIgual == DATATYPE_BYTE))
                                            printf("ERROR - at line %d: Variables containing different types.\n", node->lineNumber);
                                        break;
                                    case DATATYPE_BYTE:
                                        if(operIgual == DATATYPE_BOOL)
                                            printf("ERROR - at line %d: Variables containing different types.\n", node->lineNumber);
                                        break;
                                }
                            }
                        }
                        else
                            if(node->son[1]->type == ASTREE_DEF_FUNC_CALL)
                                if(node->son[1]->symbol->type != DATATYPE_FUNCTION)
                                    printf("ERRO - Line %d: Variable %s is not declared as a function, but it is being used as one!!!\n", node->lineNumber, node->son[1]->symbol->text);
                    }
                }
            }
            break;

        default:
        break;
    }
    
    for(i=0; i<MAX_SONS; i++)
       if(node->son[i]) 
        astCheckNature(node->son[i],rootAux);
}


int expressionAnalyzes(ASTREE *ast, ASTREE *rootAux)
{
    int help, verified, expr1, expr2;
    int expFlag = 0;

    if(ast != 0)
    {
        switch(ast->type)
        {
            case ASTREE_DEF_SYMBOL:
                funcAst = 0;
                scalDecl = 0;
                varDeclAsFuncCheck(rootAux, ast->symbol->text);
                if(scalDecl == 1)
                {
                    if(funcAst->symbol->type == DATATYPE_FUNCTION)
                        printf("ERRO - Line %d: Variable %s is using the same name of a function!!!\n", ast->lineNumber, ast->symbol->text);
                    else
                        printf("ERRO - Line %d: Variable %s is declared as a vector!!!\n", ast->lineNumber, ast->symbol->text);
                }
                if(scalDecl == 3)
                    pointer = 1;
                help = ast->symbol->dataType;
                break;

            case ASTREE_DEF_FUNC_CALL:
                if(ast->symbol->dataType == 0)
                {
                    help = 0;
                }
                else
                    help = ast->symbol->dataType;
                break;

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
            
            case ASTREE_DEF_SUB:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_MUL:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_DIV:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_OP_AND:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_OP_OR:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_OP_LE:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_OP_GE:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_OP_EQ:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_OP_NE:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_GREATER:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_LESS:
                expr1 = expressionAnalyzes(ast->son[0], rootAux);
                expr2 = expressionAnalyzes(ast->son[1], rootAux);
                verified = operationTypesCheck(expr1, expr2);
                help = resultOperTypesCheck(verified, expr1, expr2, ast->lineNumber);
                if(pointer == 1)
                    ilegalExp = 1;
                break;

            case ASTREE_DEF_VEC_ACCESS:
                funcAst = 0;
                scalDecl = 0;
                varDeclAsFuncCheck(rootAux, ast->symbol->text);
                if(scalDecl == 1)
                {
                    if(funcAst->symbol->type == DATATYPE_FUNCTION)
                        printf("ERRO - Line %d: Variable %s is using the same name of a function!!!\n", ast->lineNumber, ast->symbol->text);
                }
                if(ast->symbol->dataType != 0)
                    help = ast->symbol->dataType;
                else
                    help = 0;
                break;
        }
    }
    return help;
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

void funcCallCheck(ASTREE *ast, char *text)
{
    int i;

    if(ast==0)
        return;

    if((ast->symbol!=0) && (ast->type == ASTREE_DEF_FUNC))
    {
        if(strcmp(ast->symbol->text, text) == 0)
        {
            funcAst = ast;
            return;
        }
    }
    for(i=0; i < MAX_SONS; i++)
        funcCallCheck(ast->son[i], text);
} 

void varDeclAsFuncCheck(ASTREE *ast, char *text)
{
    int i;
    
    if(ast==0)
        return;

    if((ast->symbol!=0) && ((ast->type == ASTREE_DEF_FUNC) || (ast->symbol->type == DATATYPE_VECTOR)))
    {
        if(strcmp(ast->symbol->text, text) == 0)
        {
            funcAst = ast;
            scalDecl = 1;
            return;
        }
    }
    
    if((ast->symbol!=0) && (ast->symbol->type == SYMBOL_SCALAR))
    {
        if(strcmp(ast->symbol->text, text) == 0)
        {
            funcAst = ast;
            scalDecl = 2;
            return;
        }
    }
    
    if((ast->symbol!=0) && (ast->symbol->type == DATATYPE_POINTER))
    {
        if(strcmp(ast->symbol->text, text) == 0)
        {
            funcAst = ast;
            scalDecl = 3;
            return;
        }
        }
    for(i=0; i < MAX_SONS; i++)
        varDeclAsFuncCheck(ast->son[i], text);
}

int paramsFuncCheck(ASTREE *ast, ASTREE *filho)
{
    int cont = 0;
    ASTREE *nodeSon = 0;

    nodeSon = filho->son[0];
    
    do
    {
        if(ast == 0)
        {
            if(nodeSon != 0)
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
            if(nodeSon == 0)
            {
                cont = 2;
                return cont;
            }
            else
            {  
               if(ast->symbol){
                switch(ast->symbol->dataType)
                {
                    case DATATYPE_WORD:
                        if(nodeSon->son[0] != 0)
                        {
                            if(nodeSon->son[0]->type != SYMBOL_LIT_INTEGER)
                            {
                                if(nodeSon->son[0]->symbol->dataType != DATATYPE_WORD)
                                    {
                                        cont = 3;
                                        return cont;
                                    }
                                 else
                                    {
                                        cont = 0;
                                    }
                            }
                            else
                            {
                                cont = 0;
                            }
                        }   
                        break;
                    case DATATYPE_BYTE:
                        if(nodeSon->son[0] != 0)
                        {
                            if(nodeSon->son[0]->type != SYMBOL_LIT_INTEGER)
                            {
                                if(nodeSon->son[0]->symbol->dataType != DATATYPE_BYTE)
                                    {
                                        cont = 3;
                                        return cont;
                                    }
                                 else
                                    {
                                        cont = 0;
                                    }
                            }
                            else
                            {
                                cont = 0;
                            }
                        }   
                        break;
                    case DATATYPE_BOOL:
                        if(nodeSon->son[0] != 0)
                        {
                            if((nodeSon->son[0]->type != SYMBOL_LIT_TRUE) && (nodeSon->son[0]->type != SYMBOL_LIT_FALSE))
                            {
                                if(nodeSon->son[0]->symbol->dataType != DATATYPE_BOOL)
                                    {
                                        cont = 3;
                                        return cont;
                                    }
                                 else
                                    {
                                        cont = 0;
                                    }
                            }
                            else
                            {
                                cont = 0;
                            }
                        }   
                        break;
                    default:
                        break;
                }
               }
            }
        } 
        ast = ast->son[1];
        nodeSon = nodeSon->son[1];
    }while(1);
}

// END OF FILE
