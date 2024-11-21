%option noyywrap

%{
#include <stdio.h>

FILE *inputfile, *positivefile, *negativefile;
%}

%%

[-]?[0-9]+(\.[0-9]+)? {
    if (yytext[0] == '-') {
        fprintf(negativefile, "%s\n", yytext); 
    } else {
        fprintf(positivefile, "%s\n", yytext); 
    }
}
. ; 

%%

int main() {
    inputfile = fopen("input.txt", "r");
    positivefile = fopen("positive_numbers.txt", "w");
    negativefile = fopen("negative_numbers.txt", "w");

    if (!inputfile) {
        printf("Error opening input file.\n");
        return 1;
    }
    if (!positivefile || !negativefile) {
        printf("Error opening output files.\n");
        return 1;
    }

    yyin = inputfile;
    yylex();

    fclose(inputfile);
    fclose(positivefile);
    fclose(negativefile);

    printf("Processing complete. Check positive_numbers.txt and negative_numbers.txt for results.\n");
    return 0;
}
