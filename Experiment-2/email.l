%option noyywrap
%{
#include <stdio.h>
%}

%%
[0-9]{10}                { printf("Valid Contact: %s\n", yytext); }
[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,} { printf("Valid Email: %s\n", yytext); }
[a-zA-Z0-9@#$%^&+=]{8,}  { printf("Valid Password: %s\n", yytext); }
.                        { /* Ignore any other characters */ }
%%

int main() {
    printf("Enter your input (contact, email, or password):\n");
    yylex();
    return 0;
}