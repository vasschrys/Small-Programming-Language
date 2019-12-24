/*Expression C File*/

#include "Expression.h"

/* Allocates space for an Exp and returns pointer. */
Exp* declareExp() {

	return (Exp*) calloc(1, sizeof(Exp));

}


/* Sets values for an Exp continaing a symbol. */
void initializeSymbolExp(Exp* exp, char* symbol, Exp* rest) {

	exp->symbol = symbol;
	exp->rest = rest;

}

/* Sets values for an Exp continaing a first pointer. */
void initializeFirstExp(Exp* exp, Exp* first, Exp* rest) {

	exp->first = first;
	exp->rest = rest;

}


/* Declares and initialzes an Exp conataining a symbol. */
Exp* makeSymbolExp(char* symbol, Exp* rest) {

	Exp* exp = declareExp();
	initializeSymbolExp(exp, symbol, rest);
	return exp;

}


/* Declares and initialzes an Exp conataining a first pointer. */
Exp* makeFirstExp(Exp* first, Exp* rest) {

	Exp* exp = declareExp();
	initializeFirstExp(exp, first, rest);
	return exp;

}