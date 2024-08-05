#include "Lexer.h"
#include "postfixParser.h"
#include "rpnArrayEval.h"
#include <stdio.h>
#include <string.h>

int main(){
    char input[]="sin(x)+34*x^2-32/ln(x)";
    printf("%s\n",input);
    Stack* tokenized=lex(input);
    for(int i=0; i<=tokenized->top; i++)
        printf("Token: %s, type: %d\n",tokenized->stack[i].text,tokenized->stack[i].type);

    printf("tokenized top:%d\ntokenized stackSize:%d\n",tokenized->top,tokenized->stackSize);
    printf("\n\n");
    Stack *postfixArray=parser(tokenized);
    for(int i=0; i<=postfixArray->top;i++)
        printf("%s\n",postfixArray->stack[i].text);
 
    double val=eval(postfixArray,5.0);
    printf("%lf",val);

    return(0);
}
