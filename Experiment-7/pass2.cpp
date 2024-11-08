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

struct MachineCode {
    int LC;
    string opcode;
    string operand1;
    string operand2;
};

map<string, Symbol> SYMTAB;
vector<Literal> LITTAB;
vector<Pool> POOLTAB;
map<string, pair<string, int>> OPTAB = {
    {"MOVER", {"04", 1}},
    {"MOVEM", {"05", 1}},
    {"ADD", {"01", 1}},
    {"SUB", {"02", 1}},
    {"MULT", {"03", 1}},
    {"DIV", {"04", 1}}
};

map<string, string> REGTAB = {
    {"AREG", "01"},
    {"BREG", "02"},
    {"CREG", "03"},
    {"DREG", "04"}
};

vector<MachineCode> intermediateCode;
int LC = 0;

void loadSymbolTable(const string& filename) {
    ifstream file(filename);
    string name;
    int address, length;
    
    while (file >> name >> address >> length) {
        SYMTAB[name] = {name, address, length};
    }
    file.close();
}

void loadLiteralTable(const string& filename) {
    ifstream file(filename);
    string literal;
    int address;
    
    while (file >> literal >> address) {
        LITTAB.push_back({literal, address});
    }
    file.close();
}

string getOperandCode(const string& operand) {
    if (REGTAB.find(operand) != REGTAB.end()) {
        return REGTAB[operand];
    }
    
    if (operand[0] == '=') {
        for (size_t i = 0; i < LITTAB.size(); i++) {
            if (LITTAB[i].literal == operand) {
                return "L" + to_string(i);
            }
        }
    }
    
    if (SYMTAB.find(operand) != SYMTAB.end()) {
        return "S" + to_string(SYMTAB[operand].address);
    }
    
    return operand; 
}

void generateMachineCode(const string& filename) {
    ifstream input(filename);
    ofstream output("machine_code.txt");
    string line;
    
    while (getline(input, line)) {
        vector<string> tokens;
        stringstream ss(line);
        string token;
        
        while (ss >> token) {
            if (token.back() == ',')
                token = token.substr(0, token.size()-1);
            tokens.push_back(token);
        }
        
        if (tokens.empty()) continue;
        
        if (tokens[0] == "START") {
            LC = stoi(tokens[1]);
            output << LC << " -- --" << endl;
        }
        else if (tokens[0] == "END" || tokens[0] == "LTORG") {
            output << LC << " -- --" << endl;
        }
        else {
            int startIdx = 0;
            if (tokens[0].back() == ':') startIdx = 1;
            
            if (OPTAB.find(tokens[startIdx]) != OPTAB.end()) {
                string opcode = OPTAB[tokens[startIdx]].first;
                string operand1 = getOperandCode(tokens[startIdx + 1]);
                string operand2 = (tokens.size() > startIdx + 2) ? 
                                 getOperandCode(tokens[startIdx + 2]) : "--";
                
                output << LC << " " << opcode << " " << operand1 << " " << operand2 << endl;
                LC++;
            }
        }
    }
    
    input.close();
    output.close();
}

int main() {
    loadSymbolTable("symtab.txt");
    loadLiteralTable("littab.txt");
    
    generateMachineCode("input.txt");
    
    cout << "Machine code generation completed.\n";
    return 0;
}