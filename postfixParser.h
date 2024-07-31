#ifndef POSTFIX_PARSER_H
#define POSTFIX_PARSER_H

#include "Lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stack{
    token *stack;
    int stackSize;
    int top;    
}Stack;

void push(Stack *Stack, token Token);
void pop(Stack *Stack);
int P(token Token);
Stack* parser(token *tokenized, char *input);
void freeStack(Stack *Stack);

#endif
