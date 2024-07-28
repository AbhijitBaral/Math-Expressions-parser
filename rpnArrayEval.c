#include "rpnArrayEval.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define pi 3.14156

int stackSize,c1=1,c2=2;
rpnArr *stackA;
rpnArr *stackB;
double val=0.0;

void freeStack(rpnArr *stack){
    for(int i=0; i<=49; i++)
        free(stack->rpnArr[i].tmain.text);
    free(stack->rpnArr);
    free(stack);
}


double calc(int c1, int c2){
    if(c1==-1){
        if(strcmp(stackA->rpnArr[c2].tmain.text,"+")==0)
            return(stackA->rpnArr[c2-2].num+stackA->rpnArr[c2-1].num);

        else if(strcmp(stackA->rpnArr[c2].tmain.text,"-")==0)
            return(stackA->rpnArr[c2-2].num-stackA->rpnArr[c2-1].num);

        else if(strcmp(stackA->rpnArr[c2].tmain.text,"*")==0)
            return(stackA->rpnArr[c2-2].num*stackA->rpnArr[c2-1].num);

        else if(strcmp(stackA->rpnArr[c2].tmain.text,"/")==0)
            return(stackA->rpnArr[c2-2].num/stackA->rpnArr[c2-1].num);

        else if(strcmp(stackA->rpnArr[c2].tmain.text,"^")==0)
            return(pow(stackA->rpnArr[c2-2].num,stackA->rpnArr[c2-1].num));
    }

    else if(c2==-1){
        if(strcmp(stackA->rpnArr[c1].tmain.text,"sin")==0 )
            return(sin(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"cos")==0 )
            return(cos(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"tan")==0 )
            return(tan(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"cot")==0 )
            return(1.0/tan(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"cosec")==0 )
            return(1.0/sin(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"sec")==0 )
            return(1.0/cos(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"arcsin")==0 )
            return(asin(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"arccos")==0 )
            return(acos(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"arctan")==0 )
            return(atan(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"arccot")==0 )
            return((pi/2.0)-atan(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"arcsec")==0 )
            return(acos(1.0/(stackA->rpnArr[c1-1].num)));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"arccosec")==0 )
            return(asin(1.0/(stackA->rpnArr[c1-1].num)));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"ln")==0 )
            return(log(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"log")==0 )
            return(log10(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"fact")==0 ){
            if((stackA->rpnArr[c1-1].num-(int)stackA->rpnArr[c1-1].num)!=0.0){
                    printf("Arguement to fact function has to be an integer");
                    exit(0);
            }
            return(tgamma(stackA->rpnArr[c1-1].num+1));
        }

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"gamma")==0 )
            return(tgamma(stackA->rpnArr[c1-1].num));

        else if(strcmp(stackA->rpnArr[c1].tmain.text,"erf")==0 )
            return(erf(stackA->rpnArr[c1-1].num));

        else{
            printf("Unidentified function: %s",stackA->rpnArr[c1].tmain.text);
            exit(1);
        }
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~rpnEval function~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

double eval(Stack *postfixArray,double x0){
/*~~~~~~~~~~~~~~~~~~stack definitions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    stackA=(rpnArr*)malloc(sizeof(rpnArr));
    if(stackA==NULL){
        fprintf(stderr,"memory allocation for stackA failed");
        exit(1);
    }
    memset(stackA,0,sizeof(rpnArr));
    stackA->top=postfixArray->top-1;
    stackA->rpnArr=malloc(50*sizeof(evalToken));
    if(stackA->rpnArr==NULL){
        fprintf(stderr, "Memory allocation failed for the stackA->rpnArr");
        exit(1);
    }
    memset(stackA->rpnArr,0,50*sizeof(evalToken));
    

    stackB=(rpnArr*)malloc(sizeof(rpnArr));
    if(stackA==NULL){
        fprintf(stderr,"Memory allocation failed for stackB");
        return 1;
    }
    memset(stackB,0,sizeof(rpnArr));
    stackB->top=-1;
    stackB->rpnArr=malloc(50*sizeof(evalToken));
    if(stackB->rpnArr==NULL){
        fprintf(stderr,"Memory allocation for stackB->rpnArr failed");
        exit(1);
    }
    memset(stackB->rpnArr,0,50*sizeof(evalToken));
    rpnArr *temp=stackB;


    //Accepted from the parser function
    //To be written in the main file: double rpnArrayEval(parser(tokensHead));
    for(int i=1;i<=postfixArray->top;i++){
        stackA->rpnArr[i-1].tmain=postfixArray->stack[i];
        if(postfixArray->stack[i].type==TOKEN_NUMBER)
            stackA->rpnArr[i-1].num=atof(postfixArray->stack[i].text);
    
        else if(postfixArray->stack[i].type==TOKEN_VARIABLE)
            stackA->rpnArr[i-1].num=x0;

    }
    free(postfixArray->stack);
    free(postfixArray);

    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~postfix evaluation~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    while(stackA->top!=0 && stackB->top!=0){
        if(stackA->top==1 && stackA->rpnArr[1].tmain.type==TOKEN_FUNCTION && (stackA->rpnArr[0].tmain.type==TOKEN_NUMBER || stackA->rpnArr[0].tmain.type==TOKEN_VARIABLE))
            return(calc(1,-1));

        while(stackA->top>=2 && c2<=stackA->top){
                /*~~~~~~~~~~~~~~~~~~~~~~~~subArr:|oprnd|oprnd|operator|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                if(stackA->rpnArr[c2].tmain.type==TOKEN_OPERATOR && (stackA->rpnArr[c2-1].tmain.type==TOKEN_NUMBER || stackA->rpnArr[c2-1].tmain.type==TOKEN_VARIABLE) && (stackA->rpnArr[c2-2].tmain.type==TOKEN_NUMBER || stackA->rpnArr[c2-2].tmain.type==TOKEN_VARIABLE)) {
                    stackB->rpnArr[++(stackB->top)].num=calc(-1,c2);
                    stackB->rpnArr[stackB->top].tmain.type=TOKEN_NUMBER;
                    printf("stackB: %lf, top: %d\n",stackB->rpnArr[stackB->top].num,stackB->top);
                    if(c2+2==stackA->top){
                        if(stackA->rpnArr[stackA->top].tmain.type==TOKEN_FUNCTION && (stackA->rpnArr[stackA->top-1].tmain.type==TOKEN_NUMBER || stackA->rpnArr[stackA->top-1].tmain.type==TOKEN_VARIABLE)){
                            stackB->rpnArr[++(stackB->top)].num=calc(stackA->top,-1);
                    printf("stackB: %lf, top: %d\n",stackB->rpnArr[stackB->top].num,stackB->top);
                            break;
                        }
                    
                        else{
                            stackB->rpnArr[++(stackB->top)]=stackA->rpnArr[stackA->top-1];
                    printf("stackB: %s, top: %d\n",stackB->rpnArr[stackB->top].tmain.text,stackB->top);
                            stackB->rpnArr[++(stackB->top)]=stackA->rpnArr[stackA->top];
                    printf("stackB: %s, top: %d\n",stackB->rpnArr[stackB->top].tmain.text,stackB->top);
                            break;
                        }
                    }
                    if(c2+1==stackA->top){
                        stackB->rpnArr[++(stackB->top)]=stackA->rpnArr[stackA->top];
                        printf("stackB: %s, top: %d\n",stackB->rpnArr[stackB->top].tmain.text,stackB->top);
                        break;
                    }
                    c1+=3;c2+=3;
                }


                /*~~~~~~~~~~~~~~~~~~~~~~~~subArr: |oprnd|function|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
                else if(stackA->rpnArr[c1].tmain.type==TOKEN_FUNCTION && (stackA->rpnArr[c1-1].tmain.type==TOKEN_NUMBER || stackA->rpnArr[c1-1].tmain.type==TOKEN_VARIABLE)){
                    stackB->rpnArr[++(stackB->top)].num=calc(c1,-1);
                    stackB->rpnArr[stackB->top].tmain.type=TOKEN_NUMBER;
                    printf("stackB: %lf, top: %d\n",stackB->rpnArr[stackB->top].num,stackB->top);
                    if(c1+1==stackA->top){
                        stackB->rpnArr[++(stackB->top)]=stackA->rpnArr[stackA->top];
                    printf("stackB: %s, top: %d\n",stackB->rpnArr[stackB->top].tmain.text,stackB->top);
                        break;
                    }
                    
                    if(c1+2==stackA->top){
                        if(stackA->rpnArr[stackA->top].tmain.type==TOKEN_FUNCTION && (stackA->rpnArr[(stackA->top)-1].tmain.type==TOKEN_NUMBER || stackA->rpnArr[(stackA->top)-1].tmain.type==TOKEN_VARIABLE)){
                            stackB->rpnArr[++(stackB->top)].num=calc(stackA->top,-1);
                    printf("stackB: %lf, top: %d\n",stackB->rpnArr[stackB->top].num,stackB->top);
                            break;
                        }
                        else{
                            stackB->rpnArr[++(stackB->top)]=stackA->rpnArr[(stackA->top)-1];
                    printf("stackB: %s, top: %d\n",stackB->rpnArr[stackB->top].tmain.text,stackB->top);
                            stackB->rpnArr[++(stackB->top)]=stackA->rpnArr[stackA->top];
                    printf("stackB: %s, top: %d\n",stackB->rpnArr[stackB->top].tmain.text,stackB->top);
                            break;
                        }
                    }
                    c1+=2; c2+=2;
                }


                else{
                    stackB->rpnArr[++(stackB->top)]=stackA->rpnArr[c1-1];
                    printf("stackB: %s, top: %d\n",stackB->rpnArr[stackB->top].tmain.text,stackB->top);
                    if(c2==stackA->top){
                        stackB->rpnArr[++(stackB->top)]=stackA->rpnArr[stackA->top-1];
                    printf("stackB: %s, top: %d\n",stackB->rpnArr[stackB->top].tmain.text,stackB->top);
                        stackB->rpnArr[++(stackB->top)]=stackA->rpnArr[stackA->top];
                    printf("stackB: %s, top: %d\n",stackB->rpnArr[stackB->top].tmain.text,stackB->top);
                        break;
                    }
                    c1++;c2++;
                }
        }

        printf("swapped\n\n");

        /*~~~~~~~~~~~~~~~~~~~~~~~~~Swapping of Stacks~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
            stackSize=stackA->top+1;
            free(stackA->rpnArr);
            free(stackA);
            stackA=(rpnArr*)malloc(sizeof(rpnArr));
            if(stackA==NULL){
                fprintf(stderr,"memory allocation for stackA failed");
                return 1;
            }
            memset(stackA,0,sizeof(rpnArr));
            stackA->top=-1;
            stackA->rpnArr=(evalToken*)malloc(stackSize*sizeof(evalToken));
            if(stackA->rpnArr==NULL){
                fprintf(stderr, "Memory allocation failed for the stackA->rpnArr");
                return 1;
            }
            memset(stackA->rpnArr,0,stackSize*sizeof(evalToken));

            temp=stackB;
            stackB=stackA;
            stackA=temp;
        /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/    
            c1=1;c2=2;
    }
        if(stackA->top==0)
            val=stackA->rpnArr[stackA->top].num;
        if(stackB->top==0)
            val=stackB->rpnArr[stackB->top].num;

        freeStack(stackA);
        freeStack(stackB);
        return val;
}
