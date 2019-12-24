/*ExpressionUtils Header File*/

#ifndef EXPRESSION_UTILS
#define EXPRESSION_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Expression.h"

Exp* createExp(char*);
void freeExp(Exp*);
void printExp(Exp*);
int evaluateExp(Exp*);
void appendExp(Exp*, Exp*);
Exp* subsetExp(Exp*, char*);

#endif