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
    FILE* file = fopen("input.txt", "r");
    if(file == NULL ){
        printf("Nao foi possivel abrir o arquivo.\n");
        return 1;
    }

    
    return 0;
}
