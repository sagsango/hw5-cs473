#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ast.h"

static ty_node int_ty_node    = { int_ty };
static ty_node string_ty_node = { .kind =  string_ty};
static ty_node void_ty_node = { .kind = void_ty};

ty_node* IntTyNode(){
    return &int_ty_node;
}
ty_node* StringTyNode() {
    return &string_ty_node;
}
ty_node * VoidTyNode() {
    return &void_ty_node;
}

// TODO add more types

ty_node* TyNode(char * type) {
    if (!strcmp(type,"int")) {
        return IntTyNode();
    }
    // TODO add more types
    assert(0);
}

char* typeToStr(ty_node* type) {
    switch (type->kind) {
        case int_ty:
            return "int";
        case string_ty:
            return "string";
        // TODO add more types
        case void_ty:
            return "void";
        default:
            assert(0);
    }
}

param * Param(ty_node * type, char * name) { // function param
    param * p = malloc(sizeof(param));
    p->name = name;
    p->ty = type;
    return p;
}

exp_node* IntNode(int val){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = int_exp;
    node->data.ival = val;
    return node;
}
exp_node * StrNode(char * str) {
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = string_exp;
    node->data.strval = str;
    return node;
}
exp_node* NameNode(char * str) {
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = name_exp;
    node->data.namevar = str;
    return node;
}
exp_node* BinOpNode(binop operation, exp_node * left, exp_node * right) {
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = binop_exp;
    node->data.bin_ops.op = operation;
    node->data.bin_ops.e1 = left;
    node->data.bin_ops.e2 = right;
    return node;
}
exp_node* UnOpNode(unop operation, exp_node * expr) {
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = unop_exp;
    node->data.un_ops.op = operation;
    node->data.un_ops.e = expr;
    return node;
}
exp_node * PlusNode(struct exp_node * left_exp, struct exp_node* right_expr) {
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = plus_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * MinusNode(struct exp_node * left_exp, struct exp_node* right_expr) {
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = minus_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * MulNode(struct exp_node * left_exp, struct exp_node* right_expr) {
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = mul_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * DivNode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = div_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * RemNode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = rem_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * LTNode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = lt_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * LENode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = le_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * GTNode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = gt_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * GENode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = ge_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * EQNode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = eq_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * NENode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = ne_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * BANDNode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = band_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * BORNode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = bor_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * XORNode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = xor_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * ANDNode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = and_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * ORNode(struct exp_node * left_exp, struct exp_node* right_expr){
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = or_exp;
    node->data.plus_ops.left_exp = left_exp;
    node->data.plus_ops.right_expr = right_expr;
    return node;
}
exp_node * FunCallNode(char * name, list * args_exp) {
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = funcall_exp;
    node->data.funcall_op.name = name;
    node->data.funcall_op.args_exp = args_exp;
    return node;
}
exp_node * ArrayAccessNode(char * name, exp_node * ind_exp) {
    exp_node* node = malloc(sizeof(exp_node));
    node->kind = array_access_exp;
    node->data.array_access_ops.name = name;
    node->data.array_access_ops.ind_exp = ind_exp;
    return node;
}



stmt_node* RetNode(exp_node* e){
    stmt_node* node = malloc(sizeof(stmt_node));
    node->kind = ret_stmt;
    node->data.ret_exp = e;
    return node;
}

stmt_node* IfNode(exp_node* cond, list * thenStmts, list * elseStmts) {
    stmt_node* node = malloc(sizeof(stmt_node));
    node->kind = if_stmt;
    node->data.if_ops.cond = cond;
    node->data.if_ops.then_stmts = thenStmts;
    node->data.if_ops.else_stmts = elseStmts;
    return node;
}
stmt_node* WhileNode(exp_node *cond, list *thenStmts, list *otherwiseStmts) {
    stmt_node* node = malloc(sizeof(stmt_node));
    node->kind = while_stmt;
    node->data.while_ops.cond = cond;
    node->data.while_ops.then_stmts = thenStmts;
    node->data.while_ops.otherwise_stmts = otherwiseStmts;
    return node;
}
stmt_node *RepeatNode(exp_node *times, list *stmts) {
    stmt_node* node = malloc(sizeof(stmt_node));
    node->kind = repeat_stmt;
    node->data.repeat_ops.times = times;
    node->data.repeat_ops.stmts = stmts;
    return node;
}
stmt_node* AssignNode(char * name, exp_node * exp) {
    stmt_node* node = malloc(sizeof(stmt_node));
    node->kind = assign_stmt;
    node->data.assign_ops.name = name;
    node->data.assign_ops.exp = exp;
    return node;
}
stmt_node* ExpNode(exp_node* exp) {
    stmt_node* node = malloc(sizeof(stmt_node));
    node->kind = exp_stmt;
    node->data.exp_ops.exp = exp;
    return node;
}
stmt_node * ArrayAssignNode(char * name, exp_node * idx_exp, exp_node * assign_exp) {
    stmt_node* node = malloc(sizeof(stmt_node));
    node->kind = array_assign_stmt;
    node->data.array_assign_ops.name = name;
    node->data.array_assign_ops.ind_exp = idx_exp;
    node->data.array_assign_ops.assign_exp = assign_exp;
    return node;
}

vardec_node * VarDecNode(char * name, ty_node * type, exp_node * init) {
    vardec_node* node = malloc(sizeof(vardec_node));
    node->name = name;
    node->type = type;
    node->init = init;
    node->implicit = 0;
    node->array = 0;
    //node->dec = 0;
    node->manually = 0;
    return node;
}
vardec_node * VarDecNodeImp(char * name, ty_node * type, exp_node * init) {
    vardec_node* node = malloc(sizeof(vardec_node));
    node->name = name;
    node->type = type;
    node->init = init;
    node->implicit = 1;
    node->array = 0;
    //node->dec = 0;
    node->manually = 0;
    return node;
}

vardec_node * VarDecNodeImpManually(char * name, ty_node * type, exp_node * init) {
    vardec_node* node = malloc(sizeof(vardec_node));
    node->name = name;
    node->type = type;
    node->init = init;
    node->implicit = 1;
    node->array = 0;
    //node->dec = 0;
    node->manually = 1;
    return node;
}
vardec_node * ArrayDecNode(char * name, ty_node *type, int size) {
    vardec_node* node = malloc(sizeof(vardec_node));
    node->name = name;
    node->type = type;
    node->size = size;
    node->implicit = 0;
    node->array = 1;
    //node->dec = 0;
    node->manually = 0;
    return node;
}
vardec_node * ArrayDecNodeImp(char * name, ty_node *type, int size) {
    vardec_node* node = malloc(sizeof(vardec_node));
    node->name = name;
    node->type = type;
    node->size = size;
    node->implicit = 1;
    node->array = 1;
    //node->dec = 0;
    node->manually = 0;
    return node;
}
/*
fundec_node * FunDecNode(char * name) {
    fundec_node * node = malloc(sizeof(fundec_node));
    node->name = name;
    return node;
}
*/
fundec_node * FunDecNode(char * name, ty_node * type, list * params, list * vardecs, list * statements) {
    fundec_node * node = malloc(sizeof(fundec_node));
    node->name = name;
    node->type = type;
    node->params = params;
    node->vardecs = vardecs;
    node->statements = statements;
    return node;
}

list* ListAddFirst(void* hd, list* lst){
    list* l = malloc(sizeof(list));
    l->head = hd;
    l->next = lst;
    return l;
}

list* ListAddLast(void* hd, list* lst){
    list* l = malloc(sizeof(list));
    l->head = hd;
    l->next = NULL;

    // Empty list
    if (lst == NULL) {
        return l;
    }

    // Find last
    list * last = lst;
    while (last->next != NULL) {
        last = last->next;
    }


    last->next = l;
    return lst;
}
