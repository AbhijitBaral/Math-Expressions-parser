#ifndef POSTFIX_EVAL_H
#define POSTFIX_EVAL_H

#include "postfixParser.h"

/*Token redefined to store the token as well as the associated numeral value 
* if the token is of type variable or numeral */
typedef struct evalToken{
    token tmain;
    double num;
}evalToken;

/* Array to store the elements of type Token */
typedef struct rpnArr{
    evalToken *rpnArr;
    int top;
}rpnArr;

double eval(Stack *postfix);

#endif
