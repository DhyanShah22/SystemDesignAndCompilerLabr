#include <iostream>
#include <string>
#include <cctype>
#include <algorithm> 

class RecursiveDescentParser {
    std::string input;
    int index;

public:
    RecursiveDescentParser(std::string str) : index(0) {
        str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
        input = str;
    }

    char peek() {
        return index < input.size() ? input[index] : '\0';
    }

    char get() {
        return input[index++];
    }

    void match(char expected) {
        if (peek() == expected) {
            get();
        } else {
            throw std::runtime_error(std::string("Expected '") + expected + "', found '" + peek() + "'");
        }
    }

    int parseExpression() {
        int result = parseTerm();
        while (peek() == '+') {
            match('+');
            result += parseTerm();
        }
        return result;
    }

    int parseTerm() {
        int result = parseFactor();
        while (peek() == '*') {
            match('*');
            result *= parseFactor();
        }
        return result;
    }

    int parseFactor() {
        if (std::isdigit(peek())) {
            return parseNumber();
        } else if (peek() == '(') {
            match('(');
            int result = parseExpression();
            match(')');
            return result;
        } else {
            throw std::runtime_error(std::string("Unexpected character '") + peek() + "'");
        }
    }

    int parseNumber() {
        int start = index;
        while (std::isdigit(peek())) get();
        return std::stoi(input.substr(start, index - start));
    }

    void parse() {
        try {
            int result = parseExpression();
            if (peek() != '\0') {
                throw std::runtime_error(std::string("Unexpected character at end: '") + peek() + "'");
            }
            std::cout << "Parsed successfully! Result: " << result << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "Parsing error: " << e.what() << std::endl;
        }
    }
};

int main() {
    std::string input;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, input);

    RecursiveDescentParser parser(input);
    parser.parse();

    return 0;
}
