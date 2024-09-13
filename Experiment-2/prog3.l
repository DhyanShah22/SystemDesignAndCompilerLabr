%option noyywrap
%{
#include <stdio.h>

int spaces = 0, tabs = 0, newlines = 0;
%}

%%
[ ]          { spaces++; }    
[\t]         { tabs++; }      
[\n]         { newlines++; }  
.            { /* ignore other characters */ }
%%

int main(void) {
    yylex();
    printf("Spaces: %d\n", spaces);
    printf("Tabs: %d\n", tabs);
    printf("Newlines: %d\n", newlines);
    return 0;
}

