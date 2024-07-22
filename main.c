#include "Lexer.h"
#include "postfixParser.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    //print the tokens generated by the user
    char input[]="log(x + sin(x) * cos(x)) / exp(tan(x))";
    token *tokensHead=lex(input);

    token *currentToken = tokensHead;
    printf("String: %s\n",input);
    while(currentToken!=NULL){
        printf("Token: %s, Type: %d\n",currentToken->text, currentToken->type);
        currentToken=currentToken->nextToken;
    }

    //Call parser and print the postfix Array
    Stack *postfixArray=parser(tokensHead);
    printf("\nPostfix:\n");

    for(int i=1;i<=postfixArray->top;i++)
        printf("%s\n",postfixArray->stack[i].text);
    return(0);
}





