/*Symbol C File*/

#include "Symbol.h"
#include "Variable.h"
#include "Table.h"
#include "Function.h"
#include "ExpressionUtils.h"
#include "Expression.h"
#include "ParamFunction.h"

/* Allocates space for an Symbol and returns pointer. */
Symbol* createSymbol() {
	return (Symbol*) calloc(1, sizeof(Symbol));
}

/* Sets values for a Symbol. */
void initializeSymbol(struct Symbol* s, char type, char* name, char* input) {

    s->type = type; 
    s->name = name;
    s->next = NULL;
    s->input = input;
    switch(type){
        case 'v' :
        s->typeOf = createVarExp(input); 
        return; 
        
        case 'd':
        s->typeOf = createFuncExp(input); 
        return; 
        
        case 'l':
        s->typeOf = createPFExp(input); 
        return; 
    }

}

/*Saves variables for functions with parameters*/
char* saveVars(char* input){
    char* result= (char*) malloc(sizeof(char*)*50);
    int count = 0; 
    int i =0; 
    while(i < strlen(input)){
        if(input[i] != ' ' && input[i] != '\n'){
            result[count] = input[i];
            count++; 
        }
        i++; 
        
    }
    return result; 
}

/*Checks which kind of expression you want to print*/
void checkPrint(Symbol* s){
    switch(s->type){
        case 'v' :
        printVariable(s->typeOf);
        return; 
        
        case 'd':
        printFunc(s->typeOf);
        return; 
        
        case 'l':
        printPF(s->typeOf);
        return; 
    }
}

/*Checks for letter in string*/
int checkLetter(char* str){

    for(int i =0; i<strlen(str); i++){
        int ans  = isalpha(str[i]);
        if(ans !=0){

            return 1; 
        }
    }
    return 0; 
}



/*checks how to evaluate the symbol based on character type*/
void checkEval(Symbol* s){
    

    switch(s->type){

        case 'v' :
        evaluateVar(s->typeOf);
        return; 
        
        case 'd':
        evaluateFunc(s->typeOf);
        return; 
        
        case 'l':
        printf("cannot Evaluate a Function with Parameters");
        return; 
    }

}


/*Creates a new string */
char* createNewString(char* parameter, char* name, char* input){
	char* ptr; 
	int size = strlen(input);
	char* newstring = (char*) calloc(size, sizeof(char*));
	char snum[30];

	for(int i =0; i<strlen(input); i++){
		if(isalpha(input[i])){   //if the input is a character
			if(input[i] == name[0]){
				continue;
				newstring[i] = input[i];
				
			}
			else if(input[i] != name[0]){
				newstring[i] = parameter[i];
			}
			else{
				newstring[i] = input[i];
			}

		}
		
	}
	return newstring;
}






