//
//  ParamFunction.c
//  
//
//  Created by Lia Chrysanthopoulos on 12/4/19.
//

#include "ParamFunction.h"



/* Allocates space for an Exp and returns pointer. */
PF* declarePF() {

	return (PF*) calloc(1, sizeof(PF));

}


/* Sets values for an Exp continaing a symbol. */
Exp* createPFExp(char* input) {
	Exp* exp = declarePF()->exp; 
	exp = createExp(input);
	return exp; 
}

/* Prints Expression */
void printPF(Exp* exp){
	printExp(exp);

}

/* Evaluates Expression */
void evaluatePF(Exp* exp){

	printf("%i\n", evaluateExp(exp));
}

/* Returns the evaluated expression Expression */
int returnEval(Exp* exp){
	return evaluateExp(exp);
}

