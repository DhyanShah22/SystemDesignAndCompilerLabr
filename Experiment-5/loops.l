%{
#include "loops.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%

[0-9]+          { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return IDENTIFIER; }
"for"          { return FOR; }
"do"           { return DO; }
"while"        { return WHILE; }
"end"          { return END; }
"("            { return '('; }
")"            { return ')'; }
"{"            { return '{'; }
"}"            { return '}'; }
";"            { return ';'; }
"="            { return '='; }
"++"           { return "++"; }
"+"            { return '+'; }
"-"            { return '-'; }
"*"            { return '*'; }
"/"            { return '/'; }
[ \t\n]+       { /* ignore whitespace */ }
.              { printf("Unexpected character: %s\n", yytext); }

%%

// Error handling
int yywrap() {
    return 1;
}
