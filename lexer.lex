%{

#include <assert.h>
#include "ast.h"
#include <string.h>
#include "y.tab.h"


/* keep track of current character number */
static int col = 1;
/* keep track of current line number */
static int line = 1;
static const int TAB_SIZE = 4;


static int stack[1<<10];
static int fast_block = 0;
static int slow_block = 0;

void process_indentation() {
	int indentSpaces = 0;
	int indentTabs = 0;
    int indentation;

	// Count spaces and tabs
	for (int i = 0; i < yyleng; i++) {
		if (yytext[i] == ' ') {
			indentSpaces++;
			col += 1;
		} else if (yytext[i] == '\t') {
			indentTabs++;
			col += 1;
		} else if (yytext[i] == '\n') {
			line += 1;
			col = 1;
			indentTabs = indentSpaces  = 0;
		}
	}
    // We will use this to figureout the current block later.
	indentation = indentSpaces + indentTabs * TAB_SIZE;

    if (indentation > stack[fast_block]) {
        fast_block += 1;
    } else {
        while (indentation < stack[fast_block]) {
          fast_block -= 1;
        }
    }

    stack[fast_block] = indentation;

   // fprintf (stderr, "[%s], ind:%d old %d, new %d\n", yytext, indentation, slow_block, fast_block);

    /*
    We should have exact number of spaces in start of the block and end of the block
    means multiple of 2
    */
}


#define copy_token_location_and_update_col()  { int status = __copy_token_location_and_update_col(); if (status != 0) { yyless(0);  return status;}  }
int __copy_token_location_and_update_col() {
    //fprintf(stderr, "%s, %dm %d\n", yytext, slow_block, fast_block);
    if (slow_block < fast_block) {
        slow_block += 1;
        // yyless(0);
        return BLOCK_START;
    }

    if (slow_block > fast_block) {
        slow_block -= 1;
        // yyless(0);
        return BLOCK_END;
    }
	col += yyleng;
    return 0;
}
/*

We have to return INDENDEATION to the parser somehow
when indentation increase parser should get some token
when indentation decreases parser should get some token
when <EOF> is hit we have to close all the indentations

This is the possible way:
	process indentation will happen normaly and we will not return anything;
	we will keep track of curr_ind and new_ind
	new_ind will be updateded by the process indentation


	for other case of the regular expression than the "process indentation"
	we should first check if curr_ind != new_ind
	we should undo the last parsing again
	and try to make the cur_id == new_ind first


	and at the end of the file we should det the new_ind = 0
	and try to make cur_ind == new_ind again and again with undo
*/

%}

%option noyywrap
%x COMMENT_CODE
%%
"/*"        	{ BEGIN(COMMENT_CODE); }
"*/"        	{ return TRASH;  /* No comment start; otherwise will be threaded as  math operators '*' & '/' */ }
<COMMENT_CODE>{
  "*/"      		{ BEGIN(INITIAL); }
  [^*]*     		{ /* In comment; and its not '*' */ }
  "*"       		{ /* In comment; and we are sure that next char is not '/' because that have been handled above */ }
  <<EOF>>   		{ return TRASH; /* No commend end */}
}
\n[ \t\n]*	{ process_indentation(); /*return INDENTATION;/* /* TODO: Dont use c; just write good parser with start, mid and end contdition */}
return		{ copy_token_location_and_update_col(); return RETURN; }
var		{ copy_token_location_and_update_col(); return VAR; }
implicit	{ copy_token_location_and_update_col(); return IMPLICIT; }
int		{ copy_token_location_and_update_col(); return TYPE_INT; }
void		{ copy_token_location_and_update_col(); return TYPE_VOID; }
string		{ copy_token_location_and_update_col(); return TYPE_STRING; }
fun		{ copy_token_location_and_update_col(); return FUN; }
if		{ copy_token_location_and_update_col(); return IF; }
else       	{ copy_token_location_and_update_col(); return ELSE; }
"while"      	{ copy_token_location_and_update_col(); return WHILE; }
"otherwise"     { copy_token_location_and_update_col(); return OTHERWISE; }
"repeat"     	{ copy_token_location_and_update_col(); return REPEAT; }
#[^\n]*      	{ strcpy(yylval.str_val,yytext); /*return COMMENT;*/ }
\"([^\n\"`]|`[\"`nt])*?\" 		{ copy_token_location_and_update_col(); yylval.str = strdup(yytext); return STRING;  /* TODO: Dont use c; just write good parser with start, mid and end contdition */}
[0-9]+[A-Za-wyz]+[0-9A-Za-z]* 		{ copy_token_location_and_update_col(); strcpy(yylval.str,yytext); return TRASH; }
0x[0-9A-F]*[a-zG-Z]+[0-9a-zA-Z]*	{ copy_token_location_and_update_col(); strcpy(yylval.str,yytext); return TRASH; }
0x[0-9A-F]+	{ copy_token_location_and_update_col(); yylval.int_val = strtol(yytext, 0, 16); return NUMBER; }
0[0-7]+		{ copy_token_location_and_update_col(); yylval.int_val = strtol(yytext, 0, 8); return NUMBER; }
[0-9]+		{ copy_token_location_and_update_col(); yylval.int_val = strtol(yytext, 0, 10); return NUMBER; }
[a-zA-Z][a-zA-Z0-9]*			{ copy_token_location_and_update_col(); yylval.str = strdup(yytext); return NAME; }
[ ]		{ copy_token_location_and_update_col(); /*return SPACE;*/ }
\t		{ copy_token_location_and_update_col(); /*return TAB;*/ }
";"		{ copy_token_location_and_update_col(); return SEMICOLON; }
","		{ copy_token_location_and_update_col(); return COMMA; }
"+"		{ copy_token_location_and_update_col(); return PLUS; }
"-"		{ copy_token_location_and_update_col(); return MINUS; }
"*"		{ copy_token_location_and_update_col(); return MUL; }
"/"		{ copy_token_location_and_update_col(); return DIV; }
"%"		{ copy_token_location_and_update_col(); return REM; }
"=="		{ copy_token_location_and_update_col(); return EQ; }
"<>"		{ copy_token_location_and_update_col(); return NE; }
"<"		{ copy_token_location_and_update_col(); return LT; }
"<="		{ copy_token_location_and_update_col(); return LE; }
">"		{ copy_token_location_and_update_col(); return GT; }
">="		{ copy_token_location_and_update_col(); return GE; }
"!"		{ copy_token_location_and_update_col(); return NOT; }
"&"		{ copy_token_location_and_update_col(); return BAND; }
"|"		{ copy_token_location_and_update_col(); return BOR; }
"^"		{ copy_token_location_and_update_col(); return XOR; }
"&&"		{ copy_token_location_and_update_col(); return AND; }
"||"		{ copy_token_location_and_update_col(); return OR; }
"("		{ copy_token_location_and_update_col(); return LPAREN; }
")"		{ copy_token_location_and_update_col(); return RPAREN; }
":="            { copy_token_location_and_update_col(); return ASSIGN; }
"["        { copy_token_location_and_update_col(); return LBRACKET; }
"]"        { copy_token_location_and_update_col(); return RBRACKET; }
<<EOF>>   {   int status; fast_block = 0; while ((status = __copy_token_location_and_update_col()) != 0) return status; return 0; }
.		{ copy_token_location_and_update_col(); strcpy(yylval.str_val,yytext); return TRASH; }
