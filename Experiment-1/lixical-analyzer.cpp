#include <iostream>
#include <cstring>
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
    return isspace(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' 
           || ch == ';' || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' 
           || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '&' || ch == '|';
}

bool isSymbol(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || ch == ';' 
           || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == '[' 
           || ch == ']' || ch == '{' || ch == '}' || ch == '&' || ch == '|';
}

bool isValidIdentifierChar(char ch) {
    return std::isalnum(ch) || ch == '_';
}

bool isIdentifier(const std::string& str) {
    if (!std::isalpha(str[0]) && str[0] != '_') {
        return false;
    }
    for (char ch : str) {
        if (!isValidIdentifierChar(ch)) {
            return false;
        }
    }
    return !isKeyword(str); 
}

bool isNumber(const std::string& str) {
    for (char ch : str) {
        if (!std::isdigit(ch)) {
            return false;
        }
    }
    return true;
}

void identifyTokens(const std::string& str) {
    int length = str.length();
    std::string buffer;

    for (int i = 0; i < length; i++) {
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
                    std::cout << buffer << ": Unknown\n";
                }
                buffer.clear();
            }

            if (!isspace(ch)) {
                if (isSymbol(ch)) {
                    std::cout << ch << ": Symbol\n";
                } else {
                    std::cout << ch << ": Other\n"; // Print delimiter as other
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
            std::cout << buffer << ": Unknown\n";
        }
    }
}

int main() {
    std::string str;
    std::cout << "Enter a string: ";
    std::getline(std::cin, str);
    identifyTokens(str);
    return 0;
}
