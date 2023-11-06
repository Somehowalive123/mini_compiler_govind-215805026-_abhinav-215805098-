#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

// Token types
typedef enum {
    TOKEN_INT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_ERROR
} TokenType;

// Structure to represent a token
typedef struct {
    TokenType type;
    char lexeme[100];
    int line;
} Token;

// Function to tokenize the source code
Token getNextToken(FILE *sourceFile, int *lineNumber);

// Function to generate intermediate code for expressions
void generateIntermediateCode(Token *tokens, FILE *intermediateFile);

int main() {
    FILE *sourceFile = fopen("source_code.txt", "r");
    if (!sourceFile) {
        perror("Error opening source code file");
        return 1;
    }

    FILE *listingFile = fopen("listing.txt", "w");
    if (!listingFile) {
        perror("Error opening listing file");
        fclose(sourceFile);
        return 1;
    }

    FILE *intermediateFile = fopen("intermediate_code.txt", "w");
    if (!intermediateFile) {
        perror("Error opening intermediate code file");
        fclose(sourceFile);
        fclose(listingFile);
        return 1;
    }

    int lineNumber = 1;
    Token token;

    while ((token = getNextToken(sourceFile, &lineNumber)).type != TOKEN_EOF) {
        // Print line number and token
        fprintf(listingFile, "Line %d: %s\n", token.line, token.lexeme);

        if (token.type == TOKEN_ERROR) {
            fprintf(listingFile, "Error: Invalid token\n");
        }
    }

    // Generate intermediate code
    rewind(sourceFile);
    lineNumber = 1;
    Token *tokens = (Token *)malloc(sizeof(Token) * 1000);
    int tokenCount = 0;

    while ((token = getNextToken(sourceFile, &lineNumber)).type != TOKEN_EOF) {
        tokens[tokenCount++] = token;
    }

    generateIntermediateCode(tokens, intermediateFile);

    fclose(sourceFile);
    fclose(listingFile);
    fclose(intermediateFile);
    free(tokens);

    return 0;
}

Token getNextToken(FILE *sourceFile, int *lineNumber) {
    Token token;
    char ch;

    while ((ch = fgetc(sourceFile)) != EOF) {
        if (ch == '\n') {
            (*lineNumber)++;
            continue;
        }

        if (isspace(ch)) {
            continue; // Skip whitespace
        }

        if (isdigit(ch)) {
            // Tokenize integers
            token.type = TOKEN_INT;
            ungetc(ch, sourceFile);
            fscanf(sourceFile, "%s", token.lexeme);
            token.line = *lineNumber;
            return token;
        } else if (ch == '+') {
            token.type = TOKEN_PLUS;
        } else if (ch == '-') {
            token.type = TOKEN_MINUS;
        } else if (ch == '*') {
            token.type = TOKEN_MUL;
        } else if (ch == '/') {
            token.type = TOKEN_DIV;
        } else if (ch == '(') {
            token.type = TOKEN_LPAREN;
        } else if (ch == ')') {
            token.type = TOKEN_RPAREN;
        } else {
            // Invalid token
            token.type = TOKEN_ERROR;
            token.lexeme[0] = ch;
            token.lexeme[1] = '\0';
            token.line = *lineNumber;
            return token;
        }

        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        token.line = *lineNumber;
        return token;
    }

    // End of file
    token.type = TOKEN_EOF;
    token.lexeme[0] = '\0';
    token.line = *lineNumber;
    return token;
}

void generateIntermediateCode(Token *tokens, FILE *intermediateFile) {
    fprintf(intermediateFile, "Intermediate Code:\n");
    int i;
    for ( i = 0; tokens[i].type != TOKEN_EOF; i++) {
        if (tokens[i].type == TOKEN_INT) {
            fprintf(intermediateFile, "LOAD %s\n", tokens[i].lexeme);
        } else if (tokens[i].type == TOKEN_PLUS) {
            fprintf(intermediateFile, "ADD\n");
        } else if (tokens[i].type == TOKEN_MINUS) {
            fprintf(intermediateFile, "SUB\n");
        } else if (tokens[i].type == TOKEN_MUL) {
            fprintf(intermediateFile, "MUL\n");
        } else if (tokens[i].type == TOKEN_DIV) {
            fprintf(intermediateFile, "DIV\n");
        } else if (tokens[i].type == TOKEN_LPAREN) {
            fprintf(intermediateFile, "LPAREN\n");
        } else if (tokens[i].type == TOKEN_RPAREN) {
            fprintf(intermediateFile, "RPAREN\n");
        } else if (tokens[i].type == TOKEN_ERROR) {
            fprintf(intermediateFile, "Error: Invalid token '%s'\n", tokens[i].lexeme);
        }
    }
}
