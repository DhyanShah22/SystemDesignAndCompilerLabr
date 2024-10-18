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
    lexp ';'                  
    | ID '(' exp_list ')' ';' 
    ;

exp_list:
    exp_list ',' exp
    | exp
    ;

lexp:
    fexp
    |                          
    ;

fexp:
    fexp ',' exp              
    | exp
    | '(' fexp ')'            
    ;

exp:
    ID BOP exp                
    | ID UOP                  
    | UOP ID                  
    | ID
    | NUMBER
    | STRING                  
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
