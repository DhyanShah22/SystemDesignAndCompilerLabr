#include <iostream>
#include <cctype>
#include <cstring>
#include <vector>
#include <string>
#include <set>

using namespace std;

bool isNonTerminal(char c) {
    return isupper(c);
}

void findFirst(set<char>& firstSet, const vector<string>& productions, char nonTerminal) {
    for (const string& production : productions) {
        if (production[0] == nonTerminal) {
            char rhs = production[2];  
            if (!isNonTerminal(rhs)) {
                firstSet.insert(rhs); // Add terminal to the set
            } else {
                findFirst(firstSet, productions, rhs); // Recur for non-terminal
            }
        }
    }
}

int main() {
    int n;
    vector<string> productions;
    char nonTerminal;

    cout << "Enter the number of production rules: ";
    cin >> n;

    cout << "Enter the production rules (e.g., E=TR):" << endl;
    for (int i = 0; i < n; i++) {
        string rule;
        cin >> rule;
        productions.push_back(rule);
    }

    cout << "Enter the non-terminal to find the first set: ";
    cin >> nonTerminal;

    set<char> firstSet;
    findFirst(firstSet, productions, nonTerminal);

    cout << "First(" << nonTerminal << ") = { ";
    for (char c : firstSet) {
        cout << c << " ";
    }
    cout << "}" << endl;

    return 0;
}
