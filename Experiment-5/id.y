%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXVARS 100

int yylex();
void yyerror(const char *s);  // Just declare it

typedef struct {
    char name[50];
    int value;
} Variable;

Variable vars[MAXVARS];
int varCount = 0;

int getVarValue(char *name);
void setVarValue(char *name, int value);
%}

%union {
    int ival;  // For integer values
    char *sval;  // For strings (like variable names)
}

%token <ival> NUMBER
%token <sval> IDENTIFIER

%left '+' '-'
%left '*' '/'
%right '^'
%right UMINUS

%type <ival> expression statement

%%
program:
    | program statement
    | program exit_statement
    ;

statement:
    IDENTIFIER '=' expression {
        setVarValue($1, $3);  // Set the variable value without printing
        printf("Assigned %s = %d\n", $1, $3); // Debugging line
    }
    | expression {
        printf("Result: %d\n", $1);  // Print the result of the expression
        printf("Result: %d\n", $1);
    }
    ;

exit_statement:
    "exit" { exit(0); }
    ;

expression:
    expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression {
        if ($3 == 0) {
            yyerror("divide by zero");
            $$ = 0; // Returning 0 to prevent further errors
        } else {
            $$ = $1 / $3;
        }
    }
    | expression '^' expression { $$ = pow($1, $3); }
    | '-' expression %prec UMINUS { $$ = -$2; }
    | '(' expression ')' { $$ = $2; }
    | IDENTIFIER {
        $$ = getVarValue($1);  // Fetch the variable value
    }
    | NUMBER { $$ = $1; }
    ;

%%

// Main function to run the parser
int main() {
    printf("Enter expressions (e.g., a = 3, b = 5, a + b):\n");
    yyparse();
    return 0;
}

// Error handling function
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int getVarValue(char *name) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return vars[i].value;
        }
    }
    yyerror("undefined variable");
    return 0;  
}

void setVarValue(char *name, int value) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            vars[i].value = value;  
            return;
        }
    }
    if (varCount < MAXVARS) {
        strcpy(vars[varCount].name, name);
        vars[varCount].value = value;
        varCount++;
    } else {
        yyerror("too many variables");
    }
}
