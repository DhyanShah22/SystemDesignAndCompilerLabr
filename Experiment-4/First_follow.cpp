#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

bool isNonTerminal(char c) {
    return isupper(c);
}

void addToSet(char set[], char element) {
    if (strchr(set, element) == NULL) {
        int length = strlen(set);
        set[length] = element;
        set[length + 1] = '\0';
    }
}

void findFirst(char first[], char productions[][10], char nonTerminal) {
    for (int i = 0; i < 10; i++) {
        if (productions[i][0] == nonTerminal) {
            char* production = productions[i] + 2;  // Skip the non-terminal and the '='

            if (production[0] == '\0') continue; // Skip empty productions

            for (int j = 0; production[j] != '\0'; j++) {
                if (production[j] == '/') continue; // Handle alternatives
                if (!isNonTerminal(production[j])) {
                    // Add terminal to First set
                    addToSet(first, production[j]);
                    break;
                } else {
                    // Recursively find First of the next non-terminal
                    char temp[10] = "";
                    findFirst(temp, productions, production[j]);
                    for (int k = 0; temp[k] != '\0'; k++) {
                        if (temp[k] != 'e') { // Use 'e' to represent epsilon
                            addToSet(first, temp[k]);
                        }
                    }
                    if (strchr(temp, 'e') == NULL) {
                        break;
                    }
                }
            }
        }
    }
}

void findFollow(char follow[], char productions[][10], char nonTerminal) {
    if (nonTerminal == productions[0][0]) {
        addToSet(follow, '$'); // Add '$' to the Follow of the start symbol
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 2; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == nonTerminal) {
                if (productions[i][j + 1] != '\0') {
                    char temp[10] = "";
                    findFirst(temp, productions, productions[i][j + 1]);
                    for (int k = 0; temp[k] != '\0'; k++) {
                        if (temp[k] != 'e') { // Ignore epsilon in First set
                            addToSet(follow, temp[k]);
                        }
                    }
                    if (strchr(temp, 'e') != NULL) {
                        // Add Follow of the left-hand non-terminal if epsilon is present
                        char tempFollow[10] = "";
                        findFollow(tempFollow, productions, productions[i][0]);
                        for (int k = 0; tempFollow[k] != '\0'; k++) {
                            addToSet(follow, tempFollow[k]);
                        }
                    }
                } else {
                    // If at the end, add Follow of the LHS non-terminal
                    char tempFollow[10] = "";
                    findFollow(tempFollow, productions, productions[i][0]);
                    for (int k = 0; tempFollow[k] != '\0'; k++) {
                        addToSet(follow, tempFollow[k]);
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    char productions[10][10], nonTerminal[10], first[10] = "", follow[10] = "";

    cout << "Enter the number of production rules: ";
    cin >> n;

    cout << "Enter the production rules (e.g., S=abAB/bB):\n";
    for (int i = 0; i < n; i++) {
        cin >> productions[i];
    }

    cout << "Enter the non-terminal to find the First and Follow sets: ";
    cin >> nonTerminal;

    findFirst(first, productions, nonTerminal[0]);
    findFollow(follow, productions, nonTerminal[0]);

    cout << "First(" << nonTerminal[0] << ") =  ";
    for (int i = 0; first[i] != '\0'; i++) {
        cout << first[i] << " ";
    }
    cout << "\n";

    cout << "Follow(" << nonTerminal[0] << ") =  ";
    for (int i = 0; follow[i] != '\0'; i++) {
        cout << follow[i] << " ";
    }
    cout << "\n";

    return 0;
}
