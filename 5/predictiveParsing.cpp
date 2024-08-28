#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

map<string, vector<vector<string>>> rules;
map<string, set<string>> first;
map<string, set<string>> follow;
set<string> nonTerminals;
set<string> terminals;

set<string> getFirst(const string& symbol) {
    if (terminals.find(symbol) != terminals.end()) {
        return {symbol};
    }

    if (symbol == "ε") {
        return {"ε"};
    }

    if (first.find(symbol) != first.end()) {
        return first[symbol];
    }

    set<string> result;

    for (const auto& production : rules[symbol]) {
        bool epsilonFound = true;

        for (const auto& part : production) {
            set<string> partFirst = getFirst(part);

            result.insert(partFirst.begin(), partFirst.end());

            if (partFirst.find("ε") == partFirst.end()) {
                epsilonFound = false;
                break;
            }
        }

        if (epsilonFound) {
            result.insert("ε");
        }
    }

    first[symbol] = result;
    return result;
}

set<string> getFollow(const string& symbol) {
    if (follow.find(symbol) != follow.end()) {
        return follow[symbol];
    }

    set<string> result;

    if (symbol == "S") {
        result.insert("$");
    }

    for (const auto& [nt, productions] : rules) {
        for (const auto& production : productions) {
            for (size_t i = 0; i < production.size(); ++i) {
                if (production[i] == symbol) {
                    if (i + 1 < production.size()) {
                        set<string> nextFirst = getFirst(production[i + 1]);
                        result.insert(nextFirst.begin(), nextFirst.end());
                        result.erase("ε");

                        if (nextFirst.find("ε") == nextFirst.end() || terminals.find(production[i + 1]) != terminals.end()) {
                            continue;
                        }
                    }

                    if (i + 1 == production.size() || first[production[i + 1]].find("ε") != first[production[i + 1]].end()) {
                        set<string> ntFollow = getFollow(nt);
                        result.insert(ntFollow.begin(), ntFollow.end());
                    }
                }
            }
        }
    }

    follow[symbol] = result;
    return result;
}

void readGrammar() {
    string line;

    while (getline(cin, line) && !line.empty()) {
        istringstream iss(line);
        string left, arrow, right;
        iss >> left >> arrow;

        if (arrow != "->") {
            cerr << "Error: Expected '->' in production rule." << endl;
            continue;
        }

        nonTerminals.insert(left);

        vector<string> production;
        while (iss >> right) {
            if (right == "|") {
                if (!production.empty()) {
                    rules[left].push_back(production);
                    production.clear();
                }
            } else {
                production.push_back(right);
            }
        }

        if (!production.empty()) {
            rules[left].push_back(production);
        }
    }

    for (const auto& [nt, productions] : rules) {
        nonTerminals.insert(nt);

        for (const auto& production : productions) {
            for (const auto& symbol : production) {
                if (nonTerminals.find(symbol) == nonTerminals.end() && symbol != "ε") {
                    terminals.insert(symbol);
                }
            }
        }
    }
}

void calculateFirst() {
    for (const auto& nt : nonTerminals) {
        getFirst(nt);
    }
}

void calculateFollow() {
    for (const auto& nt : nonTerminals) {
        getFollow(nt);
    }
}

void printSets() {
    cout << "First Sets:\n";
    for (const auto& [nt, set] : first) {
        cout << nt << ": ";
        for (const auto& symbol : set) {
            cout << symbol << " ";
        }
        cout << endl;
    }

    cout << "Follow Sets:\n";
    for (const auto& [nt, set] : follow) {
        cout << nt << ": ";
        for (const auto& symbol : set) {
            cout << symbol << " ";
        }
        cout << endl;
    }
}

int main() {
    readGrammar();
    calculateFirst();
    calculateFollow();
    printSets();
    return 0;
}
