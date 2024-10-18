%{
#include "parser.tab.h"
#include <ctype.h>
%}

%%

[0-9]+ { yylval = atoi(yytext); return NUMBER; }
[ \t]  ;  // Ignore whitespace
\n     return 0;  // End of input on newline
.      return yytext[0];  // Return individual characters (+, -, *, /, etc.)

%%

int yywrap() {
    return 1;
}
