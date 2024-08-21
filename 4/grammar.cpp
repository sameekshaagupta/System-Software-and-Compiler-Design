#include <iostream>
#include <string>

using namespace std;

// Function to check if a string can be derived from A
bool isA(const string& str, int& index, string& derivation) {
    if (index >= str.length()) {
        derivation += "A -> ε\n";
        return true;  // Represents the epsilon (empty) production
    }

    if (str[index] == 'a') {
        derivation += "A -> aB\n";
        index++;
        if (index < str.length() && str[index] == 'b') {
            derivation += "B -> b\n";
            index++;
            return true;  // A -> aB
        } else {
            return false;  // B must be followed by 'b'
        }
    }

    derivation += "A -> ε\n";
    return true;  // epsilon (empty string)
}

// Function to check if a string can be derived from S
bool isS(const string& str, string& derivation) {
    int index = 0;

    derivation += "S -> AA\n";

    // Check if the string can be split into AA
    string firstA, secondA;

    if (!isA(str, index, firstA)) return false;
    if (!isA(str, index, secondA)) return false;

    derivation += firstA + secondA;

    return index == str.length();
}

int main() {
    string input;

    cout << "Enter the string to check: ";
    cin >> input;

    string derivation;
    if (isS(input, derivation)) {
        cout << "The string belongs to the grammar." << endl;
        cout << "Derivation steps:" << endl;
        cout << derivation;
    } else {
        cout << "The string does not belong to the grammar." << endl;
    }

    return 0;
}
