%{
#define _POSIX_C_SOURCE 200809L
#include <assert.h>
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


extern char * result;
extern program p;

int yylex(void); /* function prototype */

void yyerror(const char *s) {
    fprintf(stderr, "parsing error %s\n", s);
    exit(73);
}

%}

%union {
    int int_val;
    char str_val[256];
  /*  char * type;
    char * name;

    char * stmt_val;
    char * return_type;
    char * space_type;
    char * int_type;
    char * semicolan_type;
    char * comma_type;
    char * RETURN_type;
    char * SPACE_type;
    char * INT_type;
    char * SEMICOLON_type;
    char * COMMA_type;
    char * AND_type;
    char * LPAREN_type;
    char * RPAREN_type;
    char * LBRACKET_type;
    char * RBRACKET_type;
    char * BAND_type;
    char * BOR_type;
    char * DIV_type;
    char * ELSE_type;
    char * EQ_type;
    char * GE_type;
    char * GT_type;
    char * IF_type;
    char * LE_type;
    char * LT_type;
    char * MINUS_type;
    char * MUL_type;
    char * NE_type;
    char * NOT_type;
    char * OR_type;
    char * PLUS_type;
    char * REM_type;
    char * WHILE_type;
    char * XOR_type;
    char * NEWLINE_type;
    char * ASSIGN_type;
    char * OTHERWISE_type;
    char * REPEAT_type;
    char * TAB_type;
    char * BINARY_type;
    char * OCTAL_type;
    char * HEXADECIMAL_type;
    char * INDENTATION_type;
    char * VAR_type;
    char * IMPLICIT_type;
    char * TYPE_INT_type;
    char * TYPE_VOID_type;
    char * TYPE_STRING_type;
    char * NAME_type;
    char * TRASH_type;
    char * FUN_type;
    char * COMMENT_type;
    char * STRING_type;
    char * NUMBER_type;
*/
    char * str;
    char * statements_ret_type;
    char * statement_ret_type;
    char * return_stmt_ret_type;

    list * variables_type;
    program * program_type;
    vardec_node * var_decl_type;
    exp_node * expression_type;
    list * functions_type;
    fundec_node * func_decl_type;
    list * statements_type;
    stmt_node * statement_type;
    ty_node * type_type;
    list * arg_list_type;
    list * arg_list_nonempty_type;
    stmt_node * expr_stmt_type;
    stmt_node * return_stmt_type;
    stmt_node * if_stmt_type;
    stmt_node * while_stmt_type;
    stmt_node * repeat_stmt_type;
    stmt_node * assignment_type;
    int NUMBER_type;
    char * NAME_type;
    list * fn_variables_type;
    vardec_node * fn_var_decl_type;
    list * expr_list_type;
    list * expr_list_non_empty_type;

}

%define parse.error verbose

%token
    RETURN
    SPACE
    INT
    SEMICOLON
    COMMA
    AND
    LPAREN
    RPAREN
    LBRACKET
    RBRACKET
    BAND
    BOR
    DIV
    ELSE
    EQ
    GE
    GT
    IF
    LE
    LT
    MINUS  MUL
    NE
    NOT
    OR
    PLUS
    REM
    <WHILE_type> WHILE
    XOR
    <NEWLINE_type> NEWLINE
    <ASSIGN_type> ASSIGN
    <OTHERWISE_type> OTHERWISE
    <REPEAT_type> REPEAT
    <TAB_type> TAB
    <BINARY_type> BINARY
    <OCTAL_type> OCTAL
    <HEXADECIMAL_type> HEXADECIMAL
    <INDENTATION_type> INDENTATION
    <VAR_type> VAR
    <IMPLICIT_type> IMPLICIT
    <TYPE_INT_type> TYPE_INT
    <TYPE_VOID_type> TYPE_VOID
    <TYPE_STRING_type> TYPE_STRING
    <NAME_type> NAME
    <TRASH_type> TRASH
    <FUN_type> FUN
    <COMMENT_type> COMMENT
    <str> STRING
    <NUMBER_type> NUMBER
    BLOCK_START
    BLOCK_END


// Precedence and associativity rules
%left ASSIGN        // Assignment
%left OR              // Logical OR
%left AND             // Logical AND
%left BOR            // Bitwise OR
%left XOR            // Bitwise XOR
%left BAND           // Bitwise AND
%left EQ NE      // Equality
%left LT LE GT GE // Relational operators
%left PLUS MINUS     // Addition and subtraction
%left MUL DIV REM   // Multiplication, division, and remainder
%right NOT           // Logical NOT
%right LBRACKET LPAREN // Array access and function calls
%left SEMICOLON
%left FUNC_CALL_PREC

%nonassoc "then"
%nonassoc ELSE
%nonassoc OTHERWISE

%type <program_type> program
%type <variables_type> variables
%type <functions_type> functions
%type <statements_type> statements
%type <var_decl_type> var_decl
%type <type_type> type
%type <func_decl_type> func_decl
%type <arg_list_type> arg_list
%type <arg_list_nonempty_type> arg_list_nonempty
%type <str> func_body
%type <statement_type> statement
%type <str> func_call
%type <expr_stmt_type> expr_stmt
%type <return_stmt_type> return_stmt
%type <expression_type> expression
    %type <if_stmt_type> if_stmt
    %type <while_stmt_type> while_stmt
    %type <repeat_stmt_type> repeat_stmt
    %type <assignment_type> assignment
    %type <fn_variables_type> fn_variables
    %type <fn_var_decl_type> fn_var_decl
    %type <expr_list_type> expr_list
    %type <expr_list_non_empty_type> expr_list_non_empty
%start program

%%
program: /* OK */
    variables functions statements    {  p.variables=$1; p.functions=$2; p.statements=$3;}
    ;

// Variables section: global variables
variables: /* OK */
    /* empty */  { $$ = NULL;  }
    | variables var_decl  { $$ = ListAddLast($2, $1); }
    ;

// Variables section: function variables
fn_variables: /* OK */
    /* empty */  { $$ = NULL;}
    | fn_variables fn_var_decl  { $$ = ListAddLast($2, $1);   }
    ;

// Functions section: global function declarations
functions:
    /* empty */            { $$ = NULL;  }
    | functions func_decl  { $$ = ListAddLast($2, $1);   }
    ;

// Statements section: standalone statements
statements:
    /* empty */   {  $$ = NULL;  }
    | statements statement  { $$ = ListAddLast($2, $1); }
    ;
/*
nonempty_statements:
	statement   //{ $$= buf_printf("(%s)", $1);  }
    |   statements statement  //{ $$= buf_printf("(%s)", $1);  }
	;
*/
// Variable declaration rules (support for arrays)
var_decl:
    VAR NAME type ASSIGN expression SEMICOLON   { $$ = VarDecNode($2, $3, $5); }
    | IMPLICIT NAME type ASSIGN expression SEMICOLON   {  $$ = VarDecNodeImp($2, $3, $5); }
    | VAR NAME LBRACKET NUMBER RBRACKET type SEMICOLON   { $$ = ArrayDecNode($2, $6, $4);  } /* Array declaration */
    | IMPLICIT NAME LBRACKET NUMBER RBRACKET type SEMICOLON  { assert(0);   }  /* Implicit array declaration */
    ;

fn_var_decl:
    VAR NAME type ASSIGN expression SEMICOLON   { $$ = VarDecNode($2, $3, $5); }
    //| IMPLICIT NAME type ASSIGN expression SEMICOLON   { $$=(debug?buf_printf("<var_decl%svar_decl>",$5):buf_printf("%s\n",$5));  } */
    | VAR NAME LBRACKET NUMBER RBRACKET type SEMICOLON   { $$ = ArrayDecNode($2, $6, $4);   } /* Array declaration */ //{ $$= buf_printf("(%s)", $1);  }
    /* | IMPLICIT NAME LBRACKET NUMBER RBRACKET type SEMICOLON  */
    ;

// Type definitions: int, string, and void
type:
    TYPE_INT    { $$ = IntTyNode(); }//{ $$= buf_printf("(%s)", $1);  }
    | TYPE_STRING { $$ = StringTyNode(); }//{ $$= buf_printf("(%s)", $1);  }
    | TYPE_VOID  { $$ = VoidTyNode(); }//{ $$= buf_printf("(%s)", $1);  }
    ;

// Function declaration rules with BLOCK_START and BLOCK_END
/*
func_decl:
    FUN NAME type LPAREN arg_list RPAREN BLOCK_START func_body BLOCK_END { assert(0);   }
    ;
*/
func_decl:
    FUN NAME type LPAREN arg_list RPAREN BLOCK_START fn_variables statements BLOCK_END { $$ = FunDecNode($2, $3, $5, $8, $9);   }
    ;

// Argument list for functions (supports arrays as arguments)
arg_list:
    /* empty */ { $$ = NULL;}
    | arg_list_nonempty { $$ = $1; }//{ $$= buf_printf("(%s)", $1);  }
    ;

arg_list_nonempty:
    NAME type { $$ = ListAddFirst(Param($2, $1),NULL); } //{ $$= buf_printf("(%s)", $1);  }
    | NAME type LBRACKET RBRACKET   {assert(0);} /* Array argument in function */ //{ $$= buf_printf("(%s)", $1);  }
    | arg_list_nonempty COMMA NAME type { $$ = ListAddLast(Param($4, $3), $1); } //{ $$= buf_printf("(%s)", $1);  }
    | arg_list_nonempty COMMA NAME type LBRACKET RBRACKET  {assert(0);} /* Multiple array arguments */ //{ $$= buf_printf("(%s)", $1);  }
    ;

    /*
// Function body enclosed with BLOCK_START and BLOCK_END
func_body:
    fn_variables statements    { assert(0);  }
    ;
*/


// Statement rules
statement:
    expr_stmt        { $$ = $1;  }
    | return_stmt    { $$ = $1;  }
    | if_stmt        { $$ = $1;  }
    | while_stmt     { $$ = $1;  }
    | repeat_stmt    { $$ = $1;  }
   /*func_call   // function call is already presnet in expression
    ;
    */
    ;

/*
// Function call rules (as expression)
func_call:
    NAME LPAREN expr_list RPAREN SEMICOLON %prec FUNC_CALL_PREC { $$= buf_printf("<<<%s\n", $3);}
    ;
*/

// Expression statements
expr_stmt:
    expression SEMICOLON    { $$ = ExpNode($1); }
    | assignment            { $$ = $1;  }
    ;

// Return statements
return_stmt:
    RETURN expression SEMICOLON   { $$ = RetNode($2); }
    | RETURN SEMICOLON            { $$ = RetNode(NULL);  }
    ;

/*
if_stmt:
    IF LPAREN expression RPAREN statement { $$ = (debug?buf_printf("<if_stmt%s<mid_if_stmt>%sif_stmt>", $3, $5):buf_printf("%s%s", $3, $5)); free($3); free($5); $3=$5=0;}
   ;
*/

 /*
while_stmt:
    WHILE LPAREN expression RPAREN statement  { $$ = (debug?buf_printf("<while_stmt%s<mid_while_stmt>%swhile_stmt>", $3, $5):buf_printf("%s%s", $3, $5));  free($3); free($5); $3=$5=0;}
;
*/

repeat_stmt:
    REPEAT LPAREN expression RPAREN statement { $$ = RepeatNode($3, ListAddFirst($5, NULL));  }
    |  REPEAT LPAREN expression RPAREN BLOCK_START statement statements BLOCK_END { $$ = RepeatNode($3, ListAddFirst($6, $7));  }
;

// If-Else-If statements with inline or BLOCK_START/BLOCK_END
if_stmt:
    IF LPAREN expression RPAREN statement   %prec "then"   { $$ = IfNode($3, ListAddFirst($5, NULL), NULL); }
    | IF LPAREN expression RPAREN statement ELSE statement { $$ = IfNode($3, ListAddFirst($5, NULL), ListAddFirst($7, NULL)); }
    | IF LPAREN expression RPAREN statement ELSE BLOCK_START statement statements BLOCK_END { $$ = IfNode($3, ListAddFirst($5, NULL), ListAddFirst($8, $9));  }
    | IF LPAREN expression RPAREN BLOCK_START statement statements BLOCK_END  %prec "then" { $$ = IfNode($3, ListAddFirst($6, $7), NULL);  }
    | IF LPAREN expression RPAREN BLOCK_START statement statements BLOCK_END  ELSE statement { assert(0);  }
    | IF LPAREN expression RPAREN BLOCK_START statement statements BLOCK_END  ELSE BLOCK_START statement statements BLOCK_END { $$ = IfNode($3, ListAddFirst($6, $7), ListAddFirst($11, $12));   }
/*
    | IF LPAREN expression RPAREN BLOCK_START nonempty_statements BLOCK_END  // Block-statement if
    | IF LPAREN expression RPAREN BLOCK_START nonempty_statements BLOCK_END else_clause // Block if-else
    ;
*/


 while_stmt:
    WHILE LPAREN expression RPAREN statement  %prec "then" { $$ = WhileNode($3,ListAddFirst($5, NULL), NULL); }
   | WHILE LPAREN expression RPAREN statement OTHERWISE statement { $$ = WhileNode($3, ListAddFirst($5, NULL), ListAddFirst($7, NULL));  }
   | WHILE LPAREN expression RPAREN statement OTHERWISE BLOCK_START statement statements BLOCK_END {  assert(0); }
   | WHILE LPAREN expression RPAREN BLOCK_START statement statements BLOCK_END  %prec "then" { $$ = WhileNode($3, ListAddFirst($6, $7), NULL);   }
   | WHILE LPAREN expression RPAREN BLOCK_START statement statements BLOCK_END  OTHERWISE statement { assert(0);  }
   | WHILE LPAREN expression RPAREN BLOCK_START statement statements BLOCK_END  OTHERWISE BLOCK_START statement statements BLOCK_END { $$ = WhileNode($3, ListAddFirst($6, $7), ListAddFirst($11, $12));  }
;

/*
else_clause:
      // Single-statement else
     // | ELSE BLOCK_START nonempty_statements BLOCK_END                   // Block-statement else
    ;
 */


/*
// While statements with optional 'otherwise' clause
while_stmt:
    WHILE LPAREN expression RPAREN statement                            // Single-statement while
    | WHILE LPAREN expression RPAREN BLOCK_START nonempty_statements BLOCK_END   // Block-statement while
    | WHILE LPAREN expression RPAREN statement otherwise_clause         // Inline while-otherwise
    | WHILE LPAREN expression RPAREN BLOCK_START nonempty_statements BLOCK_END otherwise_clause  // Block while-otherwise
    ;

otherwise_clause:
    OTHERWISE statement                                                 // Single-statement otherwise
    | OTHERWISE BLOCK_START nonempty_statements BLOCK_END                        // Block-statement otherwise
    ;

// Repeat statements with BLOCK_START and BLOCK_END
repeat_stmt:
    REPEAT LPAREN expression RPAREN statement                           // Single-statement repeat
    | REPEAT LPAREN expression RPAREN BLOCK_START nonempty_statements BLOCK_END  // Block-statement repeat
    ;
*/

// Expressions
expression:
    NUMBER   { $$ = IntNode($1);  }
    | STRING { $$ = StrNode($1); }
    | NAME   { $$ = NameNode($1); }
    | NAME LBRACKET expression RBRACKET   { $$ = ArrayAccessNode($1, $3);  } /* Array access (read) */
    | NAME LPAREN expr_list RPAREN  %prec FUNC_CALL_PREC /* Function call*/  { $$ = FunCallNode($1, $3); }
    | LPAREN expression RPAREN    { $$ = $2;  }
    | NOT expression   { $$ = UnOpNode(not_op, $2); }
    | expression MUL expression   { $$ = MulNode($1, $3); }
    | expression DIV expression   { $$ = DivNode($1, $3);   }
    | expression REM expression   { $$ = RemNode($1, $3);   }
    | expression PLUS expression  { $$ = PlusNode($1, $3);   }
    | expression MINUS expression { $$ = MinusNode($1, $3);  }
    | expression LT expression    { $$ = LTNode($1, $3); }
    | expression LE expression    { $$ = LENode($1, $3);  }
    | expression GT expression    { $$ = GTNode($1, $3);   }
    | expression GE expression    { $$ = GENode($1, $3);  }
    | expression EQ expression    { $$ = EQNode($1, $3);   }
    | expression NE expression    { $$ = NENode($1, $3);   }
    | expression BAND expression   { $$ = BANDNode($1, $3);  }
    | expression BOR expression    { $$ = BORNode($1, $3);   }
    | expression XOR expression    { $$ = XORNode($1, $3);   }
    | expression AND expression    { $$ = ANDNode($1, $3);   }
    | expression OR expression     { $$ = ORNode($1, $3);   }
    ;

// Assignment rules
assignment:
    NAME ASSIGN expression SEMICOLON { $$ = AssignNode($1, $3);  }// Standard assignment
    | NAME LBRACKET expression RBRACKET ASSIGN expression SEMICOLON  { $$ = ArrayAssignNode($1, $3, $6);} // Array assignment
    ;

expr_list:
    /* empty */  { $$ = NULL;  }
    | expr_list_non_empty { $$ = $1; }
    ;

expr_list_non_empty:
     expression { $$ = ListAddFirst($1, NULL); }
    | expr_list_non_empty COMMA expression {  $$ = ListAddLast($3, $1); }
    ;
%%
