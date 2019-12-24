/*Functions with Parameters Header File */

#ifndef ParamFunction_h
#define ParamFunction_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ExpressionUtils.h"
#include "Expression.h"
#include "Table.h"


typedef struct PF {
	Exp* exp; //the inner expression
    //Var* var; //array of variables

} PF;

extern PF* declarePF();
extern Exp* createPFExp(char* input);
extern void printPF(Exp* exp); 
extern void evaluatePF(Exp* exp); 
#endif /* ParamFunction_h */
