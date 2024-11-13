%{

#include <string.h>
#include "y.tab.h"

/* keep track of current character number */
int col = 1;
/* keep track of current line number */
int line = 1;

%}

%option noyywrap

%%

"return"                 { col += 6; return RETURN; }

.                        { fprintf(stderr,"illegal token\n"); exit(1); }

