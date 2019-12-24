/*Variable Header File */

#ifndef Variable_h
#define Variable_h

#include <stdio.h>
#include <string.h>
#include "ExpressionUtils.h"
#include "Expression.h"

typedef struct Var {
	Exp* exp; //the inner expression

} Var;

extern Var* declareVar();
extern Exp* createVarExp(char* input);
extern void printVariable(Exp* exp); 
extern void evaluateVar(Exp* exp); 

#endif /* Variable_h */
