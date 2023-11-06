#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

enum TokenType {
    IDENTIFIER,
    ASSIGNMENT,
    INTEGER,
    PLUS,
    SEMICOLON,
    EOF_TOKEN,
    ERROR,
};

struct Token {
    enum TokenType type;
    char lexeme[100];
    int line;
};

struct Token getNextToken(FILE *file) {
    struct Token token;
    int c = fgetc(file);

    if (c == EOF) {
        token.type = EOF_TOKEN;
    } else if (isdigit(c)) {
        ungetc(c, file);
        fscanf(file, "%d", &token.lexeme);
        token.type = INTEGER;
    } else if (isalpha(c)) {
        ungetc(c, file);
        fscanf(file, "%s", token.lexeme);
        token.type = IDENTIFIER;
    } else if (c == '=') {
        token.type = ASSIGNMENT;
    } else if (c == '+') {
        token.type = PLUS;
    } else if (c == ';') {
        token.type = SEMICOLON;
    } else {
        token.type = ERROR;
    }
    return token;
}

int main() {
    FILE *inputFile = fopen("source_code.txt", "r");
    FILE *listingFile = fopen("listing.txt", "w");
    struct Token currentToken;
    int lineCount = 1;

    while ((currentToken = getNextToken(inputFile)).type != EOF_TOKEN) {
        fprintf(listingFile, "Line %d: ", lineCount);
        switch (currentToken.type) {
            case IDENTIFIER:
                fprintf(listingFile, "Identifier '%s'\n", currentToken.lexeme);
                break;
            case ASSIGNMENT:
                fprintf(listingFile, "Assignment Operator\n");
                break;
            case INTEGER:
                fprintf(listingFile, "Integer '%d'\n", currentToken.lexeme);
                break;
            case PLUS:
                fprintf(listingFile, "Plus Operator\n");
                break;
            case SEMICOLON:
                fprintf(listingFile, "Semicolon\n");
                lineCount++;
                break;
            case ERROR:
                fprintf(listingFile, "Error: Unexpected character\n");
                break;
            default:
                break;
        }
    }

    fclose(inputFile);
    fclose(listingFile);
    return 0;
}