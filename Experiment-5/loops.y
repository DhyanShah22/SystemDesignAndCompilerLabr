%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXVARS 100

int yylex();
void yyerror(const char *s);

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
    int ival;
    char *sval;
}

%token <ival> NUMBER
%token <sval> IDENTIFIER
%token FOR DO WHILE END

%left '+' '-'
%left '*' '/'
%right UMINUS

%type <ival> expression statement program for_statement while_statement

%%
program:
    /* empty */ { }
    | program statement { }
    ;

statement:
    IDENTIFIER '=' expression ';' {
        setVarValue($1, $3);
        printf("Assigned %s = %d\n", $1, $3);
    }
    | for_statement
    | while_statement
    ;

for_statement:
    FOR '(' IDENTIFIER '=' expression ';' expression ';' IDENTIFIER ')' DO '{' program '}' END {
        // Initialize loop variable
        int i;
        setVarValue($3, $5); // Initialize loop variable
        for (i = getVarValue($3); i < $7; i++) { // Use $7 for the condition
            // Execute the statements in the program block
            printf("In loop: %s = %d\n", $3, i);
            // You need to handle block execution here
        }
    }
    ;

while_statement:
    WHILE '(' expression ')' DO '{' program '}' END {
        while ($3) {
            printf("While loop condition true, executing block.\n");
            // Execute the statements in the block
        }
    }
    ;

expression:
    expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { $$ = $1 / $3; }
    | '-' expression %prec UMINUS { $$ = -$2; }
    | '(' expression ')' { $$ = $2; }
    | IDENTIFIER { $$ = getVarValue($1); }
    | NUMBER { $$ = $1; }
    ;

%%

// Main function to run the parser
int main() {
    printf("Enter statements (e.g., a = 5; for(i = 0; i < 10; i++) do { ... } end;):\n");
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
    return 0;
}

// Function to set the value of a variable
void setVarValue(char *name, int value) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            vars[i].value = value;
            return;
        }
    }
    // Create a new variable if it doesn't exist
    if (varCount < MAXVARS) {
        strcpy(vars[varCount].name, name);
        vars[varCount].value = value;
        varCount++;
    } else {
        yyerror("too many variables");
    }
}
