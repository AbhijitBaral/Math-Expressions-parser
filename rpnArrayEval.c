#include "postfixParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* User entered value of x, the expression is to be evaluated at. */
double x0;
double val;

double rpnArrayEval(Stack *postfixArray){
    
    rpnArr *Arr=(rpnArr*)malloc(sizeof(rpnArr));
    if(Arr==NULL){
        fprintf(stderr,"memory allocation for struct rpnArr failed");
        return 1;
    }
    
    Arr->rpnArr=(Token*)malloc(30*sizeof(Token));
    if(Arr->rpnArr==NULL){
        fprintf(stderr, "Memory allocation failed for the evalToken Array");
        return 1;
    }
    
    //Accepted from the parser function
    //To be written in the main file: double rpnArrayEval(parser(tokensHead));
    for(int i=1;i<=postfixArray->top;i++){
        Arr->rpnArr[i-1].tmain=postfixArray->stack[i];
        if(postfixArray->stack[i].type==TOKEN_NUMBER)
            Arr->rpnArr[i-1].num=atof(postfixArray->stack[i].text);
    
        else if(postfixArray->stack[i].type==TOKEN_VARIABLE)
            Arr->rpnArr[i-1].num=x0;
    
        else
            Arr->rpnArr[i-1].num=NULL;
        Arr->top=postfixArray->top-1;
    }
    
    stackAB StackAB;
    StackAB.stackA=(rpnArr*)malloc(sizeof(rpnArr));
    StackAB.stackA->rpnArr=(evalToken*)malloc((Arr->top)*sizeof(evalToken));
    StackAB.stackB=(rpnArr*)malloc(sizeof(rpnArr));
    stackAB.stackB->rpnArr=(evalToken*)malloc((Arr->top)*sizeof(evalToken));

    stackAB.stackB->top=-1;
    stackAB.stackA=*Arr;
    stackAB.sel=1;
    free(Arr);
    rpnArr *temp=stackAB.stackB;
    while(stackAB.stackA->top!=0 || stackAB.stackB->top!=0){
            for(int c1=2,c2=1; stackAB.stackA->top>=2 && c2<=stackAB.stackA->top ;c1++,c2++){
                if(stackAB.stackA->rpnArr[c1].num==NULL && stackAB.stackA->rpnArr[c2-1].num!=NULL && stackAB.stackA->rpnArr[c2-2].num!=NULL){


                    stackAB.stackB->rpnArr[++stackAB.stackB->top].num= "The three elements evaluated";
                    stackAB.stackB->rpnArr[stackAB.stackB->top].tmain.type=TOKEN_NUMERAL;
                }

                else if(stackAB.stackA->rpnArr[c1].tmain.type==TOKEN_FUNCTION && stackAB.stackA->rpnArr[c1-1].num!=NULL){

                    stackAB.stackB->rpnArr[++stackAB.stackB->top].num="Two elements evaluated";
                    stackAB.stackB->rpnArr[stackAB.stackB->top].tmain.type=TOKEN_NUMERAL;
                }

                else{
                    stackAB.stackB->rpnArr[++stackAB.stackB->top]=stackAB.stackA->rpnArr[c1-1];
                }
            }
            temp=stackAB.stackB;
            stackAB.stackB=stackAB.stackA;
            stackAB.stackA=temp;
    }


