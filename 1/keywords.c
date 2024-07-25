// C prog: reading from file identifier, keywords, operator, separator and number

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100

const char *keywords[] = {
    "int", "float", "double", "char", "if", "else", "while", "for", "do", "return", "void", "static", "struct"
};
const int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

const char *operators[] = {
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>"
};
const int num_operators = sizeof(operators) / sizeof(operators[0]);

const char *separators[] = {
    ";", ",", "(", ")", "{", "}", "[", "]"
};
const int num_separators = sizeof(separators) / sizeof(separators[0]);

int is_keyword(const char *token) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(token, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int is_operator(const char *token) {
    for (int i = 0; i < num_operators; i++) {
        if (strcmp(token, operators[i]) == 0)
            return 1;
    }
    return 0;
}

int is_separator(const char *token) {
    for (int i = 0; i < num_separators; i++) {
        if (strcmp(token, separators[i]) == 0)
            return 1;
    }
    return 0;
}

int is_number(const char *token) {
    for (int i = 0; token[i] != '\0'; i++) {
        if (!isdigit(token[i]))
            return 0;
    }
    return 1;
}

int is_identifier(const char *token) {
    if (!isalpha(token[0]) && token[0] != '_')
        return 0;

    for (int i = 1; token[i] != '\0'; i++) {
        if (!isalnum(token[i]) && token[i] != '_')
            return 0;
    }

    return 1;
}

void analyze_token(const char *token) {
    if (is_keyword(token)) {
        printf("Keyword: %s\n", token);
    } else if (is_operator(token)) {
        printf("Operator: %s\n", token);
    } else if (is_separator(token)) {
        printf("Separator: %s\n", token);
    } else if (is_number(token)) {
        printf("Number: %s\n", token);
    } else if (is_identifier(token)) {
        printf("Identifier: %s\n", token);
    } else {
        printf("Unknown: %s\n", token);
    }
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

    char token[MAX_TOKEN_LENGTH];
    while (fscanf(file, "%s", token) != EOF) {
        analyze_token(token);
    }

    fclose(file);
    return 0;
}
