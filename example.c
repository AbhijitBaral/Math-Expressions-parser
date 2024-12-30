#include "rpnArrayEval.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
    char input[]="(tan(5.76 * x)-ln(9.17 * x))";
    Stack *tokenized=lex(input);
    Stack *postfixArray=parser(tokenized);
    
    double v,val;
    printf("Enter the decimal number, the expression is to be evaluated at>");
    scanf("%lf",&v);
    val=eval(postfixArray,v);
    printf("\nThe value of the entered expression at %lf is %lf\n",v,val);
    return(0);
}
