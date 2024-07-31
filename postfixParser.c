
#include "postfixParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~Function to free a stack~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void freeStack(Stack *Stack){
    for(int n=0;n<=Stack->top; n++){
        free(Stack->stack[n].text);
        Stack->stack[n].text=NULL;
    }
    free(Stack->stack);
    free(Stack);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~Push~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *Function to push a token onto the opStack */
void push(Stack *Stack, token Token){
    Stack->stack[++Stack->top].text=(char*)malloc((strlen(Token.text)+1)*sizeof(char));
    strcpy(Stack->stack[Stack->top].text,Token.text);
    Stack->stack[Stack->top].type=Token.type;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Pop~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Function to Pop a token and store in a variable of type token.If the popped element is to 
 * be used the pPopped pointer can be used. A pointer has been used only because the defined
 * push function accepts pointer to type token for pushing the token */

token popped;
void pop(Stack *Stack){
    if(Stack->top>=0){
        popped.text=malloc((strlen(Stack->stack[Stack->top].text)+1)*sizeof(char));
        strcpy(popped.text,Stack->stack[Stack->top].text);
        popped.type=Stack->stack[Stack->top].type;
        free(Stack->stack[Stack->top].text);
        Stack->stack[Stack->top--].text=NULL;
    }
}

/*~~~~~~~~~~~~~~~Precedence mapper~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Function that maps a numerical precedence value to operators based on their precedence*/
int P(token Token){
    if (strcmp(Token.text, "(") == 0) return 6;
    if (strcmp(Token.text, ")") == 0) return 5;
    if (strcmp(Token.text, "^") == 0) return 4;
    if (strcmp(Token.text, "/") == 0) return 3;
    if (strcmp(Token.text, "*") == 0) return 2;
    if (strcmp(Token.text, "+") == 0) return 1;
    if (strcmp(Token.text, "-") == 0) return 1;
    return -1;
}

token *currentToken=NULL;
//tokensHead is to be passed into this function in the main program
Stack *parser(token *tokenized, char *input){

    /*~~~~~~~~~~~~~~~~~~~~~~~Operator Stack Definition~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    * The operator stack is an "array" of type "token" variables and can be accessed by the
    * "opStack"  pointer */

    Stack *opStack=(Stack*)malloc(sizeof(Stack));
    if(opStack==NULL){
        fprintf(stderr,"Memory allocation for opStack failed");
        return NULL;
    }
    memset(opStack,0,sizeof(Stack));

    opStack->stack=(token*)calloc(50,sizeof(token));
    if(opStack->stack==NULL){
        fprintf(stderr,"Memory allocation for opStack->stack failed");
        free(opStack);
        return NULL;
    }
    opStack->stackSize=50;
    opStack->top=-1;


    /*~~~~~~~~~~~~~~~~~~~~~~~Postfix Array Definition~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    * This is the output dynamic array which would represent the expression structure in postfix
    *form and can be accessed by the "postfixArray" pointer */

    Stack *postfixArray=(Stack*)malloc(sizeof(Stack));
    if(postfixArray==NULL){
        free(opStack);
        free(postfixArray);
        fprintf(stderr,"memory allocation for postfixArray failed");
        return NULL;
    }
    memset(postfixArray,0,sizeof(Stack));

    postfixArray->stack=(token*)calloc(50,sizeof(token));
    if(postfixArray->stack==NULL){
        fprintf(stderr,"Memory allocation for postfixArray->stack failed");
        free(opStack->stack);
        free(opStack);
        free(postfixArray);
        return NULL;
    }
    postfixArray->stackSize=50;
    postfixArray->top=-1;

    
    /*~~~~~~~~~~~~~~~~~~~~~~ Shunting Yard Algorithm~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    int i=0;
    while(i != strlen(input)){
        if (tokenized[i].type == TOKEN_NUMBER ||tokenized[i].type == TOKEN_VARIABLE){
            push(postfixArray, tokenized[i]);
        }

        else if(tokenized[i].type == TOKEN_FUNCTION){
            push(opStack, tokenized[i]);
        }

        else if(tokenized[i].type == TOKEN_OPERATOR){
            //This while loop is to pop elemnts from the opStack
            while(strcmp(opStack->stack[opStack->top].text,"(")!=0 && (P(opStack->stack[opStack->top])>P(*currentToken) ||(P(opStack->stack[opStack->top])==P(tokenized[i])))){
            
                pop(opStack);
                push(postfixArray, popped);
            }
            push(opStack, tokenized[i]);
        }

        else if(strcmp(tokenized[i].text,"(")==0){
            push(opStack, tokenized[i]);
        }

        else if(strcmp(tokenized[i].text,")")==0){
            while(opStack->stack[opStack->top].text!=NULL && strcmp(opStack->stack[opStack->top].text,"(")!=0){
                pop(opStack);
                push(postfixArray, popped);
            }
            if(strcmp(opStack->stack[opStack->top].text,"(")==0)
                pop(opStack);
            if(opStack->stack[opStack->top].type==TOKEN_FUNCTION){
                pop(opStack);
                push(postfixArray, popped);
            }
        }
        i=i+1;
    }

    while(opStack->top>=0){
        pop(opStack);
        push(postfixArray, popped);
    }

    //Freeing the array of tokens
    freeTokens(input,tokenized);

    //Freeing opStack
    free(opStack->stack);
    free(opStack);

    return(postfixArray);
}    

