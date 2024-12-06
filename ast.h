#ifndef AST_H
#define AST_H

#include "symbol.h"

typedef struct list_ list;

struct list_ {
    void* head;
    struct list_ * next;
};

// curr node, head/tail
list* ListAddFirst(void* hd, list* tl);
list* ListAddLast(void* hd, list* tl);

// Program:------------------------------------------------------------------
typedef struct program_ {
    list * variables;
    list * functions;
    list * statements;
} program;

// types::------------------------------------------------------------------
typedef struct ty_node {
    enum {
        int_ty,
        string_ty,
        void_ty,
        // TODO Add more types if needed
    } kind;
} ty_node;

ty_node* IntTyNode();
ty_node* StringTyNode();
ty_node* VoidTyNode();
// TODO Add more types if needed
ty_node* TyNode(char * type);
char* typeToStr(ty_node* type);

// Expressions:------------------------------------------------------------------
typedef enum {
    plus_op,
    // TODO Add more binary operators
} binop;

typedef enum { not_op } unop;

typedef struct exp_node {
    // This is a tagged union
    // TODO add more variants to support all types of expressions
    enum {
        int_exp, binop_exp, unop_exp, string_exp, plus_exp, minus_exp,
        mul_exp, div_exp, rem_exp,
        lt_exp, le_exp, gt_exp, ge_exp, eq_exp, ne_exp, band_exp, bor_exp, xor_exp, and_exp, or_exp,
        name_exp, funcall_exp, array_access_exp } kind;
    union {
        int ival;
        char * strval;
        char * namevar;
        struct { binop op; struct exp_node* e1; struct exp_node* e2; } bin_ops;
        struct { unop op; struct exp_node* e; } un_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } plus_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } minus_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } mul_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } div_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } rem_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } lt_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } le_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } gt_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } ge_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } eq_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } ne_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } band_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } bor_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } xor_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } and_ops;
        struct { struct exp_node * left_exp; struct exp_node* right_expr; } or_ops;
        struct { char * name; list *args_exp; } funcall_op;
        struct { char * name; struct exp_node * ind_exp;} array_access_ops;
    } data;
} exp_node;

exp_node* IntNode(int val);
exp_node* StrNode(char * str);
exp_node* NameNode(char * str);
exp_node* BinOpNode(binop operation, exp_node * left, exp_node * right);
exp_node* UnOpNode(unop operation, exp_node * expr);
exp_node * PlusNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * MinusNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * MulNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * DivNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * RemNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * LTNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * LENode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * GTNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * GENode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * EQNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * NENode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * BANDNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * BORNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * XORNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * ANDNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * ORNode(struct exp_node * left_exp, struct exp_node* right_expr);
exp_node * FunCallNode(char * name, list * args_exp);
exp_node * ArrayAccessNode(char * name, exp_node * ind_exp);
// TODO add more constructor functions, one per variant in the tagged union above

// Statements::------------------------------------------------------------------
typedef struct stmt_node {
    // This is a tagged union
    // TODO add more variants to support all types of statements
    enum { if_stmt, ret_stmt, while_stmt, repeat_stmt, assign_stmt, exp_stmt, array_assign_stmt} kind;
    union {
        struct { exp_node* cond; struct list_* then_stmts; struct list_* else_stmts; } if_ops;
        struct { exp_node* cond; struct list_* then_stmts; struct list_* otherwise_stmts; } while_ops;
        struct { exp_node* times; struct list_* stmts;} repeat_ops;
        /* TODO: Array assignment deal separately for clean code */
        struct { char * name; exp_node * exp; } assign_ops;
        struct { exp_node * exp; } exp_ops;
        struct { char * name; exp_node * ind_exp; exp_node * assign_exp;} array_assign_ops;
        exp_node* ret_exp;
    } data;
} stmt_node;

stmt_node* RetNode(exp_node* e);
stmt_node* IfNode(exp_node* cond, list * thenStmts, list * elseStmts);
stmt_node* WhileNode(exp_node *cond, list *thenStmts, list *otherwiseStmts);
stmt_node* RepeatNode(exp_node *times, list *stmts);
stmt_node* AssignNode(char * name, exp_node * exp);
stmt_node* ExpNode(exp_node* exp);
stmt_node * ArrayAssignNode(char * name, exp_node * idx_exp, exp_node * assign_exp);
// TODO add more constructor functions, one per variant in the tagged union above

// Variable declaration::------------------------------------------------------------------
typedef struct vardec_node {
    ty_node * type;
    char * name;
    exp_node * init;
    char implicit;
    char array;
    int size;
    //char dec;
    char manually;
} vardec_node;

vardec_node * VarDecNode(char * name, ty_node * type, exp_node * init);
vardec_node * VarDecNodeImp(char * name, ty_node * type, exp_node * init);
vardec_node * VarDecNodeImpManually(char * name, ty_node * type, exp_node * init);
vardec_node * ArrayDecNode(char * name, ty_node *type, int size);
vardec_node * ArrayDecNodeImp(char * name, ty_node *type, int size);


// Function declaration::------------------------------------------------------------------
typedef struct param {
    ty_node* ty;
    char* name;
} param ;

param * Param(ty_node * type, char * name);

typedef struct fundec_node {
    ty_node * type;
    char * name;
    list * params;
    list * vardecs;
    list * statements;
    // TODO add everything that a function declaration needs
} fundec_node;

fundec_node * FunDecNode(char * name, ty_node * type, list * params, list * vardecs, list * statements);
// TODO improve constructor with everything that a function declaration needs

typedef struct frame {
    S_table args_locs_types;
    S_table args;
    S_table indexes;   // Dont save 0
    S_table seen;
    ty_node * ret;
    long n_args;
    long n_index;
    long n_imp;
} frame;

#endif
