%{
#include <stdio.h>
%}

%token NUM  /* Define NUM as a token */

%%
expr:   expr '+' expr   { printf("%d + %d\n", $1, $3); }
    |   expr '*' expr   { printf("%d * %d\n", $1, $3); }
    |   '(' expr ')'    { $$ = $2; }
    |   NUM             { $$ = $1; }  /* Use the token */
    ;
%%

int main() {
    yyparse();
    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
    return 0;
}
