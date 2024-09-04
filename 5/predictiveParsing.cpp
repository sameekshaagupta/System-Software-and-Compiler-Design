#include <iostream>
#include <cctype>
#include <cstring>

#define MAX 10

using namespace std;

struct Grammar {
    char nonTerminal;
    char production[MAX][MAX];
    int productionCount;
};

char firstSet[MAX][MAX];
char followSet[MAX][MAX];
Grammar grammar[MAX];
int n;

void findFirst(char first[], char nonTerminal) {
    for (int i = 0; i < n; i++) {
        if (grammar[i].nonTerminal == nonTerminal) {
            for (int j = 0; j < grammar[i].productionCount; j++) {
                char symbol = grammar[i].production[j][0];

                if (symbol == 'e') {  // Check for epsilon
                    strcat(first, "e");
                } else if (islower(symbol)) {
                    strncat(first, &symbol, 1);
                } else {
                    char tempFirst[MAX] = "";
                    findFirst(tempFirst, symbol);
                    strcat(first, tempFirst);
                }
            }
        }
    }
}

void findFollow(char follow[], char nonTerminal) {
    if (nonTerminal == grammar[0].nonTerminal) {
        strcat(follow, "$");
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < grammar[i].productionCount; j++) {
            char* pos = strchr(grammar[i].production[j], nonTerminal);

            if (pos != nullptr) {
                if (*(pos + 1) != '\0') {
                    char nextSymbol = *(pos + 1);
                    if (nextSymbol == 'e') {
                        char tempFollow[MAX] = "";
                        findFollow(tempFollow, grammar[i].nonTerminal);
                        strcat(follow, tempFollow);
                    } else if (islower(nextSymbol)) {
                        strncat(follow, &nextSymbol, 1);
                    } else {
                        char tempFirst[MAX] = "";
                        findFirst(tempFirst, nextSymbol);
                        strcat(follow, tempFirst);
                    }
                } else {
                    if (grammar[i].nonTerminal != nonTerminal) {
                        char tempFollow[MAX] = "";
                        findFollow(tempFollow, grammar[i].nonTerminal);
                        strcat(follow, tempFollow);
                    }
                }
            }
        }
    }
}

int main() {
    cout << "Enter the number of non-terminals: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter the non-terminal: ";
        cin >> grammar[i].nonTerminal;

        cout << "Enter the number of productions for " << grammar[i].nonTerminal << ": ";
        cin >> grammar[i].productionCount;

        for (int j = 0; j < grammar[i].productionCount; j++) {
            cout << "Enter production " << j + 1 << " for " << grammar[i].nonTerminal << " (use 'e' for epsilon): ";
            cin >> grammar[i].production[j];
        }
    }

    for (int i = 0; i < n; i++) {
        char first[MAX] = "";
        findFirst(first, grammar[i].nonTerminal);
        strcpy(firstSet[i], first);

        char follow[MAX] = "";
        findFollow(follow, grammar[i].nonTerminal);
        strcpy(followSet[i], follow);
    }

    for (int i = 0; i < n; i++) {
        cout << "\nFirst(" << grammar[i].nonTerminal << ") = { ";
        for (int j = 0; j < strlen(firstSet[i]); j++) {
            cout << firstSet[i][j] << " ";
        }
        cout << "}";

        cout << "\nFollow(" << grammar[i].nonTerminal << ") = { ";
        for (int j = 0; j < strlen(followSet[i]); j++) {
            cout << followSet[i][j] << " ";
        }
        cout << "}\n";
    }

    return 0;
}
