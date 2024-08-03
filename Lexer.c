/*This code is intended to perform lexical analysis. A lexer converts a sequence of characters like a 
 * mathematical expression composed of variables, operators, functions, etc and converts it to a sequ
 * -ence of tokens. Tokens are meaningful character sequences.
 * The recognized tokens here are ;
 *          + Decimal Numbers
 *          + Elementary functions
 *          + Variable 'x'
 *          + Operators
 *          + Parantheses  */

#include "Lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*~~~~~~~~~~~~~~~~~~~~~~~~Function to free a stack~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void freeStack(Stack *Stack){
    for(int n=0;n<=Stack->top; n++){
        free(Stack->stack[n].text);
        Stack->stack[n].text=NULL;
    }
    free(Stack->stack);
    free(Stack);
}


Stack* lex(char* input){

    Stack *tokenized=(Stack*)malloc(sizeof(Stack));
    if(tokenized==NULL){
        printf("Memory allocation for tokenized array failed");
        exit(1);
    }
    memset(tokenized,0,sizeof(Stack));
    tokenized->stack=calloc(50,sizeof(token));
    if(tokenized->stack==NULL){
        printf("Memory allocation for tokenized array falied");
        exit(1);
    }
    int i=0;
    while (*input !='\0'){
        if((*input)==' '){
               input++;           
               continue;
        }

        //~~~Numerals~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if (isdigit(*input) || (*input)=='.'){
            //recognize a number
            char* start= input;
            while (isdigit(*input)||(*input)=='.'){
                input++;
            }
            char *end=input;
            tokenized->stack[i].text=(char*)malloc((end - start +1)*sizeof(char));
            strncpy (tokenized->stack[i].text, start, end-start);
            tokenized->stack[i].text[end-start]='\0';    //Null terminate the string
            tokenized->stack[i].type=TOKEN_NUMBER;
        }

        //~~~Elementary Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (isalpha(*input) && (*input)!='x'){
            char *start=input;
            while(isalpha(*input)&&(*input)!='x')
                input++;
            char *end=input;
            tokenized->stack[i].text=(char*)malloc((end - start +1)*sizeof(char));
            strncpy( tokenized->stack[i].text, start, end-start);
            tokenized->stack[i].text[end-start]='\0';
            tokenized->stack[i].type=TOKEN_FUNCTION;
            //input++;
        }
        
        //~~~Variable 'x'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if((*input)== 'x'){
            tokenized->stack[i].text=(char*)malloc(2*sizeof(char));
            tokenized->stack[i].text[0]='x';
            tokenized->stack[i].text[1]='\0';
            tokenized->stack[i].type=TOKEN_VARIABLE;
            input++;
        }

        //~~~Operators~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if ((*input)=='+' ||(*input)=='-' ||(*input)=='*' ||(*input)=='/' ||(*input)=='^'){
            tokenized->stack[i].text=(char*)malloc(2*sizeof(char));
            tokenized->stack[i].text[0]=*input;
            tokenized->stack[i].text[1]='\0';
            tokenized->stack[i].type=TOKEN_OPERATOR;
            input++;
        }

        //~~~Parantheses~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if((*input)=='(' || (*input)==')'){
            tokenized->stack[i].text=(char*)malloc(2*sizeof(char));
            tokenized->stack[i].text[0]=*input;
            tokenized->stack[i].text[1]='\0';
            tokenized->stack[i].type=TOKEN_PARENTHESES;
            input++;
        }

        else{
            printf("MALFORMED EXPRESSION");
            exit(EXIT_FAILURE);
        }
        
        i++;
        tokenized->top=i-1;
    }
    tokenized->stack=realloc(tokenized->stack,(tokenized->top+1)*sizeof(token));
    tokenized->stackSize=tokenized->top+1;
    return tokenized;
}
