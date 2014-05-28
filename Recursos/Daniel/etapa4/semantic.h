//SEMANTIC ANALYSIS 2012
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "astree.h"

void checkDeclaration(ASTREE *root);

void checkVarDeclAsFunc(ASTREE *ast, char *text);

void checkFuncCall(ASTREE *ast, char *text);

void checkUtilization(ASTREE *root, ASTREE *rootAux);

int analisaExpressao(ASTREE *ast, ASTREE *rootAux);

int checkOperationTypes(int expr1, int expr2);

int checkResultOperTypes(int verified, int expr1, int expr2, int lineNumber);

int checkParamsFunc(ASTREE *ast, ASTREE *filho);

void checkUndeclared();

#endif
