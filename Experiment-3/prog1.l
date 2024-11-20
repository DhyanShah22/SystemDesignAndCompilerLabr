%option noyywrap

%{
#include<stdio.h>    
%}

%%

\/\/[^\n]* ;
\/\*([^*]|\*+[^\/])*\*\/ ;
.                           {fputc(yytext[0], yyout);}
\n                          {fputc('\n', yyout);}

%%

int main(int argc, char **argv){
    if(argc>2){
        FILE *infile = fopen(argv[1], "r");
        FILE *outfile = fopen(argv[2], "w");
        if (!infile || !outfile) {
            printf("Error opening files.\n");
            return 1;
        }

        yyin = infile;
        yyout = outfile;
        yylex();

        fclose(infile);
        fclose(outfile);
    }
    else{
        printf("Usage: %s <input file> <output file>\n", argv[0]);
    }
    return 0;
}