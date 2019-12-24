/*Variable C File*/

#include "Variable.h"

/* Allocates space for an Exp and returns pointer. */
Var* declareVar() {

	return (Var*) calloc(1, sizeof(Var));

}

/*Create a Variable expression */
Exp* createVarExp(char* input) {

	Exp* exp = declareVar()->exp; 
	exp = createExp(input);
	return exp; 
}

/*Prints a Variable expression */
void printVariable(Exp* exp){
	printExp(exp);

}

/*Evaluate a variable expression*/
void evaluateVar(Exp* exp){
	//int ans = evaluateExp(exp);
	printf("%i\n", evaluateExp(exp));
}





