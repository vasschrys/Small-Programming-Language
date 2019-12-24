/*ExpressionUtils C File*/

#include "ExpressionUtils.h"
#include "Table.h"

char* p; //Used to step through the input from different recursive levels.

/* Recursivly creates an expression using p as the current string position. */
Exp* createExpRec() {

	// If the current char is a space, recursivly move to the next char.
	if(*p == ' ') {
		p++;
		return createExpRec();
	}

	// If the current char is a right parenthasees, the rest is NULL.
	if((*p == ')') || (*p == '\n')) {
		p++;
		return NULL;
	}

	/* If the current char is a left parenthasees, recursivly create first expression 
	in parenthasees and create rest starting where inner expression ended. */
	if(*p == '(') {
		p++;
		Exp* first = createExpRec();
		return makeFirstExp(first, createExpRec());
	}

	/* If the current char is a digit, copy all sequential digits to the symbol of the current
	expression. Then, recursivly create rest starting after the digits. */
	if(isdigit(*p)) {
		int i;
		for(i=0; isdigit(p[i]); i++);
		char* symbol = (char*) calloc(i+1, sizeof(char));
		strncpy(symbol, p, i);
		p += i;
		return makeFirstExp(makeSymbolExp(symbol, 0), createExpRec());
	
	}

//MAKE THIS AN IF 
	/*If the current char is a operation, copy it to the symbol of the current expression. Then,
	recursivly create rest starting at the next char*/
	if(*p == '+' || *p == '-' || *p == '*' ){
	char* symbol = (char*) calloc(2, sizeof(char));
	*symbol = *(p++);
	return makeFirstExp(makeSymbolExp(symbol, 0), createExpRec());
	}

//ELSE IT MUST BE A VARIABLE OR A FUNTION, FROM HER GO LOOK THROUGH 
//YOUR SYMBOOL TABLE FOR THE MATCHING THING?
    /*If the current char is a function or variable*/
	
    else{
        int i;
			for(i=0; isalpha(p[i]) || isdigit(p[i]); i++);
			char* symbol = (char*) calloc(i+1, sizeof(char));
			strncpy(symbol, p, i);
			p += i;
			return makeFirstExp(makeSymbolExp(symbol, 0), createExpRec());
		
    }

}

/* Creates an expression from string at input. */
Exp* createExp(char* input) {

	p = input;
	for(; *p == ' '; p++); // Removes unecessary initial parenthasees
	if(*p == '(') p++;
	return createExpRec();

}

/* Recursively frees all allocated memory used to store a expression starting at exp. */
void freeExpRec(Exp* exp) {

	if(!exp) return;

	if(exp->symbol)
		free(exp->symbol);

	// Recursivly free first and rest pointers in exp
	freeExpRec(exp->first);
	freeExpRec(exp->rest);

	free(exp);

}

/* Frees all allocated memory used to store a expression starting at exp. */
void freeExp(Exp* exp) {

	freeExpRec(exp);

}

/* Recursivly prints expression starting at exp. */
void printExpRec(Exp* exp) {

	if(exp->symbol) {
		printf("%s", exp->symbol);
		return;
	}

	// Determins whether first is a inner statement and, if so, prints open parenthasees.
	bool innerExp = false;
	//&& (!isalpha(*(exp->first->symbol)))
	if(exp->first->symbol && (!isdigit(*(exp->first->symbol)))  ) {
		innerExp = true;
		printf("(");
	}


	// Recursivly prints first expression.
	printExpRec(exp->first);

	// If exp has a rest, recursivly prints it.
	if(exp->rest) {
		printf(" ");
		printExpRec(exp->rest);
	}

	// Closes parenthasees if needed.
	if(innerExp) printf(")");

}

/* Prints expression starting at exp. */
void printExp(Exp* exp) {

	printExpRec(exp);
	printf("\n");

}

/* Dummy addition function to use in Evaluate() */
int add(int a, int b) {

	return a + b;

}

/* Dummy multiplication function to use in Evaluate() */
int mult(int a, int b) {

	return a * b;

}


/* Recursivly evaluates expression starting at exp using the combination function pointed to
by combine and returns its value. */
int evaluateExpRec(Exp* exp, int (*combine)(int, int)) {

	// If exp has symbol, return its value.
	if(exp->symbol)
		return atoi(exp->symbol);
 
 	// If the first of exp is a operation, evaluate it.
	if(exp->first->symbol && (!isdigit(*(exp->first->symbol)))) {
		switch(*(exp->first->symbol)) {
			// If operation is addition, recursivly evaluate the rest expression with the add() function.
			case '+':
				return evaluateExpRec(exp->rest, &add);
			/* If operation is subtraction, recursivly evaluate the next exp and subtract the value of the
			remaining expression evaluated recursivly using the add() function. */
			case '-':
				return evaluateExpRec(exp->rest->first, 0) - evaluateExpRec(exp->rest->rest, &add);
				// If operation is multiplicaiton, recursivly evaluate the rest expression with the mult() function.
			case '*':
				return evaluateExpRec(exp->rest, &mult);
			
			default:
				
				return evaluateExpRec(exp->rest, &mult);
				// char* ans = exp->first->symbol; 
				// if(smolFind(ans) != NULL){ // find the function 

				// 	return evaluateExpRec(ans, combine);
				// }
				
		}
	}

	// If exp has rest, return the combination of first and rest using the combination function pointer.
	if(exp->rest)
		return (*combine)(evaluateExpRec(exp->first, 0), (evaluateExpRec(exp->rest, combine)));	

	// If exp doesn't has rest, return the value of first.
	return evaluateExpRec(exp->first, 0);

}




/* Evaluates expression starting at exp. */
int evaluateExp(Exp* exp) {
	
	return evaluateExpRec(exp, 0);

}

/* Returns the last exp in the expression starting at exp. */
Exp* appendExpRec(Exp* exp) {

	if(exp->rest)
		return appendExpRec(exp->rest);
	
	return exp;

}

/* Appends rest to the last exp in expression starting at exp */
void appendExp(Exp* exp, Exp* rest) {
	
	/* If rest is just a number, make it the last value in exp. If rest is more complex, 
	make it a inner expression at the end of exp. */
	if(!rest->first->symbol || isdigit(*(rest->first->symbol)))
		appendExpRec(exp)->rest = rest;
	else
		appendExpRec(exp)->rest = makeFirstExp(rest, 0);

}

/* Recursivly returns subset of exp according to string at p. */
Exp* subsetExpRec(Exp* exp) {

	// If the current char is a space, recursivly return subset at next char.
	if(*p == ' ') {
		p++;
		return subsetExpRec(exp);
	}

	// If the current char is 'r', recursivly return subset from rest at next char.
	if(*p == 'r') {
		p++;
		return subsetExpRec(exp->rest);
	}

	// If the current char is 'r', recursivly return subset from first at next char.
	if(*p == 'f') {
		p++;
		return subsetExpRec(exp->first);
	}

	// If string is empty, return exp.
	return exp;

}


/* Returns subset of exp according to string at input. */
Exp* subsetExp(Exp* exp, char* input) {

	p = input;
	return subsetExpRec(exp);

}