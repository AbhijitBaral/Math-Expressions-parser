#ifndef RPN_ARRAY_EVAL_H
#define RPN_ARRAY_EVAL_H

#include "Lexer.h"
#include "postfixParser.h"
#include <math.h>
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

double calc(int c1, int c2);
double eval(Stack *postfix,double x0);

#endif
