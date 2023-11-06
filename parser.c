// parser.c
#include <stdio.h>

// Function to parse the source code
void parse(FILE *sourceFile);

int main() {
    FILE *sourceFile = fopen("source_code.txt", "r");
    if (sourceFile == NULL) {
        perror("Error opening source code file");
        return 1;
    }

    parse(sourceFile);

    fclose(sourceFile);
    return 0;
}

void parse(FILE *sourceFile) {
    int i=0;
    void Error()
    {
        if(i=1)
        {
        printf("ERROR DETECTED IN THE FILE");
        }

    }
   // Implement parsing logic here
    // Check for program structure according to your language's grammar.
    // Print error messages as needed.
    // For simplicity, we'll just print a message.
    printf("PARSING THE CURRENT FILE\n");
    // Implement parsing logic here
    // Check for program structure according to your language's grammar.
    printf("\n%d ERRORS\n",i);
    // Print error messages as needed.
    printf("\nParsing completed successfully.\n");
    // For simplicity, we'll just print a message.
}
