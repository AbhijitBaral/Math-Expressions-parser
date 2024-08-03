#ifndef LEXER_H
#define LEXER_H

//This enumeration defines the types of recognizable tokens for the specific code.

typedef enum{
    TOKEN_NUMBER,
    TOKEN_FUNCTION,
    TOKEN_VARIABLE,
    TOKEN_OPERATOR,
    TOKEN_PARENTHESES
}tokenType;

/*This structure represents a token, which includes the text of the token as written in the string 
 * and the token type */

typedef struct token{
    char* text;
    tokenType type;
}token;

typedef struct Stack{
    token *stack;
    int stackSize;
    int top;    
}Stack;

Stack *lex(char *input);
void freeStack(Stack *tokenized);

#endif
