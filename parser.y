%{
#include <stdio.h>
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
expr : expr '+' expr {printf("addition\n");}
        | expr '-' expr {printf("subtraction\n");}
        | expr '*' expr {printf("multiplication\n");}
        | expr '/' expr {printf("division\n");}
        | NUMBER {printf("number\n");}
        ;

%%

int main(){
    yyparse();
    return 0;
}

int yyerror(char *s){
    printf("error: %s\n", s);
    return 0;
}