%{
#include "parse.tab.h"  // Include the Bison-generated header for token definitions
#include <ctype.h>
%}

%% 

[0-9]+ { yylval = atoi(yytext); return NUMBER; }  // Return NUMBER token
[ \t]  ;  // Ignore whitespace
\n     return 0;  // End of input on newline
.      return yytext[0];  // Return individual characters (+, -, *, /, etc.)

%%

int yywrap() {
    return 1;
}
