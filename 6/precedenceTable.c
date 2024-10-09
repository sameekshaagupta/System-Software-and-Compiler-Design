#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OPERATORS 4
#define MAX_STACK_SIZE 100

char operators[] = {'+', '*', 'i', '$'};
int precedence[NUM_OPERATORS][NUM_OPERATORS] = {
    //   +   *   i   $
    { '>', '<', '<', '>' }, // + 
    { '>', '>', '<', '>' }, // * 
    { '>', '>', '>', '>' }, // i 
    { '<', '<', '<', '=' }  // $ 
};

int get_operator_index(char op) {
    for (int i = 0; i < NUM_OPERATORS; i++) {
        if (operators[i] == op) {
            return i;
        }
    }
    return -1;
}

void print_precedence_table() {
    printf("Operator Precedence Table:\n");
    printf("   ");
    for (int i = 0; i < NUM_OPERATORS; i++) {
        printf("  %c", operators[i]);
    }
    printf("\n");

    for (int i = 0; i < NUM_OPERATORS; i++) {
        printf(" %c ", operators[i]);
        for (int j = 0; j < NUM_OPERATORS; j++) {
            printf("  %c", precedence[i][j]);
        }
        printf("\n");
    }
}

typedef struct {
    char items[MAX_STACK_SIZE];
    int top;
} Stack;

void initialize_stack(Stack *s) {
    s->top = -1;
}

int is_empty(Stack *s) {
    return s->top == -1;
}

int is_full(Stack *s) {
    return s->top == MAX_STACK_SIZE - 1;
}

void push(Stack *s, char value) {
    if (!is_full(s)) {
        s->items[++(s->top)] = value;
    } else {
        printf("Stack overflow!\n");
    }
}

char pop(Stack *s) {
    if (!is_empty(s)) {
        return s->items[(s->top)--];
    } else {
        printf("Stack underflow!\n");
        return '\0';
    }
}

char peek(Stack *s) {
    if (!is_empty(s)) {
        return s->items[s->top];
    } else {
        return '\0';
    }
}

void print_stack(Stack *s) {
    for (int i = 0; i <= s->top; i++) {
        printf("%c", s->items[i]);
    }
    printf("\n");
}

int parse_string(const char *input) {
    Stack stack;
    initialize_stack(&stack);
    push(&stack, '$');

    int i = 0;
    char a = input[i];
    printf("Stack\tInput\tAction\n");
    
    while (a != '\0') {
        char stack_top = peek(&stack);
        int stack_index = get_operator_index(stack_top);
        int input_index = get_operator_index(a);

        if (stack_index == -1 || input_index == -1) {
            printf("Invalid operator encountered.\n");
            return 0;
        }

        char precedence_relation = precedence[stack_index][input_index];

        printf("%.*s\t%s\t", stack.top + 1, stack.items, &input[i]);

        if (precedence_relation == '<' || precedence_relation == '=') {
            printf("Shift\n");
            push(&stack, a);
            i++;
            a = input[i];
        } else if (precedence_relation == '>') {
            printf("Reduce\n");
            pop(&stack);
        } else {
            printf("Parsing error encountered.\n");
            return 0;
        }
    }

    while (peek(&stack) != '$') {
        char stack_top = peek(&stack);
        int stack_index = get_operator_index(stack_top);

        if (precedence[stack_index][get_operator_index('$')] == '>') {
            printf("%.*s\t \tReduce\n", stack.top + 1, stack.items);
            pop(&stack);
        } else {
            printf("Parsing error encountered during final stack processing.\n");
            return 0;
        }
    }

    if (peek(&stack) == '$' && a == '\0') {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    print_precedence_table();

    char input[MAX_STACK_SIZE];
    printf("Enter a string to parse: ");
    scanf("%s", input);

    if (parse_string(input)) {
        printf("The string can be parsed successfully.\n");
    } else {
        printf("The string cannot be parsed.\n");
    }

}