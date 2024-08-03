#ifndef POSTFIX_PARSER_H
#define POSTFIX_PARSER_H

#include "Lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void push(Stack *Stack, token Token);
void pop(Stack *Stack);
int P(token Token);
Stack* parser(Stack *tokenized);

#endif
