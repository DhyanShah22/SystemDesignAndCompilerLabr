%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>  // For pow() function
int yylex();          // Lexer function declaration
void yyerror(char *); // Error handling function declaration
%}

%token NUMBER  /* Declare NUMBER token */

%%
expression:
    expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression {
        if ($3 == 0) {
            yyerror("divide by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | expression '%' expression { $$ = $1 % $3; } // Modulus operator
    | expression '^' expression { $$ = pow($1, $3); } // Exponentiation
    | '-' expression { $$ = -$2; } // Unary minus
    | '(' expression ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;
%%

// The main function
int main() {
    printf("Enter an expression: ");
    yyparse();
    return 0;
}

// Error handling function
void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}
