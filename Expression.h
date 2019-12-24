/*Expression Header File*/

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <stdlib.h>

typedef struct Exp {

	struct Exp* first; //the inner expression
	struct Exp* rest; //the rest of the expression (only used if symbol == NULL)
	char* symbol; //number or operation symbol (only used if first == NULL)

} Exp;

Exp* makeSymbolExp(char*, Exp*);
Exp* makeFirstExp(Exp*, Exp*);
void initializeFirstExp(Exp* exp, Exp* first, Exp* rest); //Lia added this

#endif