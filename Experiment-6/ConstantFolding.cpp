#include <iostream>

int main() {
    int a, b, c, d, result;

    // Get user input for all variables
    std::cout << "Enter a value for a: ";
    std::cin >> a;

    std::cout << "Enter a value for b: ";
    std::cin >> b;

    std::cout << "Enter a value for c: ";
    std::cin >> c;

    std::cout << "Enter a value for d: ";
    std::cin >> d;

    // Now perform constant folding calculations
    // Assuming constant folding expressions like: (a + b) * c - d

    // Evaluate expressions step by step for constant folding
    int sum_ab = a + b; // a + b -> constant folding at runtime
    int product = sum_ab * c; // (a + b) * c -> constant folding at runtime
    result = product - d; // ((a + b) * c) - d -> final result

    // Output the final result
    std::cout << "Result of the expression (a + b) * c - d: " << result << std::endl;

    return 0;
}
