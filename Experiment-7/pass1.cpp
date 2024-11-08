#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;

struct Symbol {
    string name;
    int address;
    int length;
};

struct Literal {
    string literal;
    int address;
};

struct Pool {
    int firstLiteral;
    int literalCount;
};

map<string, Symbol> SYMTAB;
vector<Literal> LITTAB;
vector<Pool> POOLTAB;
map<string, int> OPTAB = {
    {"START", 1}, {"MOVER", 1}, {"MOVEM", 1}, 
    {"LTORG", 1}, {"END", 1}
};

int LC = 0;
int poolPtr = 0;

void initializePoolTable() {
    POOLTAB.push_back({(int)LITTAB.size(), 0});
    cout << "Initialized Pool Table\n";
}

void addSymbol(const string& label) {
    if (SYMTAB.find(label) == SYMTAB.end()) {
        SYMTAB[label] = {label, LC, 1};
        cout << "Added symbol: " << label << " at address " << LC << endl;
    } else {
        SYMTAB[label].address = LC;  // Update address if symbol exists
        cout << "Updated symbol: " << label << " at address " << LC << endl;
    }
}

bool isLiteral(const string& token) {
    return token.size() > 2 && token[0] == '=' && token[1] == '\'';
}

void addLiteral(const string& literal) {
    int poolStart = POOLTAB[poolPtr].firstLiteral;
    int poolEnd = poolStart + POOLTAB[poolPtr].literalCount;
    
    for (int i = poolStart; i < poolEnd; i++) {
        if (LITTAB[i].literal == literal) {
            cout << "Literal " << literal << " already exists in current pool\n";
            return;
        }
    }

    LITTAB.push_back({literal, -1});
    POOLTAB[poolPtr].literalCount++;
    cout << "Added literal: " << literal << endl;
}

void processLiterals() {
    cout << "Processing literals in current pool...\n";
    int poolStart = POOLTAB[poolPtr].firstLiteral;
    int poolEnd = poolStart + POOLTAB[poolPtr].literalCount;
    
    for (int i = poolStart; i < poolEnd; i++) {
        if (LITTAB[i].address == -1) {
            LITTAB[i].address = LC++;
            cout << "Assigned address " << LITTAB[i].address << " to literal " << LITTAB[i].literal << endl;
        }
    }
    
    poolPtr++;
    POOLTAB.push_back({(int)LITTAB.size(), 0});
}

void processStatement(const vector<string>& tokens) {
    if (tokens.empty()) return;
    
    cout << "\nProcessing line tokens: ";
    for (const string& token : tokens) cout << token << " ";
    cout << endl;

    string firstToken = tokens[0];
    int startIdx = 0;
    if (firstToken.back() == ':') {
        string label = firstToken.substr(0, firstToken.size() - 1);
        addSymbol(label);
        startIdx = 1;
        if (tokens.size() == 1) return;
    }

    string opcode = tokens[startIdx];
    if (opcode == "START") {
        LC = stoi(tokens[startIdx + 1]);
        cout << "LC initialized to " << LC << endl;
    }
    else if (opcode == "LTORG" || opcode == "END") {
        processLiterals();
    }
    else if (OPTAB.find(opcode) != OPTAB.end()) {
        LC++;
        
        for (size_t i = startIdx + 1; i < tokens.size(); i++) {
            string token = tokens[i];
            if (token.find('=') != string::npos) {
                addLiteral(token);
            }
        }
    }
}

void loadProgram(const string& filename) {
    ifstream input(filename);
    string line;
    
    while (getline(input, line)) {
        vector<string> tokens;
        stringstream ss(line);
        string token;
        
        while (ss >> token) {
            size_t pos = token.find(',');
            if (pos != string::npos) {
                string first = token.substr(0, pos);
                string second = token.substr(pos + 1);
                if (!first.empty()) tokens.push_back(first);
                if (!second.empty()) tokens.push_back(second);
            } else {
                tokens.push_back(token);
            }
        }
        
        if (!tokens.empty()) {
            processStatement(tokens);
        }
    }
    input.close();
}

void displayTables() {
    cout << "\nSymbol Table (SYMTAB):\n";
    for (const auto& entry : SYMTAB) {
        cout << entry.first << "\t" << entry.second.address << "\t" << entry.second.length << endl;
    }

    cout << "\nLiteral Table (LITTAB):\n";
    for (const auto& literal : LITTAB) {
        cout << literal.literal << "\t" << literal.address << endl;
    }

    cout << "\nPool Table (POOLTAB):\n";
    for (size_t i = 0; i < POOLTAB.size(); i++) {
        cout << "Pool " << i + 1 << ": First Literal = " << POOLTAB[i].firstLiteral 
             << ", Number of Literals = " << POOLTAB[i].literalCount << endl;
    }
}

int main() {
    initializePoolTable();
    loadProgram("input.txt");
    displayTables();
    return 0;
}