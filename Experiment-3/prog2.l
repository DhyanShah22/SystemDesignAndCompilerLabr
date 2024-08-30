%{
#include <stdio.h>

int char_count = 0;
int word_count = 0;
int line_count = 0;
int in_word = 0;

void count_word() {
    if (in_word) {
        word_count++;
        in_word = 0;
    }
}
%}

%option noyywrap

%%

[^ \t\n]     { char_count++; in_word = 1; }
[ \t]        { count_word(); }
\n           { count_word(); line_count++; char_count++; }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *infile = fopen(argv[1], "r");
        if (!infile) {
            printf("Error opening file: %s\n", argv[1]);
            return 1;
        }

        yyin = infile;

        yylex();

        fclose(infile);

        // Print the counts
        printf("Characters: %d\n", char_count);
        printf("Words: %d\n", word_count);
        printf("Lines: %d\n", line_count);
    } else {
        printf("Usage: %s <input file>\n", argv[0]);
    }

    return 0;
}
