#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

class RecursiveDescentParser {
    string input;
    int index;

public:
    RecursiveDescentParser(string str) : index(0) {
        str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
        input = str;
    }

    void match(char expected) {
        if (index < input.size() && input[index] == expected) {
            index++;
        } else {
            throw runtime_error(string("Expected '") + expected + "', found '" + (index < input.size() ? input[index] : '\0') + "'");
        }
    }

    int parseExpression() {
        int result = parseTerm();
        while (index < input.size() && input[index] == '+') {
            match('+');
            result += parseTerm();
        }
        return result;
    }

    int parseTerm() {
        int result = parseFactor();
        while (index < input.size() && input[index] == '*') {
            match('*');
            result *= parseFactor();
        }
        return result;
    }

    int parseFactor() {
        if (index < input.size() && isdigit(input[index])) {
            return parseNumber();
        } else if (index < input.size() && input[index] == '(') {
            match('(');
            int result = parseExpression();
            match(')');
            return result;
        } else {
            throw runtime_error(string("Unexpected character '") + (index < input.size() ? input[index] : '\0') + "'");
        }
    }

    int parseNumber() {
        int start = index;
        while (index < input.size() && isdigit(input[index])) index++;
        return stoi(input.substr(start, index - start));
    }

    void parse() {
        try {
            int result = parseExpression();
            if (index < input.size()) {
                throw runtime_error(string("Unexpected character at end: '") + input[index] + "'");
            }
            cout << "Parsed successfully! Result: " << result << endl;
        } catch (const runtime_error& e) {
            cerr << "Parsing error: " << e.what() << endl;
        }
    }
};

int main() {
    string input;
    cout << "Enter an arithmetic expression: ";
    getline(cin, input);

    RecursiveDescentParser parser(input);
    parser.parse();

    return 0;
}
