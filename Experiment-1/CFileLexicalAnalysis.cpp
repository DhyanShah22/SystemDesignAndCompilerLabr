#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

const std::string keywords[] = {
    "int", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "float", "double", "void", "static", "const", "sizeof", "switch",
    "case", "default", "struct", "union", "typedef", "enum", "extern", "volatile", "main"
};
const int keywordCount = sizeof(keywords) / sizeof(keywords[0]);

bool isKeyword(const std::string& str) {
    for (int i = 0; i < keywordCount; i++) {
        if (str == keywords[i]) {
            return true;
        }
    }
    return false;
}

bool isDelimiter(char ch) {
    return ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' ||
           ch == ';' || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
           ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '&' || ch == '|';
}

bool isSymbol(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || ch == ';' ||
           ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == '[' ||
           ch == ']' || ch == '{' || ch == '}' || ch == '&' || ch == '|';
}

bool isIdentifier(const std::string& str) {
    if (!std::isalpha(str[0]) && str[0] != '_') {
        return false;
    }
    for (size_t i = 1; i < str.length(); i++) {
        if (!std::isalnum(str[i]) && str[i] != '_') {
            return false;
        }
    }
    return !isKeyword(str); 
}

bool isNumber(const std::string& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

void identifyTokens(const std::string& str) {
    size_t length = str.length();
    std::string buffer;

    for (size_t i = 0; i < length; i++) {
        char ch = str[i];

        if (isDelimiter(ch)) {
            if (!buffer.empty()) {
                if (isKeyword(buffer)) {
                    std::cout << buffer << ": Keyword\n";
                } else if (isNumber(buffer)) {
                    std::cout << buffer << ": Number\n";
                } else if (isIdentifier(buffer)) {
                    std::cout << buffer << ": Identifier\n";
                } else {
                    std::cout << buffer << ": Others\n";
                }
                buffer.clear();
            }

            if (!isspace(ch)) {
                if (isSymbol(ch)) {
                    std::cout << ch << ": Symbol\n";
                } else {
                    std::cout << ch << ": Delimiter\n";
                }
            }
        } else {
            buffer += ch;
        }
    }

    if (!buffer.empty()) {
        if (isKeyword(buffer)) {
            std::cout << buffer << ": Keyword\n";
        } else if (isNumber(buffer)) {
            std::cout << buffer << ": Number\n";
        } else if (isIdentifier(buffer)) {
            std::cout << buffer << ": Identifier\n";
        } else {
            std::cout << buffer << ": Others\n";
        }
    }
}

int main() {
    std::ifstream file;
    std::string filename, line;

    std::cout << "Enter the filename: ";
    std::cin >> filename;

    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    while (std::getline(file, line)) {
        identifyTokens(line);
    }

    file.close();
    return 0;
}
