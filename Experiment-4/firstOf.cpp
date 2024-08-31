#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

void FIRST(char[], char, bool[]);
void addToResultSet(char[], char);

int numOfProductions;
char productionSet[10][10];

int main() {
    cout << "How many number of productions? : ";
    cin >> numOfProductions;

    for (int i = 0; i < numOfProductions; i++) {
        cout << "Enter production Number " << i + 1 << ": ";
        cin >> productionSet[i];
    }

    char choice;
    do {
        char c;
        char result[20] = { '\0' }; 
        bool visited[26] = { false }; 
        cout << "\nFind the FIRST of: ";
        cin >> c;
        FIRST(result, c, visited);
        cout << "\nFIRST(" << c << ") = { ";
        for (int i = 0; result[i] != '\0'; i++)
            cout << " " << result[i] << " ";
        cout << "}\n";
        cout << "Press 'y' to continue: ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    return 0;
}

void FIRST(char* Result, char c, bool visited[]) {
    char subResult[20] = { '\0' }; 

    if (!isupper(c)) {
        addToResultSet(Result, c);
        return;
    }

    if (visited[c - 'A']) return;

    visited[c - 'A'] = true;

    for (int i = 0; i < numOfProductions; i++) {
        if (productionSet[i][0] == c) { 
            if (productionSet[i][2] == '$') { 
                addToResultSet(Result, '$');
            } else {
                int j = 2;
                while (productionSet[i][j] != '\0') {
                    subResult[0] = '\0'; 
                    FIRST(subResult, productionSet[i][j], visited); 

                    for (int k = 0; subResult[k] != '\0'; k++)
                        addToResultSet(Result, subResult[k]);

                    bool foundEpsilon = false;
                    for (int k = 0; subResult[k] != '\0'; k++) {
                        if (subResult[k] == '$') {
                            foundEpsilon = true;
                            break;
                        }
                    }

                    if (!foundEpsilon)
                        break;

                    j++;
                }
            }
        }
    }

    visited[c - 'A'] = false;
}

void addToResultSet(char Result[], char val) {
    int k;
    for (k = 0; Result[k] != '\0'; k++) {
        if (Result[k] == val) 
            return;
    }
    Result[k] = val;
    Result[k + 1] = '\0'; 
}
