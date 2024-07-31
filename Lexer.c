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


void freeTokens(char *input ,token *tokenized){
    int n=0;
    while(n<=strlen(input)){
        free(tokenized[n].text);
        n++;
    }
    free(tokenized);
}


token* lex(char* input){

    token *tokenized=calloc(50,sizeof(token));
    if(tokenized==NULL){
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
            tokenized[i].text=(char*)malloc((end - start +1)*sizeof(char));
            strncpy (tokenized[i].text, start, end-start);
            tokenized[i].text[end-start]='\0';    //Null terminate the string
            tokenized[i].type=TOKEN_NUMBER;
        }

        //~~~Elementary Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (isalpha(*input) && (*input)!='x'){
            char *start=input;
            while(isalpha(*input)&&(*input)!='x')
                input++;
            char *end=input;
            tokenized[i].text=(char*)malloc((end - start +1)*sizeof(char));
            strncpy( tokenized[i].text, start, end-start);
            tokenized[i].text[end-start]='\0';
            tokenized[i].type=TOKEN_FUNCTION;
            input++;
        }
        
        //~~~Variable 'x'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if((*input)== 'x'){
            tokenized[i].text=(char*)malloc(2*sizeof(char));
            tokenized[i].text[0]='x';
            tokenized[i].text[1]='\0';
            tokenized[i].type=TOKEN_VARIABLE;
            input++;
        }

        //~~~Operators~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if ((*input)=='+' ||(*input)=='-' ||(*input)=='*' ||(*input)=='/' ||(*input)=='^'){
            tokenized[i].text=(char*)malloc(2*sizeof(char));
            tokenized[i].text[0]=*input;
            tokenized[i].text[1]='\0';
            tokenized[i].type=TOKEN_OPERATOR;
            input++;
        }

        //~~~Parantheses~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if((*input)=='(' || (*input)==')'){
            tokenized[i].text=(char*)malloc(2*sizeof(char));
            tokenized[i].text[0]=*input;
            tokenized[i].text[1]='\0';
            tokenized[i].type=TOKEN_PARENTHESES;
            input++;
        }

        else{
            printf("MALFORMED EXPRESSION");
            exit(EXIT_FAILURE);
        }
        
        i++;
    }
    //tokenized=realloc(tokenized,(--i)*sizeof(token));
    return tokenized;
}
