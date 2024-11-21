#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cctype>

using namespace std;

vector<string> productions;
map<char, set<char>> firstSets, followSets;

void computeFirst(char c);
void computeFollow(char c);
void addFirstToFollow(const set<char>& source, set<char>& destination);

int main() {
    int n;
    char startSymbol;

    cout<<"Enter no of prods: "<<endl;
    cin >> n;
    productions.resize(n);
    cin.ignore();
    
    cout<<"Enter production: "<< endl;
    for (int i = 0; i < n; i++) {
        getline(cin, productions[i]);
    }

    cout << "Enter the start symbol: "<<endl;
    cin >> startSymbol;

    for (const auto& production : productions) {
        char nonTerminal = production[0];
        computeFirst(nonTerminal);
    }

    followSets[startSymbol].insert('$');
    for (const auto& production : productions) {
        char nonTerminal = production[0];
        computeFollow(nonTerminal);
    }

    for (const auto& [nonTerminal, firstSet] : firstSets) {
        cout << "FIRST(" << nonTerminal << ") = { ";
        for (char symbol : firstSet) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    for (const auto& [nonTerminal, followSet] : followSets) {
        cout << "FOLLOW(" << nonTerminal << ") = { ";
        for (char symbol : followSet) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    return 0;
}

void computeFirst(char c) {
    if (firstSets.count(c)) return;

    set<char> result;
    for (const auto& production : productions) {
        if (production[0] == c) {
            if (!isupper(production[2])) {
                result.insert(production[2]);
            } else {
                char next = production[2];
                computeFirst(next);
                addFirstToFollow(firstSets[next], result);
            }
        }
    }
    firstSets[c] = result;
}

void computeFollow(char c) {
    for (const auto& production : productions) {
        for (size_t i = 2; i < production.length(); i++) {
            if (production[i] == c) {
                if (i + 1 < production.length()) {
                    char next = production[i + 1];
                    if (!isupper(next)) {
                        followSets[c].insert(next);
                    } else {
                        addFirstToFollow(firstSets[next], followSets[c]);
                        followSets[c].erase('$');
                    }
                }
                if (i + 1 == production.length() || firstSets[production[i + 1]].count('$')) {
                    char lhs = production[0];
                    if (lhs != c) {
                        computeFollow(lhs);
                        addFirstToFollow(followSets[lhs], followSets[c]);
                    }
                }
            }
        }
    }
}

void addFirstToFollow(const set<char>& source, set<char>& destination) {
    for (char symbol : source) {
        if (symbol != '$') {
            destination.insert(symbol);
        }
    }
}
