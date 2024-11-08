#include <iostream>
#include <cctype>
#include <cstring>
#include <map>
#include <set>
#include <vector>

using namespace std;

map<char, set<char>> firstSets;
map<char, set<char>> followSets;
vector<string> productions;
set<char> visited;

bool isNonTerminal(char c) {
    return isupper(c);
}

void addToSet(set<char>& s, char element) {
    s.insert(element);
}

void findFirst(char nonTerminal) {
    if (visited.count(nonTerminal)) return;
    visited.insert(nonTerminal);

    for (const auto& production : productions) {
        if (production[0] == nonTerminal) {
            for (size_t i = 2; i < production.size(); i++) {
                char symbol = production[i];
                if (symbol == '/') continue;

                if (!isNonTerminal(symbol)) {
                    addToSet(firstSets[nonTerminal], symbol);
                    break;
                } else {
                    findFirst(symbol);
                    for (char c : firstSets[symbol]) {
                        if (c != 'e') addToSet(firstSets[nonTerminal], c);
                    }
                    if (firstSets[symbol].count('e') == 0) break;
                }
            }
        }
    }
}

void findFollow(char nonTerminal) {
    if (followSets[nonTerminal].empty() && nonTerminal == productions[0][0]) {
        addToSet(followSets[nonTerminal], '$');
    }

    for (const auto& production : productions) {
        for (size_t i = 2; i < production.size(); i++) {
            if (production[i] == nonTerminal) {
                size_t next = i + 1;
                bool epsilonReached = true;
                
                while (epsilonReached && next < production.size()) {
                    epsilonReached = false;
                    char nextSymbol = production[next++];
                    for (char c : firstSets[nextSymbol]) {
                        if (c == 'e') epsilonReached = true;
                        else addToSet(followSets[nonTerminal], c);
                    }
                }

                if (epsilonReached || next == production.size()) {
                    if (production[0] != nonTerminal) {
                        findFollow(production[0]);
                        for (char c : followSets[production[0]]) {
                            addToSet(followSets[nonTerminal], c);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of production rules: ";
    cin >> n;
    productions.resize(n);

    cout << "Enter the production rules (e.g., S=abA/B):\n";
    for (int i = 0; i < n; i++) {
        cin >> productions[i];
    }

    char nonTerminal;
    cout << "Enter the non-terminal to find the First and Follow sets: ";
    cin >> nonTerminal;

    for (const auto& production : productions) {
        visited.clear();
        findFirst(production[0]);
    }

    for (const auto& production : productions) {
        findFollow(production[0]);
    }

    cout << "First(" << nonTerminal << ") = ";
    for (char c : firstSets[nonTerminal]) {
        cout << c << " ";
    }
    cout << endl;

    cout << "Follow(" << nonTerminal << ") = ";
    for (char c : followSets[nonTerminal]) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}



// S=AbC, A=aA, B=bB, C=c