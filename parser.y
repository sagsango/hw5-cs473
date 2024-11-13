%{
#include <stdio.h>
#include <stdlib.h>

extern char * result;

int yylex(void); /* function prototype */

void yyerror(const char *s) {
    fprintf(stderr,"parsing error %s\n", s); exit(1);
}

%}


%union {
	int ival;
    char * stmt;
	}

%define parse.error verbose

%token <ival> INT

%token
  RETURN

%type <stmt>  stmt

%start program

%%

program:	stmt   { }

stmt: RETURN       { printf("RETURN"); }