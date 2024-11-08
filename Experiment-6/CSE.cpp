#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, int> variables;
    std::unordered_map<std::string, int> subexpressions; 
    int result;

    std::cout << "Enter initial values for variables (e.g., a = 5, x = 3, etc.). Type 'done' to finish:\n";

    while (true) {
        std::string var;
        int value;
        std::cout << "Variable name (or 'done' to finish): ";
        std::cin >> var;
        if (var == "done") break;
        
        std::cout << "Enter value for " << var << ": ";
        std::cin >> value;
        variables[var] = value;
    }

    std::cout << "\nEnter Three-Address Code operations (e.g., t1 = a + x). Type 'done' to finish:\n";

    while (true) {
        std::string resultVar, op1, op, op2;
        std::cout << "Enter operation (or 'done' to finish): ";
        std::cin >> resultVar;

        if (resultVar == "done") break;

        std::cin.ignore();
        std::cout << "Enter the operation in the format '<resultVar> = <op1> <operator> <op2>': ";
        std::cin >> op1 >> op >> op2;

        std::string expression = op1 + " " + op + " " + op2;

        if (subexpressions.find(expression) != subexpressions.end()) {
            variables[resultVar] = subexpressions[expression];
            std::cout << "Using cached result for " << resultVar << " = " << subexpressions[expression] << std::endl;
        } else {
            if (op == "+") {
                subexpressions[expression] = variables[op1] + variables[op2];
            } else if (op == "-") {
                subexpressions[expression] = variables[op1] - variables[op2];
            } else if (op == "*") {
                subexpressions[expression] = variables[op1] * variables[op2];
            } else if (op == "/") {
                if (variables[op2] == 0) {
                    std::cerr << "Error: Division by zero." << std::endl;
                    continue;
                }
                subexpressions[expression] = variables[op1] / variables[op2];
            } else {
                std::cerr << "Invalid operator. Only +, -, *, / are supported." << std::endl;
                continue;
            }
            variables[resultVar] = subexpressions[expression];
            std::cout << "Computed and cached result for " << resultVar << " = " << variables[resultVar] << std::endl;
        }
    }

    std::cout << "\nFinal variable values:\n";
    for (const auto& [key, value] : variables) {
        std::cout << key << " = " << value << std::endl;
    }

    return 0;
}


// Variable name (or 'done' to finish): a
// Enter value for a: 5
// Variable name (or 'done' to finish): x
// Enter value for x: 3
// Variable name (or 'done' to finish): done

// Enter operation (or 'done' to finish): t1
// Enter the operation in the format '<resultVar> = <op1> <operator> <op2>': a + x
// Result of t1 = 8

// Enter operation (or 'done' to finish): t2
// Enter the operation in the format '<resultVar> = <op1> <operator> <op2>': t1 * x
// Result of t2 = 24

// Enter operation (or 'done' to finish): done
