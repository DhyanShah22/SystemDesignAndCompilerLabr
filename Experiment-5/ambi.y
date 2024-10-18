%{
#include <stdio.h>
#include <stdlib.h>

int yylex();          // Lexer function declaration
void yyerror(char *); // Error handling function declaration
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%right UMINUS

%%
expression:
    expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression {
        if($3 == 0) {
            yyerror("divide by zero");
            $$ = 0;  // Return 0 to avoid further errors
        } else {
            $$ = $1 / $3;
        }
    }
    | '-' expression %prec UMINUS { $$ = -$2; }
    | '(' expression ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;
%%

int main() {
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}
