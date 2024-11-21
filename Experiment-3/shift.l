%option noyywrap
%{
#include<stdio.h>
#include<string.h>
FILE *inputfile, *outputfile;
int vowel_count = 0, cons_count = 0;

int is_vowel(char c) {
    return strchr("aeiouAEIOU", c) != NULL;
}

void process_word(char *word) {
    char temp = word[0];
    int len = strlen(word);
    memmove(word, word + 1, len - 1);
    word[len - 1] = temp;
    word[len] = is_vowel(temp) ? '#' : '$';
    word[len + 1] = '\0';
}
%}

%%
[a-zA-Z]+ {
    for (int i = 0; yytext[i] != '\0'; i++) {
        is_vowel(yytext[i]) ? vowel_count++ : cons_count++;
    }
    char word[100];
    strncpy(word, yytext, sizeof(word) - 1);
    word[sizeof(word) - 1] = '\0';
    process_word(word);
    fprintf(outputfile, "%s ", word);
}
%%
int main() {
    inputfile = fopen("input.txt", "r");
    outputfile = fopen("output.txt", "w");
    if (!inputfile || !outputfile) return 1;

    yyin = inputfile;
    yylex();

    fclose(inputfile);
    fclose(outputfile);

    printf("No. of vowels: %d\n", vowel_count);
    printf("No. of consonants: %d\n", cons_count);
    return 0;
}
