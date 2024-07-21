#include "postfixParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*~~~~~~~~~~~~~~~~~~~~~~~~Push~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *Function to push a token onto the opStack */
void push(Stack *Stack, token *Token){
    Stack->stack=(token*)realloc(Stack->stack, sizeof(token)*(Stack->stackSize+1));
    if(Stack->stack==NULL){
        fprintf(stderr, "Memory reallocation while pushing failed\n");
        free(Stack->stack);
        return;
    }
    Stack->stackSize=(Stack->stackSize)+1;
    Stack->top=Stack->stackSize-1;
    Stack->stack[Stack->top]=*Token;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Pop~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Function to Pop a token and store in a variable of type token.If the popped element is to 
 * be used the pPopped pointer can be used. A pointer has been used only because the defined
 * push function accepts pointer to type token for pushing the token */

token popped;
token *pPopped=NULL;
void pop(Stack *Stack){
    if(Stack->stackSize==1){
        fprintf(stderr,"Stack Underflow\n");
        return;
    }
    Stack->top=Stack->stackSize-1;
    popped=Stack->stack[Stack->top];
    Stack->stack=realloc(Stack->stack, sizeof(token)*(--(Stack->stackSize)));
    if(Stack->stack==NULL && Stack->stackSize>0){
        fprintf(stderr, "Memory reallocation while popping failed\n");
        free(Stack->stack);
        return;
    }
    Stack->top=Stack->stackSize-1;
    pPopped=&(popped);
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


//tokensHead is to be passed into this function in the main program
Stack *parser(token *currentToken){

    /*~~~~~~~~~~~~~~~~~~~~~~~Operator Stack Definition~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    * The operator stack is an "array" of type "token" variables and can be accessed by the
    * "opStack"  pointer */

    Stack *opStack=(Stack*)malloc(sizeof(Stack));
    if(opStack==NULL){
        fprintf(stderr,"Memory allocation for opStack failed");
        return NULL;
    }

    opStack->stack=(token*)malloc(sizeof(token));
    if(opStack->stack==NULL){
        fprintf(stderr,"Memory allocation for opStack->stack failed");
        free(opStack);
        return NULL;
    }
    opStack->stackSize=1;
    opStack->top=0;
    opStack->stack->text="\0";


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

    postfixArray->stack=(token*)malloc(sizeof(token));
    if(postfixArray->stack==NULL){
        fprintf(stderr,"Memory allocation for postfixArray->stack failed");
        free(opStack->stack);
        free(opStack);
        free(postfixArray);
        return NULL;
    }
    postfixArray->stackSize=1;
    postfixArray->top=0;
    postfixArray->stack->text=NULL;

    
    /*~~~~~~~~~~~~~~~~~~~~~~ Shunting Yard Algorithm~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    while(currentToken !=NULL){
        if (currentToken->type == TOKEN_NUMBER ||currentToken->type == TOKEN_VARIABLE){
            push(postfixArray, currentToken);
        }

        else if(currentToken->type == TOKEN_FUNCTION){
            push(opStack, currentToken);
        }

        else if(currentToken->type == TOKEN_OPERATOR){
            //This while loop is to pop elemnts from the opStack
            while(strcmp(opStack->stack[opStack->top].text,"(")!=0 && (P(opStack->stack[opStack->top])>P(*currentToken) ||(P(opStack->stack[opStack->top])==P(*currentToken)))){
            
                pop(opStack);
                push(postfixArray,pPopped);
            }
            push(opStack, currentToken);
        }

        else if(strcmp(currentToken->text,"(")==0){
            push(opStack, currentToken);
        }

        else if(strcmp(currentToken->text,")")==0){
            while(opStack->stack[opStack->top].text!=NULL && strcmp(opStack->stack[opStack->top].text,"(")!=0){
                pop(opStack);
                push(postfixArray, pPopped);
            }
            if(strcmp(opStack->stack[opStack->top].text,"(")==0)
                pop(opStack);
            if(opStack->stack[opStack->top].type==TOKEN_FUNCTION){
                pop(opStack);
                push(postfixArray, pPopped);
            }
        }
        currentToken=currentToken->nextToken;
    }

    while(opStack->stackSize>1){
        pop(opStack);
        push(postfixArray, pPopped);
    }

    free(opStack->stack);
    free(opStack);
    return(postfixArray);
}    
