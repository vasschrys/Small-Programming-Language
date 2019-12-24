/*CommandLine C file -- MAIN is run from here*/

#include "CommandLine.h"
#include "Symbol.h"
#include "Table.h"
#include "ParamFunction.h"

/* Prints command instructions. Then, repeatedly reads and processes commands 
(accepting secondary input when needed). */
void commandLine() {

	Exp* currentExp = 0; // Pointer to current expression
	char cmd[200]; // Stores command input
	char* input = malloc(sizeof(char)*200); // Pointer to secondary input
	char* input2 = malloc(sizeof(char)*200); // Pointer to secondary input
	char* input3 = malloc(sizeof(char)*200); 
	SymbolTable* table = createTable(); 
	char* fooVar = malloc(sizeof(char)*200);
	printf("c - create new expression\n");
	printf("p - print current expression\n");
	printf("e - evaluate a expression\n");
	printf("a - append current expression\n");
	printf("s - print subset of current expression\n");
	printf("v - create and define a variable\n");
	printf("d - create and define a function without parameters\n");
	printf("l - create and define a function with paramters\n");
	printf("q - quit\n");
	printf("--------------------------------\n\n");

	// Continuously accepts and processes commands
	while(true) {

		//Reads command
		fgets(cmd, 200, stdin);

		switch(*cmd) {
			case 'c': // Frees old current expression and creates new one from input
				
				fgets(input2, 200, stdin);
				freeExp(currentExp);
				char* cname2 = strdup((input2));
				
				if(cname2[strlen(cname2) -1] == 10){
       				 cname2[strlen(cname2) -1] = 0;

   				}	
				
				addSymbol(table, 'd', "foo", cname2);
				Symbol* symb = find(table, "foo");
				currentExp = symb->typeOf;
				continue;  

			case 's': 
				fgets(input, 200, stdin);
				printExp(subsetExp(currentExp, input));
				continue;
			
			case 'v': 
	
				fgets(input, 200, stdin);
				char* name = strdup(input); 
				fgets(input2, 200, stdin);
				char* name2 = strdup((input2));
    			if(name[strlen(name) -1] == 10){
       				 name[strlen(name) -1] = 0;

   				}	

				addSymbol(table, 'v', name, name2);
				continue; 

			case 'd': 
				fgets(input, 200, stdin);
				char* Funcname = strdup(input); 
				fgets(input2, 200, stdin);
				char* Funcname2 = strdup((input2));
				if(Funcname[strlen(Funcname) -1] == 10){
       				 Funcname[strlen(Funcname) -1] = 0;

   				}
				addSymbol(table, 'd', Funcname, Funcname2);
				continue;  
			case 'l':
				fgets(input, 200, stdin); 
				char* pfName = strdup(input);  //'fl'
				fgets(input2, 200, stdin);
				char* parameters = strdup((input2)); //variables
				fgets(input3, 200, stdin); //exp
				char* pFexp = strdup((input3));
				fooVar = saveVars(parameters);
				
				if(pfName[strlen(pfName) -1] == 10){
       				 pfName[strlen(pfName) -1] = 0;

   				}
				addSymbol(table, 'l', pfName, pFexp);
				continue;  

			case 'p' :
				fgets(input2, 200, stdin);
				char* varVal = strdup((input2));
				
				if(varVal[strlen(varVal) -1] == 10){
       				 varVal[strlen(varVal) -1] = 0;

   				}

				Symbol* symbol = find(table, varVal);
				checkPrint(symbol);
				continue; 

			case 'e': // Prints the numerical of the current expression
				fgets(input2, 200, stdin);
				char* eVal = strdup((input2));
				if(eVal[strlen(eVal) -1] == 10){
       				 eVal[strlen(eVal) -1] = 0;

   				}
				
				printf("%i\n",evaluationFunc(table, eVal));

				continue;
			case 'a': // Appends the inputted expression to the current expression
				fgets(input, 200, stdin);
				appendExp(currentExp, createExp(input));
				continue;
			case 'q': // Frees allocated memory and exits function
				freeExp(currentExp);
				free(input);
				return;
			

		}

		// If the first character is not recognized as a command
		printf("'%c' is not a valid command\n", *cmd);

	}

}

int main() {

	commandLine();

}
