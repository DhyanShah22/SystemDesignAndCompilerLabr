// Save as parse.y
%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int yylex();  
int yyerror(char *s);  
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%right '^'  
%right UMINUS  

%%
expression: expression '+' expression { $$ = $1 + $3; printf("%d + %d = %d\n", $1, $3, $$); }
    | expression '-' expression { $$ = $1 - $3; printf("%d - %d = %d\n", $1, $3, $$); }
    | expression '*' expression { $$ = $1 * $3; printf("%d * %d = %d\n", $1, $3, $$); }
    | expression '/' expression
        {
            if ($3 == 0) {
                yyerror("divide by zero");
                $$ = 0;
            } else {
                $$ = $1 / $3;
                printf("%d / %d = %d\n", $1, $3, $$);
            }
        }
    | expression '^' expression { $$ = pow($1, $3); printf("%d ^ %d = %d\n", $1, $3, $$); }  
    | '-' expression %prec UMINUS { $$ = -$2; printf("-%d = %d\n", $2, $$); }  
    | '(' expression ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;

%%
int main() {
    printf("Enter expressions:\n");
    yyparse();
    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}
