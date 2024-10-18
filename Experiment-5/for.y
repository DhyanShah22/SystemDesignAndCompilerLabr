%{
#include <stdio.h>
#include <stdlib.h>
%}

%token FOR ID BOP UOP NUMBER STRING DO WHILE IF ELSE

%% 

prg:
    FOR '(' lexp ';' lexp ';' lexp ')' lbody { printf("For loop\n"); }
    | WHILE '(' lexp ')' lbody { printf("While loop\n"); }
    | DO codeblock WHILE '(' lexp ')' ';' { printf("DO while\n"); }
    | IF '(' lexp ')' lbody { printf("IF\n"); }
    | IF '(' lexp ')' lbody ELSE lbody { printf("IF..ELSE\n"); }
    ;

lbody:
    stmt
    | codeblock
    ;

codeblock:
    '{' stmt_list '}'
    ;

stmt_list:
    stmt_list stmt
    | 
    ;

stmt:
    lexp ';'                  // Expression followed by a semicolon
    | ID '(' exp_list ')' ';' // Function call (e.g., printf)
    ;

exp_list:
    exp_list ',' exp
    | exp
    ;

lexp:
    fexp
    |                          /* Empty for allowing blank segments */
    ;

fexp:
    fexp ',' exp              // Comma-separated expressions
    | exp
    | '(' fexp ')'            // Use braces for priority
    ;

exp:
    ID BOP exp                // Binary operation
    | ID UOP                  // Unary operation on the right
    | UOP ID                  // Unary operation on the left
    | ID
    | NUMBER
    | STRING                  // Handle string literals for printf
    ;

%% 

int main() {
    printf("Enter a program:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
