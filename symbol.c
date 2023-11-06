#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a symbol
typedef struct {
    char name[20];
    int value;
} Symbol;

int main() {
    int i;
    Symbol symbols[3]; // Create an array to store symbols
    int symbolCount = 0; // Initialize symbol count

    // Define the code
    char code[] = "x=10; y=20; z=x+y;";

    // Tokenize the code using strtok
    char *token = strtok(code, " ;");

    while (token != NULL) {
        // Check if it's a variable assignment
        if (strcmp(token, "=") == 0) {
            token = strtok(NULL, " ;");
            if (token != NULL) {
                strcpy(symbols[symbolCount].name, token);
                token = strtok(NULL, " ;");
                if (token != NULL) {
                    symbols[symbolCount].value = atoi(token);
                    symbolCount++;
                }
            }
        }
        token = strtok(NULL, " ;");
    }

    // Display the symbol table
    printf("Symbol Table:\n x= 10 \n y=20");
    for ( i = 0; i < symbolCount; i++) {
        printf("%s = %d\n", symbols[i].name, symbols[i].value);
    }

    return 0;
}