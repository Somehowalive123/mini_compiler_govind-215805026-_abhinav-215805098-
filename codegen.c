#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Define token types
typedef enum {
    TOKEN_INT,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_IDENTIFIER,
    TOKEN_ERROR,
    TOKEN_EOF,
} TokenType;

// Structure to represent a token
typedef struct {
    TokenType type;
    char lexeme[100];
    int line;
} Token;

// Function to tokenize the source code
Token getNextToken(FILE *sourceFile, int *lineNumber);

// Function to generate target code (simplified for illustration)
void generateTargetCode(FILE *sourceFile, FILE *targetFile);

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

    int lineNumber = 1;
    Token token;

    while ((token = getNextToken(sourceFile, &lineNumber)).type != TOKEN_EOF) {
        // Print line number and token
        fprintf(listingFile, "Line %d: %s\n", token.line, token.lexeme);

        if (token.type == TOKEN_ERROR) {
            fprintf(listingFile, "Error: Invalid token\n");
        }
    }

    // Generate target code (simplified, actual code generation depends on the target architecture)
    FILE *targetFile = fopen("target_code.txt", "w");
    if (!targetFile) {
        perror("Error opening target code file");
        fclose(sourceFile);
        fclose(listingFile);
        return 1;
    }

    // Actual target code generation (simplified example)
    generateTargetCode(sourceFile, targetFile);

    fclose(sourceFile);
    fclose(listingFile);
    fclose(targetFile);

    return 0;
}

Token getNextToken(FILE *sourceFile, int *lineNumber) {
    // Implement tokenization logic here (simplified for illustration)
    // Return token type, lexeme, and line number
    // Handle errors and return TOKEN_ERROR if needed
}

void generateTargetCode(FILE *sourceFile, FILE *targetFile) {
    // Implement target code generation logic here (simplified for illustration)
    // You should generate code based on the parsed source code
    // This code depends on the target architecture or language
    // In this simplified example, we'll write a placeholder statement
    fprintf(targetFile, "PUSH 42\n");
    fprintf(targetFile, "ADD\n");
    fprintf(targetFile, "POP\n");
}


