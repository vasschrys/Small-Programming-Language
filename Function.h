/*Functions without parameters Header File */

#ifndef Function_h
#define Function_h

#include <stdio.h>
#include <string.h>
#include "ExpressionUtils.h"
#include "Expression.h"

typedef struct F {
	Exp* exp; //the inner expression

} F;

extern F* declareFunc();
extern Exp* createFuncExp(char* input);
extern void printFunc(Exp* exp); 
extern void evaluateFunc(Exp* exp); 

#endif /* Function_h */
