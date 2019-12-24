/*Symbol Header File*/

#ifndef Symbol_h
#define Symbol_h

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Variable.h"
#include "Function.h"
#include "ExpressionUtils.h"
#include "Expression.h"
#include "ParamFunction.h"


typedef struct Symbol{ 
    char* input; 
    char type; 
    void* typeOf; 
    char* name; 
    struct Symbol* next; 
    struct Symbol* prev; 
} Symbol; 

extern void initializeSymbol(struct Symbol* symbol, char type, char* name, char* input);
extern struct Symbol* createSymbol(); 
extern void checkPrint(Symbol* s);
extern void checkEval(Symbol* s);
extern char* saveVars(char* input);
extern int checkLetter(char* str);

#endif /* Symbol_h */
