#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Structure to store information in the symbol table
struct SymbolTable {
    char token[MAX];        // Name of the variable or function
    char scope[MAX];        // Scope: global or local
    char dataType[MAX];     // Data type: int, float, etc.
    char kind[MAX];         // Variable or procedure (function)
} table[MAX];

int tableIndex = 0;

// Function to check if a string is a data type
int isDataType(char* str) {
    return (strcmp(str, "int") == 0 || strcmp(str, "float") == 0 || 
            strcmp(str, "char") == 0 || strcmp(str, "double") == 0 || 
            strcmp(str, "void") == 0);
}

// Function to check if a character is a valid identifier character
int isValidChar(char c) {
    return (isalpha(c) || c == '_' || isdigit(c));
}

// Function to add entry to the symbol table
void addToSymbolTable(char* token, char* scope, char* dataType, char* kind) {
    strcpy(table[tableIndex].token, token);
    strcpy(table[tableIndex].scope, scope);
    strcpy(table[tableIndex].dataType, dataType);
    strcpy(table[tableIndex].kind, kind);
    tableIndex++;
}

// Function to print the symbol table
void printSymbolTable() {
    printf("\nSymbol Table:\n");
    printf("%-20s %-10s %-10s %-15s\n", "Token", "Scope", "Data Type", "Variable/Procedure");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < tableIndex; i++) {
        printf("%-20s %-10s %-10s %-15s\n", table[i].token, table[i].scope, table[i].dataType, table[i].kind);
    }
}

// Main function to process the input code and create a symbol table
int main() {
    char code[MAX][MAX];
    char currentScope[MAX] = "global";
    int n;

    printf("Enter the number of lines of code: ");
    scanf("%d", &n);
    getchar();  // To consume the newline after entering the number

    printf("Enter the code line by line:\n");
    for (int i = 0; i < n; i++) {
        fgets(code[i], MAX, stdin);
        code[i][strlen(code[i]) - 1] = '\0';  // Remove the trailing newline
    }

    for (int i = 0; i < n; i++) {
        char token[MAX], dataType[MAX], kind[MAX];
        char* line = code[i];
        int j = 0, k = 0;
        
        // Split the line into tokens
        while (sscanf(line + j, "%s", token) == 1) {
            j += strlen(token) + 1; // Move the index past the token and space

            // Check for data type declaration
            if (isDataType(token)) {
                strcpy(dataType, token);
                sscanf(line + j, "%s", token); // Read the next token (variable name or function)
                j += strlen(token) + 1;

                // Check if it's a function (procedure)
                if (strchr(line + j, '(')) {
                    strcpy(kind, "Procedure");
                    strcpy(currentScope, token); // Change scope to function name
                } else {
                    strcpy(kind, "Variable");
                }
                addToSymbolTable(token, currentScope, dataType, kind);

           
            } else if (strchr(token, '}')) {
                strcpy(currentScope, "global");
            }
        }
    }

    printSymbolTable();

    return 0;
}
