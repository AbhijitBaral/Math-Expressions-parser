#include "Lexer.h"
#include "postfixParser.h"
#include "rpnArrayEval.h"
#include <stdio.h>
#include <string.h>

int main(){
    char input[]="((arccosec(0.33 * x))/ln(4.60 * x)-arccosec(6.44 * x))/arccosec(3.86 * x)";
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
