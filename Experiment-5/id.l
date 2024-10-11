%{
#include "id.tab.h"
#include <ctype.h>
#include <stdlib.h>  // For atoi
#include <string.h>  // For strdup

void yyerror(const char *s);  // Just declare it
%}

%%
[0-9]+          { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9]* { yylval.sval = strdup(yytext); return IDENTIFIER; }
[ \t\n]         ;  
"="             { return '='; }
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"^"             { return '^'; }

.               { yyerror("Unknown character"); }

%%

int yywrap() {
    return 1;
}
