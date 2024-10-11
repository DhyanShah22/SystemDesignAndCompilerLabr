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


%type <ival> expression term factor statement

%%
program:
    | program statement
    ;

statement:
    IDENTIFIER '=' expression {
        setVarValue($1, $3);  // Set the variable value
        printf("Assigned %s = %d\n", $1, $3);  // Output assignment result
    }
    | expression {
        printf("Result: %d\n", $1);  // Print the result of the expression
    }
    ;

expression:
    expression '+' term { $$ = $1 + $3; }
    | expression '-' term { $$ = $1 - $3; }
    | term { $$ = $1; }  // Simplified for unambiguous grammar
    ;

term:
    term '*' factor { $$ = $1 * $3; }
    | term '/' factor {
        if ($3 == 0) {
            yyerror("divide by zero");
            $$ = 0;  // Returning 0 to prevent further errors
        } else {
            $$ = $1 / $3;
        }
    }
    | factor { $$ = $1; }  // Simplified for unambiguous grammar
    ;

factor:
    '(' expression ')' { $$ = $2; }
    | IDENTIFIER {
        $$ = getVarValue($1);  // Fetch the variable value
    }
    | NUMBER { $$ = $1; }
    | '-' factor %prec UMINUS { $$ = -$2; }  // Unary minus
    | factor '^' factor { $$ = pow($1, $3); }  // Exponentiation
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

// Function to get the value of a variable
int getVarValue(char *name) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            return vars[i].value;
        }
    }
    yyerror("undefined variable");
    return 0;  // Default return value for undefined variables
}

// Function to set the value of a variable
void setVarValue(char *name, int value) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            vars[i].value = value;  // Update existing variable
            return;
        }
    }
    // If the variable does not exist, create it
    if (varCount < MAXVARS) {
        strcpy(vars[varCount].name, name);
        vars[varCount].value = value;
        varCount++;
    } else {
        yyerror("too many variables");
    }
}
