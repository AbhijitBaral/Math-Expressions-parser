#include "postfixParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* User entered value of x, the expression is to be evaluated at. */
double x0;
double val;

double rpnArrayEval(Stack *postfixArray){
    

    rpnArr *stackA=(rpnArr*)malloc(sizeof(rpnArr));
    if(stackA==NULL){
        fprintf(stderr,"memory allocation for stackA failed");
        return 1;
    } 
    stackA->rpnArr=(evalToken*)malloc(30*sizeof(evalToken));
    if(stackA->rpnArr==NULL){
        fprintf(stderr, "Memory allocation failed for the stackA->rpnArr");
        return 1;
    }
    

    //Accepted from the parser function
    //To be written in the main file: double rpnArrayEval(parser(tokensHead));
    for(int i=1;i<=postfixArray->top;i++){
        stackA->rpnArr[i-1].tmain=postfixArray->stack[i];
        if(postfixArray->stack[i].type==TOKEN_NUMBER)
            stackA->rpnArr[i-1].num=atof(postfixArray->stack[i].text);
    
        else if(postfixArray->stack[i].type==TOKEN_VARIABLE)
            stackA->rpnArr[i-1].num=x0;
    
        else
            stackA->rpnArr[i-1].num=NULL;
        stackA->top=postfixArray->top-1;
    }
    free(postfixArray);
   

    rpnArr *stackB=(rpnArr*)malloc(sizeof(rpnArr));
    if(stackA==NULL){
        fprintf(stderr,"Memory allocation failed for stackB");
        return 1;
    }
    stackB->rpnArr=(evalToken*)malloc(30*sizeof(evalToken));
    if(stackB->rpnArr==NULL){
        fprintf(stderr,"Memory allocation for stackB->rpnArr failed");
        return 1;
    }
    stackB->top=-1;
    rpnArr *temp=stackB;
    
    int stackSize;

    int c1=1,c2=2;
    while(stackA->top!=0 || stackB->top!=0){
        while(stackA->top>=2 && c2<=stackA->top){
                if(stackA->rpnArr[c2].tmain.type==TOKEN_OPERATOR && stackA->rpnArr[c2-1].num!=NULL && stackA->rpnArr[c2-2].num!=NULL){
                    stackB->rpnArr[++stackB->top].num= "The three elements evaluated";
                    stackB->rpnArr[stackB->top].tmain.type=TOKEN_NUMERAL;
                    if(c2+2==stackA->top){
                        stackB->rpnArr[++stackB->top]=stackA->rpnArr[stack->top];
                        break;
                    }
                    if(c2+1==stackA->top){
                        stackB->rpnArr[++stackB->top]=stackA->rpnArr[stackA->top];
                        break;
                    }
                    c1+=3;c2+=c2;
                }

                else if(stackA->rpnArr[c1].tmain.type==TOKEN_FUNCTION && stackA->rpnArr[c1-1].num!=NULL){

                    stackB->rpnArr[++stackB->top].num="Two elements evaluated";
                    stackB->rpnArr[stackB->top].tmain.type=TOKEN_NUMERAL;
                    if(c2+1==stackA->top){
                        stackB->rpnArr[++stackB->top]=stackA->rpnArr[stackA->top];
                        break;
                    }
                    c1+=1; c2+=2;
                }

                else{
                    stackB->rpnArr[++stackB->top]=stackA->rpnArr[c1-1];
                    c1++;c2++;
                }
        }
           
            stackSize=stackA->top+1;
            free(stackA->rpnArr);
            free(stackA);
            rpnArr *stackA=(rpnArr*)malloc(sizeof(rpnArr));
            stackA->top=stackSize-1;
            if(stackA==NULL){
                fprintf(stderr,"memory allocation for stackA failed");
                return 1;
            }
            stackA->rpnArr=(evalToken*)malloc(stackSize*sizeof(evalToken));
            if(stackA->rpnArr==NULL){
                fprintf(stderr, "Memory allocation failed for the stackA->rpnArr");
                return 1;
            }

            temp=stackB;
            stackB=stackA;
            stackA=temp;
            c1=1;c2=2;
    }
}


