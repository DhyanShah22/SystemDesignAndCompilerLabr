#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of C keywords
const char *keywords[] = {
    "int", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "float", "double", "void", "static", "const", "sizeof", "switch",
    "case", "default", "struct", "union", "typedef", "enum", "extern", "volatile", "main"
};
const int keywordCount = 26;

int isKeyword(const char *str) {
    for (int i = 0; i < keywordCount; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isDelimiter(char ch) {
    return ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || 
           ch == ';' || ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' || 
           ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '&' || ch == '|';
}

int isSymbol(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ',' || ch == ';' || 
           ch == '>' || ch == '<' || ch == '=' || ch == '(' || ch == ')' || ch == '[' || 
           ch == ']' || ch == '{' || ch == '}' || ch == '&' || ch == '|';
}

int isValidIdentifierChar(char ch) {
    return isalnum(ch) || ch == '_';
}

int isIdentifier(const char *str) {
    if (!isalpha(str[0]) && str[0] != '_') {
        return 0;
    }
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return 0;
        }
    }
    return !isKeyword(str); // It should not be a keyword
}

int isNumber(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

void identifyTokens(const char *str) {
    int length = strlen(str);
    char buffer[256]; // Buffer to store the current token
    int bufferIndex = 0;

    for (int i = 0; i < length; i++) {
        char ch = str[i];

        if (isDelimiter(ch)) {
            // If buffer is not empty, check the buffer
            if (bufferIndex != 0) {
                buffer[bufferIndex] = '\0';
                bufferIndex = 0;

                if (isKeyword(buffer)) {
                    printf("%s: Keyword\n", buffer);
                } else if (isNumber(buffer)) {
                    printf("%s: Number\n", buffer);
                } else if (isIdentifier(buffer)) {
                    printf("%s: Identifier\n", buffer);
                } else {
                    printf("%s: Unknown\n", buffer);
                }
            }

            if (!isspace(ch)) {
                if (isSymbol(ch)) {
                    printf("%c: Symbol\n", ch);
                } else {
                    printf("%c: Delimiter\n", ch); // Print delimiter as other
                }
            }
        } else {
            // Add character to buffer
            buffer[bufferIndex++] = ch;
        }
    }

    // Check the last buffer content if not empty
    if (bufferIndex != 0) {
        buffer[bufferIndex] = '\0';
        if (isKeyword(buffer)) {
            printf("%s: Keyword\n", buffer);
        } else if (isNumber(buffer)) {
            printf("%s: Number\n", buffer);
        } else if (isIdentifier(buffer)) {
            printf("%s: Identifier\n", buffer);
        } else {
            printf("%s: Unknown\n", buffer);
        }
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    // Remove the trailing newline character, if any
    str[strcspn(str, "\n")] = 0;
    identifyTokens(str);
    return 0;
}
