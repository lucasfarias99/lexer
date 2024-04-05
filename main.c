#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef enum {
    ID,
    OPERATOR,
    NUM_TYPE_INT,
    NUM_TYPE_FLOAT,
    INVALID,
    END,
} TokenType;

typedef struct {
    TokenType  type;
    char lexeme[MAX_SIZE];
} Token;                           

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

Token getNextToken(FILE* file){
    Token token;
    char c;
    int i = 0;
    bool flag1 = true;
    bool flag2 = false;

    while((c = fgetc(file)) != EOF){
        if(isspace(c))  continue;

        if (isalpha(c)) {
            token.type = ID;
            token.lexeme[i++] = c;
            while ((isalnum(c = fgetc(file)) || c != ' ') && !isOperator(c)) {
                    if (!isalnum(c)) {
                    token.type = INVALID;
                }
                token.lexeme[i++] = c;
            }
            ungetc(c, file);
        } else if (isdigit(c) || c == '.') {
            if (c == '.') {
                token.type = INVALID;
                token.lexeme[i++] = c;
                while (isdigit(c = fgetc(file))) {
                    token.type = NUM_TYPE_FLOAT;
                    token.lexeme[i++] = c;
                }
            } else {
                token.type = NUM_TYPE_INT;
                token.lexeme[i++] = c;
                
                while (isdigit(c = fgetc(file)) || c == '.' || isalpha(c)) {
                    if (c == '.' &&  flag2) {
                        token.type = INVALID; 
                    }
                    if (c == '.' && flag1) {
                        token.type = NUM_TYPE_FLOAT; 
                        flag1 = false; 
                        flag2 = true;
                    }
                    if(isalpha(c)) {
                        token.type = INVALID;
                        flag1 = false;
                    }
                    token.lexeme[i++] = c;
                }
            } 
            ungetc(c, file);
        } else if (isOperator(c)) {
            token.type = OPERATOR;
            token.lexeme[i++] = c;
        } else {
            token.type = INVALID;
            token.lexeme[i++] = c;
            while ((c = fgetc(file)) != ' ') {
                token.lexeme[i++] = c;
            }
            ungetc(c, file);
        }
        token.lexeme[i] = '\0';
        return token;
    }

    token.type = END;
    return token;

}

int main() {
    FILE* file = fopen("input.txt", "r");
    if(file == NULL ){
        printf("Nao foi possivel abrir o arquivo.\n");
        return 1;
    }
    
    Token token;
    while((token = getNextToken(file)).type != END){
        switch(token.type){
            case ID:
                printf("Token: ID,    Lexema: %s\n", token.lexeme);
                break;
            case OPERATOR:
                printf("Token: OPERATOR,   Lexema: %s\n", token.lexeme);
                break;
            case NUM_TYPE_INT:
                printf("Token: NUM_TYPE_INT,    Lexema: %s\n", token.lexeme);
                break;
            case NUM_TYPE_FLOAT:
                printf("Token: NUM_TYPE_FLOAT,    Lexema: %s\n", token.lexeme);
                break;
            case INVALID:
                printf("Token: INVALID, Lexema: %s\n", token.lexeme);
                break;
            case END: break;
        }
    }

    return 0;
}
