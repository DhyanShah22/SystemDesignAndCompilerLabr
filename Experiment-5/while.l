%{
#include "while.tab.h"
#include <stdio.h>
%}

num [0-9]+
id [a-zA-Z]+
bop =|<|>|!=|<=|>=|==|&&|\|\|[+-/*]
uop \+\+|--|!

%% 

"do"        { return DO; }
"while"     { return WHILE; }
"for"       { return FOR; }
"if"        { return IF; }
"else"      { return ELSE; }
"printf"    { return ID; } // Treat printf as an ID token
{bop}       { return BOP; }
{uop}       { return UOP; }
{num}       { return NUMBER; }
\"[^\"]*\"  { return STRING; } // Handle string literals
{id}        { return ID; }
[ \n\t]     ; /* Reject whitespaces */
.           { return *yytext; }

%% 

int yywrap() {
    return 1;
}
