#include "Lexer.h"

int main(){
    char input[]="sin(x)+x^2+ln(x^2+45x)";
    token* tokenized=lex(input);

    return(0);
}
