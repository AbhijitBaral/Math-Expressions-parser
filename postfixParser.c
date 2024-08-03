
#include "postfixParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*~~~~~~~~~~~~~~~~~~~~~~~~Push~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *Function to push a token onto the opStack */
void push(Stack *Stack, token Token){
    if(Stack->top<=Stack->stackSize){
        Stack->top+=1;
        Stack->stack[Stack->top].text=(char*)malloc((strlen(Token.text)+1)*sizeof(char));
        strcpy(Stack->stack[Stack->top].text,Token.text);
        Stack->stack[Stack->top].type=Token.type;
        }
    else{
        printf("Stack overflow");
        exit(1);
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Pop~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Function to Pop a token and store in a variable of type token.If the popped element is to
 * be used the pPopped pointer can be used. A pointer has been used only because the defined
 * push function accepts pointer to type token for pushing the token */

token popped;
void pop(Stack *Stack){
    if(Stack->top>=0){
        free(popped.text);
        popped.text=malloc((strlen(Stack->stack[Stack->top].text)+1)*sizeof(char));
        strcpy(popped.text,Stack->stack[Stack->top].text);
        popped.type=Stack->stack[Stack->top].type;
        free(Stack->stack[Stack->top].text);
        Stack->stack[Stack->top].text=NULL;
        Stack->top-=1;
    }
    else{
        printf("Stack underflow");
        exit(1);
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

//tokensHead is to be passed into this function in the main program
Stack *parser(Stack *tokenized){
    popped.type=0;
    popped.text=(char*)calloc(1,sizeof(char));

    /*~~~~~~~~~~~~~~~~~~~~~~~Operator Stack Definition~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    * The operator stack is an "array" of type "token" variables and can be accessed by the
    * "opStack"  pointer */

    Stack *opStack=(Stack*)malloc(sizeof(Stack));
    if(opStack==NULL){
        fprintf(stderr,"Memory allocation for opStack failed");
        return NULL;
    }
    memset(opStack,0,sizeof(Stack));

    opStack->stack=(token*)malloc(50*sizeof(token));
    if(opStack->stack==NULL){
        fprintf(stderr,"Memory allocation for opStack->stack failed");
        free(opStack);
        return NULL;
    }
    memset(opStack->stack,0,50*sizeof(token));
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
    while(i<=tokenized->top){
        if (tokenized->stack[i].type == TOKEN_NUMBER ||tokenized->stack[i].type == TOKEN_VARIABLE){
            push(postfixArray, tokenized->stack[i]);
        }

        else if(tokenized->stack[i].type == TOKEN_FUNCTION){
            push(opStack, tokenized->stack[i]);
        }

        else if(tokenized->stack[i].type == TOKEN_OPERATOR){
            if(opStack->top==-1)
                push(opStack,tokenized->stack[i]);
            else{
                //This while loop is to pop elemnts from the opStack
                while(opStack->top>=0 && strcmp(opStack->stack[opStack->top].text,"(")!=0 && P(opStack->stack[opStack->top])>=P(tokenized->stack[i])){
                    pop(opStack);
                    push(postfixArray, popped);
                }
                push(opStack, tokenized->stack[i]);
            }
        }

        else if(strcmp(tokenized->stack[i].text,"(")==0){
            push(opStack, tokenized->stack[i]);
        }

        else if(strcmp(tokenized->stack[i].text,")")==0){
            while(/*opStack->stack[opStack->top].text!=NULL*/opStack->top!=-1 && strcmp(opStack->stack[opStack->top].text,"(")!=0){
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

    if(popped.text!=NULL)
        free(popped.text);

    //Freeing the tokenized array
    freeStack(tokenized);

    //Freeing opStack
    freeStack(opStack);

    return(postfixArray);
}    

