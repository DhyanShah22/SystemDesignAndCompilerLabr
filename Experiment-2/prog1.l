%{
    #include <stdio.h>
    int keywordCount = 0;
    int identifierCount = 0;
    int numberCount = 0;
    int symbolCount = 0;
%}

%%

"int"|"for"|"if"|"while"      { keywordCount++; printf("%s: Keyword\n", yytext); }
[0-9]+(\.[0-9]+)?             { numberCount++; printf("%s: Number\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*        { identifierCount++; printf("%s: Identifier\n", yytext); }
"+"|"-"|"*"|"/"|"="|">"|"<"|"!"|"&"|"|"|";"|","|"."|"("|")"|"{"|"}"|"["|"]"   { symbolCount++; printf("%s: Symbol\n", yytext); }
[ \t\n]+                      { /* Ignore whitespace */ }
.                             { printf("%s: Unknown\n", yytext); }

%%

int main() {
    yylex();
    printf("Summary:\n");
    printf("Keywords: %d\n", keywordCount);
    printf("Identifiers: %d\n", identifierCount);
    printf("Numbers: %d\n", numberCount);
    printf("Symbols: %d\n", symbolCount);
    return 0;
}

int yywrap() {
    return 1;
}
