#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct SymbolTableEntry {
    std::string symbol;
    int address;
    bool defined;
};

struct LiteralTableEntry {
    std::string literal;
    int address;
};

struct PoolTableEntry {
    int literalIndex;
};

struct IncompleteInstruction {
    int instructionIndex;
    std::string symbol;
};

std::vector<SymbolTableEntry> symbolTable;
std::vector<LiteralTableEntry> literalTable;
std::vector<PoolTableEntry> poolTable;
std::vector<IncompleteInstruction> incompleteTable;

void addSymbol(const std::string& symbol) {
    for (auto& entry : symbolTable) {
        if (entry.symbol == symbol) {
            return;
        }
    }
    symbolTable.push_back({symbol, -1, false});
}

void addLiteral(const std::string& literal) {
    for (auto& entry : literalTable) {
        if (entry.literal == literal) {
            return;
        }
    }
    literalTable.push_back({literal, -1});
}

void addPool() {
    poolTable.push_back({(int)literalTable.size()});
}

void addIncomplete(int index, const std::string& symbol) {
    incompleteTable.push_back({index, symbol});
}

void processInstruction(const std::string& instruction, int address) {
    std::string operation, operand;
    size_t pos = instruction.find(' ');
    if (pos != std::string::npos) {
        operation = instruction.substr(0, pos);
        operand = instruction.substr(pos + 1);
    } else {
        operation = instruction;
    }

    if (operation == "LDA" || operation == "STA" || operation == "ADD" || operation == "SUB") {
        bool symbolFound = false;
        for (auto& entry : symbolTable) {
            if (entry.symbol == operand) {
                symbolFound = true;
                if (!entry.defined) {
                    addIncomplete(address, operand);
                }
                break;
            }
        }
        if (!symbolFound) {
            addSymbol(operand);
            addIncomplete(address, operand);
        }
    } else if (operation == "LTORG") {
        for (auto& literal : literalTable) {
            if (literal.address == -1) {
                literal.address = address++;
            }
        }
        addPool();
    } else if (operation == "END") {
        for (auto& literal : literalTable) {
            if (literal.address == -1) {
                literal.address = address++;
            }
        }
    }
}

void printSymbolTable() {
    std::cout << "\nSymbol Table:\n";
    std::cout << "Symbol\tAddress\tDefined\n";
    for (const auto& entry : symbolTable) {
        std::cout << entry.symbol << "\t" << entry.address << "\t" << (entry.defined ? "Yes" : "No") << "\n";
    }
}

void printLiteralTable() {
    std::cout << "\nLiteral Table:\n";
    std::cout << "Literal\tAddress\n";
    for (const auto& entry : literalTable) {
        std::cout << entry.literal << "\t" << entry.address << "\n";
    }
}

void printPoolTable() {
    std::cout << "\nPool Table:\n";
    std::cout << "Pool Start Index\n";
    for (const auto& entry : poolTable) {
        std::cout << entry.literalIndex << "\n";
    }
}

void printIncompleteTable() {
    std::cout << "\nTable of Incomplete Instructions:\n";
    std::cout << "Instruction Index\tSymbol\n";
    for (const auto& entry : incompleteTable) {
        std::cout << entry.instructionIndex << "\t\t" << entry.symbol << "\n";
    }
}

int main() {
    int address = 0;
    std::string line;
    std::cout << "Enter assembly instructions (type 'END' to finish input):\n";

    while (true) {
        std::getline(std::cin, line);
        if (line == "END") {
            processInstruction(line, address);
            break;
        }
        processInstruction(line, address++);
    }

    printSymbolTable();
    printLiteralTable();
    printPoolTable();
    printIncompleteTable();

    return 0;
}
