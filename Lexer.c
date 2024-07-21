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


token* lex(char* input){
    token *tokensHead=NULL;
    token *currentToken=NULL;
    int tokenCount=0;

    while (*input !='\0'){
        if((*input)==' '){
               input++;           
               continue;
        }

        token *newToken=malloc(sizeof(token));
      
        //~~~Numerals~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if (isdigit(*input) || (*input)=='.'){
            //recognize a number
            char* start= input;
            while (isdigit(*input)||(*input)=='.'){
                input++;
            }
            char *end=input;
            newToken->text= (char*)malloc((end - start +1)*sizeof(char));
            strncpy (newToken->text, start, end-start);
            newToken->text[end-start]='\0';    //Null terminate the string
            newToken->type=TOKEN_NUMBER;
        }

        //~~~Elementary Functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if (isalpha(*input) && (*input)!='x'){
            char *start=input;
            while(isalpha(*input)&&(*input)!='x')
                input++;
            char *end=input;
            newToken->text= (char*)malloc((end - start +1)*sizeof(char));
            strncpy( newToken->text, start, end-start);
            newToken->text[end-start]='\0';
            newToken->type=TOKEN_FUNCTION;
        }
        
        //~~~Variable 'x'~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if((*input)== 'x'){
            newToken->text=(char*)malloc(2*sizeof(char));
            newToken->text[0]='x';
            newToken->text[1]='\0';
            newToken->type=TOKEN_VARIABLE;
            input++;
        }

        //~~~Operators~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if ((*input)=='+' ||(*input)=='-' ||(*input)=='*' ||(*input)=='/' ||(*input)=='^'){
            newToken->text=(char*)malloc(2*sizeof(char));
            newToken->text[0]=*input;
            newToken->text[1]='\0';
            newToken->type=TOKEN_OPERATOR;
            input++;
        }

        //~~~Parantheses~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        else if((*input)=='(' || (*input)==')'){
            newToken->text=(char*)malloc(2*sizeof(char));
            newToken->text[0]=*input;
            newToken->text[1]='\0';
            newToken->type=TOKEN_PARENTHESES;
            input++;
        }


        else{
            printf("MALFORMED EXPRESSION");
            exit(EXIT_FAILURE);
        }


        newToken->nextToken=NULL;
        if(currentToken){
            currentToken->nextToken=newToken;
            currentToken=newToken;
        }
        else{
            tokensHead=newToken;
            currentToken=newToken;
        }
        tokenCount++;
    }
    return tokensHead;
}

    //~~Free allocated memory~~~~~~~~~~~~~~~~~
    
/*void freeTokens(token *tokensHead){
    token *currentToken = tokensHead;
    while(currentToken!=NULL){
        token *next=currentToken->nextToken;
        free(currentToken->text);
        free(currentToken);
        currentToken =next;
    } 
}*/



