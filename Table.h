/*Table Header File */

#ifndef Table_h
#define Table_h

#include <stdio.h>
#include "Symbol.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


typedef struct {
    struct Symbol* head; 
    struct Symbol* tail; 

} SymbolTable;
 
extern void addSymbol(SymbolTable* table, char type, char* name, char* input2); 
extern struct Symbol* find(SymbolTable* table, char* );
extern SymbolTable* createTable();
extern int checkFind(SymbolTable* table, char* name);
extern int evaluationFunc(SymbolTable* table, char* name);
int evaluateFunc1(Exp* exp, SymbolTable* table);
int evaluateFunc2(Exp* exp, SymbolTable* table);
int evaluateFunc3(Exp* exp, char* c, SymbolTable* table);
extern int evaluateSubFunc(Exp* e, SymbolTable* table, char*);
extern char* evaluateSubFuncHelper(Exp* e, char* str, SymbolTable* table);
Exp* subsetExp2(Exp* exp, char* input) ;
Exp* subsetExpRec2(Exp* exp);




#endif /* Table_h */
