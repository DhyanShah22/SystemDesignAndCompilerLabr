// E  → T E'
// E' → + T E' | - T E' | ε
// T  → F T'
// T' → * F T' | / F T' | ε
// F  → i | ( E )

#include<iostream>
#include<string>

using namespace std;

const char* pointer;

int E(), F(), Tdash(), Edash(), T();

int F() {
    if (*pointer == 'i') {
        cout << "i parsed" << endl;
        pointer++;
        return 1; // Success
    } else if (*pointer == '(') {
        cout << "( parsed" << endl;
        pointer++;
        if (E()) {
            cout << "E parsed" << endl;
            if (*pointer == ')') {
                cout << ") parsed" << endl;
                pointer++;
                return 1; // Success
            } else {
                return 0; // Failure
            }
        } else {
            return 0; // Failure
        }
    } else {
        return 0; // Failure
    }
}

int Tdash() {
    if (*pointer == '*' || *pointer == '/') {
        cout << "* or / parsed" << endl;
        pointer++;
        if (F()) {
            cout << "F parsed" << endl;
            if (Tdash()) {
                cout << "Tdash parsed" << endl;
                return 1; // Success
            } else {
                return 0; // Failure
            }
        } else {
            return 0; // Failure
        }
    } else if (*pointer == '\0') {
        return 1; // Success (ε transition)
    } else {
        return 1; // Success (do nothing, valid for ε)
    }
}

int T() {
    if (F()) {
        cout << "F parsed" << endl;
        if (Tdash()) {
            cout << "Tdash parsed" << endl;
            return 1; // Success
        } else {
            return 0; // Failure
        }
    } else {
        return 0; // Failure
    }
}

int Edash() {
    if (*pointer == '+' || *pointer == '-') {
        cout << "+ or - parsed" << endl;
        pointer++;
        if (T()) {
            cout << "T parsed" << endl;
            if (Edash()) {
                cout << "Edash parsed" << endl;
                return 1; // Success
            } else {
                return 0; // Failure
            }
        } else {
            return 0; // Failure
        }
    } else if (*pointer == '\0') {
        return 1; // Success (ε transition)
    } else {
        return 1; // Success (do nothing, valid for ε)
    }
}

int E() {
    if (T()) {
        cout << "T parsed" << endl;
        if (Edash()) {
            cout << "Edash parsed" << endl;
            return 1; // Success
        } else {
            return 0; // Failure
        }
    } else {
        return 0; // Failure
    }
}

int main() {
    string str;
    cout << "Enter a string: ";
    cin >> str;
    pointer = str.c_str();
    if (E() && *pointer == '\0') {
        cout << "String is successfully parsed" << endl;
    } else {
        cout << "String is not successfully parsed" << endl;
    }
    return 0;
}


// i*(i+i) no 
// i+i*i yes