#include <iostream>
#include <string>

using namespace std;

// Function prototypes
bool isE(const string& str, int& index, string& derivation);
bool isEP(const string& str, int& index, string& derivation);
bool isT(const string& str, int& index, string& derivation);
bool isTP(const string& str, int& index, string& derivation);
bool isF(const string& str, int& index, string& derivation);

// Function to check if a string can be derived from E
bool isE(const string& str, int& index, string& derivation) {
    derivation += "E -> T E'\n";
    if (isT(str, index, derivation)) {
        if (isEP(str, index, derivation)) {
            return true;
        }
    }
    return false;
}

// Function to check if a string can be derived from E'
bool isEP(const string& str, int& index, string& derivation) {
    if (index < str.length() && str[index] == '+') {
        derivation += "E' -> + T E'\n";
        index++;
        if (isT(str, index, derivation)) {
            return isEP(str, index, derivation);
        }
        return false;
    }
    derivation += "E' -> ε\n";
    return true;  // epsilon (empty string)
}

// Function to check if a string can be derived from T
bool isT(const string& str, int& index, string& derivation) {
    derivation += "T -> F T'\n";
    if (isF(str, index, derivation)) {
        if (isTP(str, index, derivation)) {
            return true;
        }
    }
    return false;
}

// Function to check if a string can be derived from T'
bool isTP(const string& str, int& index, string& derivation) {
    if (index < str.length() && str[index] == '*') {
        derivation += "T' -> * F T'\n";
        index++;
        if (isF(str, index, derivation)) {
            return isTP(str, index, derivation);
        }
        return false;
    }
    derivation += "T' -> ε\n";
    return true;  // epsilon (empty string)
}

// Function to check if a string can be derived from F
bool isF(const string& str, int& index, string& derivation) {
    if (index < str.length() && str[index] == '(') {
        derivation += "F -> (E)\n";
        index++;
        if (isE(str, index, derivation)) {
            if (index < str.length() && str[index] == ')') {
                index++;
                return true;
            }
        }
        return false;
    } else if (index < str.length() && str[index] == 'a') {
        derivation += "F -> a\n";
        index++;
        return true;
    }
    return false;
}

int main() {
    string input;

    cout << "Enter the string to check: ";
    cin >> input;

    string derivation;
    int index = 0;

    if (isE(input, index, derivation) && index == input.length()) {
        cout << "The string belongs to the grammar." << endl;
        cout << "Derivation steps:" << endl;
        cout << derivation;
    } else {
        cout << "The string does not belong to the grammar." << endl;
    }

    return 0;
}
