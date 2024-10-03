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
    cin.ignore(); // To ignore the newline character after the integer input
    for (int i = 0; i < n; i++) {
        string production;
        getline(cin, production);
        productions.push_back(production);
    }

    char nonTerminal;
    cout << "Enter the non-terminal to find the First and Follow sets: ";
    cin >> nonTerminal;

    // Finding First set
    set<char> firstSet = findFirst(nonTerminal, productions);
    cout << "First(" << nonTerminal << ") = ";
    for (char c : firstSet) {
        cout << c << " ";
    }
    cout << endl;

    // Finding Follow set
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
            for (size_t i = 2; i < production.size(); i++) { // Skip non-terminal and '='
                char symbol = production[i];

                if (!isupper(symbol)) { // Terminal
                    firstSet.insert(symbol);
                    break; // Only add the first terminal
                } else {
                    // Recursion is eliminated; use a loop
                    set<char> tempFirstSet = findFirst(symbol, productions);
                    firstSet.insert(tempFirstSet.begin(), tempFirstSet.end());

                    if (tempFirstSet.find('e') == tempFirstSet.end()) {
                        break; // Stop if epsilon not found
                    }
                }
            }
        }
    }

    // Add epsilon to the First set if applicable
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
        followSet.insert('$'); // Start symbol follows $
    }

    bool found = true;

    while (found) {
        found = false; // Reset flag for this iteration

        for (const string& production : productions) {
            for (size_t j = 2; j < production.size(); j++) { // Skip non-terminal and '='
                if (production[j] == nonTerminal) {
                    // Lookahead symbol
                    if (j + 1 < production.size()) {
                        char nextSymbol = production[j + 1];

                        if (!isupper(nextSymbol)) { // If it's terminal
                            followSet.insert(nextSymbol);
                        } else { // If it's non-terminal
                            set<char> tempFirstSet = findFirst(nextSymbol, productions);
                            followSet.insert(tempFirstSet.begin(), tempFirstSet.end());

                            // Remove epsilon if present
                            if (tempFirstSet.find('e') != tempFirstSet.end()) {
                                followSet.erase('e'); // Remove epsilon from follow set
                                found = true; // Mark that we found a new follow
                            }
                        }
                    } else {
                        // At the end of production
                        found = true; // Flag for another pass
                        set<char> tempFollowSet = findFollow(production[0], productions, firstSet);
                        followSet.insert(tempFollowSet.begin(), tempFollowSet.end());
                    }
                }
            }
        }
    }

    return followSet;
}
