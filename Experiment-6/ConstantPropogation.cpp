#include <iostream>

int main() {
    int a, x, y, z;

    // Get user input for all variables
    std::cout << "Enter a value for a: ";
    std::cin >> a;

    std::cout << "Enter a value for x (will be added to a): ";
    std::cin >> x;

    std::cout << "Enter a value for y (will be multiplied by x): ";
    std::cin >> y;

    std::cout << "Enter a value for z (will be subtracted by y): ";
    std::cin >> z;

    // Calculate based on user inputs
    int result_x = a + x;
    int result_y = result_x * y;
    int result_z = result_y - z;

    // Output results
    std::cout << "Result of the calculations: " << std::endl;
    std::cout << "x (a + x) = " << result_x << std::endl;
    std::cout << "y (x * y) = " << result_y << std::endl;
    std::cout << "z (y - z) = " << result_z << std::endl;

    return 0;
}
