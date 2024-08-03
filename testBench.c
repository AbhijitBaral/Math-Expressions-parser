#include "rpnArrayEval.h"
#define TOLERANCE 1e-4
int main(void){
    char line[250];
    char expression[250];
    char valAct[250];
    double valCalc;
    token *currentToken;
    Stack *tokenized, *postfixArray;

    int n=1;
    FILE *file=fopen("testCases.txt","r");
    if(file==NULL){
        fprintf(stderr,"Error openeing file\n");
        return 1;
    }
    
    while(fgets(line,sizeof(line),file)){

        //fgets writes "\n" character.It needs to be replaced with "\0"
        line[strcspn(line,"\n")]='\0';

        //Skip empty lines
        if(strlen(line)==0)
            continue;

        printf("\n%d\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n%s\n",n++,line);
        tokenized=lex(line);
        for(int i=0; i<=tokenized->top; i++)
            printf("Token: %s, type: %d\n",tokenized->stack[i].text,tokenized->stack[i].type);
        postfixArray=parser(tokenized);
        printf("\nPostfix:\n");
        for(int i=0; i<=postfixArray->top;i++)
            printf("%s\n",postfixArray->stack[i].text);

        valCalc=eval(postfixArray,5.0);
        printf("%lf\n",valCalc);
        
        if(fgets(line,sizeof(line),file)){
            line[strcspn(line,"\n")]='\0';
            if(fabs(valCalc-atof(line))>TOLERANCE){
                printf("Difference: %lf\n",fabs(valCalc-atof(line)));
                printf("Actual value: %s\n",line);
                printf("Calculated: %lf\n\n",valCalc);
                break;
            }
        }
    }
    fclose(file);
    return(0);
}
