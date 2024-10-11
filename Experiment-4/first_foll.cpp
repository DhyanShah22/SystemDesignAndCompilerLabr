#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

set<char> findFirst(char nonTerminal, const vector<string>& productions);
set<char> findFollow(char nonTerminal, const vector<string>& productions, const set<char>& firstSet);

int main() {
    int n;
    vector<string> productions;

    cout << "Enter the number of production rules: ";
    cin >> n;

    cout << "Enter the production rules (e.g., S=abAB/bB):\n";
    cin.ignore(); 
    for (int i = 0; i < n; i++) {
        string production;
        getline(cin, production);
        productions.push_back(production);
    }

    char nonTerminal;
    cout << "Enter the non-terminal to find the First and Follow sets: ";
    cin >> nonTerminal;

    set<char> firstSet = findFirst(nonTerminal, productions);
    cout << "First(" << nonTerminal << ") = ";
    for (char c : firstSet) {
        cout << c << " ";
    }
    cout << endl;

    set<char> followSet = findFollow(nonTerminal, productions, firstSet);
    cout << "Follow(" << nonTerminal << ") = ";
    for (char c : followSet) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}

set<char> findFirst(char nonTerminal, const vector<string>& productions) {
    set<char> firstSet;

    for (const string& production : productions) {
        if (production[0] == nonTerminal) {
            for (size_t i = 2; i < production.size(); i++) { 
                char symbol = production[i];

                if (!isupper(symbol)) { 
                    firstSet.insert(symbol);
                    break; 
                } else {
                    set<char> tempFirstSet = findFirst(symbol, productions);
                    firstSet.insert(tempFirstSet.begin(), tempFirstSet.end());

                    if (tempFirstSet.find('e') == tempFirstSet.end()) {
                        break; 
                    }
                }
            }
        }
    }

    for (const string& production : productions) {
        if (production[0] == nonTerminal && production.substr(2) == "e") {
            firstSet.insert('e');
        }
    }

    return firstSet;
}

set<char> findFollow(char nonTerminal, const vector<string>& productions, const set<char>& firstSet) {
    set<char> followSet;

    if (productions[0][0] == nonTerminal) {
        followSet.insert('$'); 
    }

    bool found = true;

    while (found) {
        found = false; 

        for (const string& production : productions) {
            for (size_t j = 2; j < production.size(); j++) { 
                if (production[j] == nonTerminal) {
                    if (j + 1 < production.size()) {
                        char nextSymbol = production[j + 1];

                        if (!isupper(nextSymbol)) {
                            followSet.insert(nextSymbol);
                        } else { 
                            set<char> tempFirstSet = findFirst(nextSymbol, productions);
                            followSet.insert(tempFirstSet.begin(), tempFirstSet.end());

                            if (tempFirstSet.find('e') != tempFirstSet.end()) {
                                followSet.erase('e'); 
                                found = true; 
                            }
                        }
                    } else {
                        found = true;
                        set<char> tempFollowSet = findFollow(production[0], productions, firstSet);
                        followSet.insert(tempFollowSet.begin(), tempFollowSet.end());
                    }
                }
            }
        }
    }

    return followSet;
}
