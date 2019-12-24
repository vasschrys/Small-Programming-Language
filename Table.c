/*Table C File*/


#include "Table.h"
char *ptr; 


SymbolTable* createTable(){
    SymbolTable* table = (SymbolTable*) malloc(sizeof(SymbolTable)); //create space 
    table->head = NULL;
    table->tail = NULL;

    return table; 
}


/*Adds a symbol to the table - (linkedlist)*/
void addSymbol(SymbolTable* table, char type, char* name, char* input){
    
    Symbol* symb= createSymbol(); 
    initializeSymbol(symb, type, name, input);

    if(table->head == NULL){
        table->head = symb; 
        table->tail = symb; 
    }
    
    else    
    {
        //check if already exists in table
        if((checkFind(table, name)) == 1) { //not in table

        symb->prev = table->tail; 
        (table->tail)->next = symb; 
        table->tail = symb; 

        }
        
        else{ //is in table

          
            Symbol* foundSymb = find(table, name); //find symbol name

            //if its the head && tail
            if(foundSymb == table->head && foundSymb == table->tail){
                table->head = symb; 
                table->tail = symb;
            }
            //if its the head
            else if(foundSymb == table->head ){
                symb->next = foundSymb->next; 
                
                Symbol* temp = foundSymb->next;
                temp->prev = symb; 
                table->head = symb;  

            }
            else if(foundSymb == table->tail){
                Symbol* temp = foundSymb->prev;
                temp->next = symb;
                symb->prev = temp; 
                table->tail = symb;  

            }else{

            Symbol* temp = foundSymb->prev; 
            temp->next = symb; 
            symb->prev = temp; 

            Symbol* tempN = foundSymb->next; 
            tempN->prev = symb; 
            symb->next = tempN; 

            } 
        }
    }
     
}

/*checks if the function is in the table*/
Symbol* find(SymbolTable* table, char* name){

    if(table->head == NULL){
        return NULL; 
    }
    Symbol* current = table->head; 
    while(current != NULL){
        if(strcmp(name, current->name) == 0) {
            return current; 
        }
        current = current->next; 
    }
    return NULL; 
}


/*check if name is found returns an int*/
int checkFind(SymbolTable* table, char* name){
    if(find(table, name) == NULL){ //not in table
        return 1; 
    }
    else{
        return 0; //in table
    }

}

/*Evaluation function for both evaluation of variables and numbers*/
int evaluationFunc(SymbolTable* table, char* name){
    Symbol* s= find(table, name);
    Exp* e = s->typeOf;
    if((strcmp(e->first->symbol, "f")== 0) || (strcmp(e->first->symbol,"r")==0)){
       return  evaluateSubFunc(e, table, s->input);

    }
    else{
        return evaluateFunc1( e, table);
    }
     

}

/*Evaluation Function for expressions with variables*/
int evaluateFunc1(Exp* exp, SymbolTable* table){
    char *symbPtr = (char*)calloc(1, 100*sizeof(char)); 
    strcpy(symbPtr, exp->first->symbol);
    if(exp->rest ==0){
        return atol(exp->first->symbol); 
    }
    int other = 0; 

    switch(*(symbPtr)) {
			// If operation is addition, recursivly evaluate the rest expression with the add() function.
			case '+':
				 other = evaluateFunc2(exp->rest, table);
                 if(exp->rest->rest != NULL){ 
                    return other + evaluateFunc3(exp->rest->rest, symbPtr, table); 
                 }
			/* If operation is subtractio*/
			case '-':
				other = evaluateFunc2(exp->rest, table);
                 if(exp->rest->rest != NULL){ 
                    return other - evaluateFunc3(exp->rest->rest, symbPtr, table); 
                 }
                
            /* If operation is multiplication*/
            default:   
                other = evaluateFunc2(exp->rest, table);
                 if(exp->rest->rest != NULL){ 
                    return other * evaluateFunc3(exp->rest->rest, symbPtr, table); 
                 }
    }

    return other; 

    
}

/*Helper method for evaluating a function*/
int evaluateFunc2(Exp* exp, SymbolTable* table){
    if(exp->first && exp->first->first){
        return evaluateFunc1(exp->first, table);

    }

    if(checkLetter(exp->first->symbol) == 1){
        return evaluationFunc(table, exp->first->symbol);

    }

    return atol(exp->first->symbol);
    
}

/*Helper method for evaluating a function*/
int evaluateFunc3(Exp* exp, char* str, SymbolTable* table){
    if(exp->first && exp->first->first){
        if(exp->rest){
            switch(*(str)) {
			// If operation is mult
			case '*':
				 return evaluateFunc1(exp->first, table) * evaluateFunc3(exp->rest, str, table);

            // if the operation is addition
            default:   
                return evaluateFunc1(exp->first, table) + evaluateFunc3(exp->rest, str, table);
            }

        }
        else{
           return evaluateFunc1(exp->first, table);

        }
    }
    else{
        switch(*(str)) {

			// If operation is addition
			case '+':
            if(exp->rest != NULL){
                    return evaluateFunc2(exp, table) + evaluateFunc3(exp->rest, str, table);
            }

            else{
                return evaluateFunc2(exp, table);
            }

			/* If operation is mult,*/
            default:   
               if(exp->rest != NULL){
                    return evaluateFunc2(exp, table) * evaluateFunc3(exp->rest, str, table);
            }
            else{
                return evaluateFunc2(exp, table);
            }
        }
    }
}

/*Evaluates a method with a subfunction in it*/
int evaluateSubFunc(Exp* e, SymbolTable* table, char* str){
    char* result = evaluateSubFuncHelper(e, str, table);
    Exp* e1 = (Exp*) calloc(1, sizeof(Exp));
    char* nameOf = (char*) calloc(1, sizeof(char));
    e1 = e; 
    printExp(e);
    //|| strcmp(e1->first,"\n") != 0
    while(e1->first != 0 ){
        if(e1->first->symbol){
           // printf("[%s]", e1->first->symbol);
        }
        if(e1->rest->first->symbol){
             //printf("[%s]", e1->rest->first->symbol);
             nameOf = e1->rest->first->symbol;
             break; 
        }
        if(e1->rest->first && e1->rest->first->first){
            e1 = e1->rest->first; 
        }
       
    }

    Exp* subOfE = (Exp*) calloc(1, sizeof(Exp));
    Symbol* s = find(table, nameOf);
    subOfE = s->typeOf;

    Exp* exp = subsetExp2(subOfE, result);

    return evaluateFunc1(exp, table);



}

/* Helper method for evaluateSubFunction Method*/
char* evaluateSubFuncHelper(Exp* e, char* str, SymbolTable* table){
    size_t l = strlen(str);
    char* temp = (char*)malloc((l + 1) * sizeof(char));
    char* r = (char*)malloc((l + 1) * sizeof(char));
    int i;
    int j =0; 
    for(i = 0; i < l; i++) {
     temp[i] = str[l - 1 - i];
        if(temp[i] == 'f' || temp[i] == 'r'){
            r[j] = temp[i];
            j = j+1; 
            r[j] = ' ';
            j++;
         }

    }

    return r; 

}

/* Recursivly returns subset of exp according to string at p. */
Exp* subsetExpRec2(Exp* exp) {

	// If the current char is a space, recursivly return subset at next char.
	if(*ptr == ' ') {
		ptr++;
		return subsetExpRec2(exp);
	}

	// If the current char is 'r', recursivly return subset from rest at next char.
	if(*ptr == 'r') {
		ptr++;
		return subsetExpRec2(exp->rest);
	}

	// If the current char is 'r', recursivly return subset from first at next char.
	if(*ptr == 'f') {
		ptr++;
		return subsetExpRec2(exp->first);
	}

	// If string is empty, return exp.
	return exp;

}


/* Returns subset of exp according to string at input. */
Exp* subsetExp2(Exp* exp, char* input) {
	ptr = input;
	return subsetExpRec2(exp);

}




