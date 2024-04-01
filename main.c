#include <stdio.h>
#include <stdlib.h>

#define MAX_TOKEN_LENGHT 100

typedef enum {
    ID,
    OPERADOR,
    INT,
    FLOAT,
    INVALID
} TokenType;

typedef struct {
    TokenType  type;
    char lexeme[MAX_TOKEN_LENGHT];
} Token;



int main() {
    return 0;
}
