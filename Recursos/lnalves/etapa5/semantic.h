#include "astree.h"

void checkDeclarations(ASTREE *root);
void checkUtilization(ASTREE *root);
void checkDataTypes(ASTREE *root);
void checkFunctionCallParameters(ASTREE *root);
void checkListParams(ASTREE *declParams, ASTREE *callParams, ASTREE *root);
int checkExpressionType(ASTREE *expression);
void checkFunctionReturn(ASTREE *root, ASTREE *aux);
void checkRightSideAssType(ASTREE *root, int type);
void checkRightSideAss(ASTREE *root, ASTREE *aux);