%{
#include <stdio.h>
#include <ctype.h>

int keyword_count = 0;
int identifier_count = 0;
int number_count = 0;
int blank_count = 0;
int tab_count = 0;
int newline_count = 0;

void print_token(const char* token_name, const char* lexeme) {
    printf("%s: %s (Length: %d)\n", token_name, lexeme, (int)strlen(lexeme));
}
%}

%option noyywrap

%%
"if"|"else"|"for"|"while"|"int"|"float"|"char" {
    keyword_count++;
    print_token("Keyword", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    identifier_count++;
    print_token("Identifier", yytext);
}

[0-9]+ {
    number_count++;
    print_token("Number", yytext);
}

[ \t]+ {
    int i;
    for(i = 0; i < yyleng; i++) {
        if(yytext[i] == ' ') blank_count++;
        else if(yytext[i] == '\t') tab_count++;
    }
}

\n {
    newline_count++;
}

. ; // Ignore any other characters

%%

int main() {
    yylex();
    printf("\nSummary:\n");
    printf("Keywords: %d\n", keyword_count);
    printf("Identifiers: %d\n", identifier_count);
    printf("Numbers: %d\n", number_count);
    printf("Blanks: %d\n", blank_count);
    printf("Tabs: %d\n", tab_count);
    printf("Newlines: %d\n", newline_count);
    return 0;
}
