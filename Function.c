/*Function C File*/

#include "Function.h"

/* Allocates space for an Exp and returns pointer. */
F* declareFunc() {

	return (F*) calloc(1, sizeof(F));

}

/* Sets values for an Exp continaing a symbol. */
Exp* createFuncExp(char* input) {

	Exp* exp = declareFunc()->exp; 
	exp = createExp(input);
	return exp; 
}

/* Prints Function */
void printFunc(Exp* exp){
	printExp(exp);

}

/* Evaluates Expression */
void evaluateFunc(Exp* exp){
    printf("%i\n", evaluateExp(exp));
}
