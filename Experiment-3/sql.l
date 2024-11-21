%option noyywrap

%{
    #include<stdio.h>
    #include<ctype.h>
    int total_tags = 0;
%}

%%

"INSERT"|"CREATE"|"DELETE"|"SELECT"|"UPDATE"|"ALTER"|"TABLE"|"DATABASE"|"INDEX"|"FROM"|"WHERE"|"JOIN" {
    total_tags++;
    printf("SQL tag was spotted %s\n", yytext);
}

.|\n {}

%%

int main(int argc, char **argv){
    if(argc > 1){
        FILE *infile = fopen(argv[1], "r");
        if(!infile){
            printf("Error opening file %s\n", argv[1]);
        }

        yyin = infile;
        yylex();

        fclose(infile);
        printf("Total SQL tags: %d\n", total_tags);
    }
    else{
        printf("Please provide a file to scan\n");
    }
}

