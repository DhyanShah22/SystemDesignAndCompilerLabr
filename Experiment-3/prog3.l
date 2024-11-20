%option noyywrap

%{
    #include <stdio.h>
    int total_tags = 0;
%}

%%
"<"[^>]*">" {total_tags++; printf("HTML Tag spotted %s\n", yytext);}
.           {}
%%

int main(int argc, char **argv){
    FILE *infile = fopen(argv[1], "r");
    if(!infile){
        printf("Error opening file\n");
    }
    yyin = infile;
    yylex();
    printf("Total HTML tags: %d\n", total_tags);
}
