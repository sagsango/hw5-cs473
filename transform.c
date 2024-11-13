#define _POSIX_C_SOURCE 200809L // enable strdup

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ast.h"
#include "transform.h"

void transformExpr(exp_node * e, S_table global_types, S_table function_decs, frame * f) {
    if(!e) return;
    switch(e->kind){
        case int_exp: {
            // Transform int constants as needed
            break;
        }
        case binop_exp: {
            // Transform binary operations as needed
            // Don't forget to transform the whole AST
            transformExpr(e->data.bin_ops.e1, global_types, function_decs, f);
            transformExpr(e->data.bin_ops.e2, global_types, function_decs, f);
            break;
        }
        case unop_exp: {
            // Transform unary operations as needed
            // Don't forget to transform the whole AST
            transformExpr(e->data.un_ops.e, global_types, function_decs, f);
            break;
        }
        // TODO transform the rest of the expressions in the AST as needed
        case funcall_exp:
            break;
        case str_exp:
            break;
        default:
            assert(0);
    }
}

void transformStmts(list * l, S_table global_types, S_table function_decs, frame * f) {
    if (l == NULL) return;

    stmt_node * s = l->head;
    if(!s) return;
    switch(s->kind){
        case if_stmt: {
            // Transform if statements as needed
            // Don't forget to traverse the whole AST
            transformExpr(s->data.if_ops.cond, global_types, function_decs, f);
            transformStmts(s->data.if_ops.then_stmts, global_types, function_decs, f);
            transformStmts(s->data.if_ops.else_stmts, global_types, function_decs, f);
            break;
        }
        case ret_stmt: {
            // Transform if statements as needed
            // Don't forget to traverse the whole AST
            transformExpr(s->data.ret_exp, global_types, function_decs, f);
            break;
        }
        // TODO transform the rest of the statements in the AST as needed
        default:
            break;
    }

    transformStmts(l->next, global_types, function_decs, f);
}

void transformVariable(vardec_node * node, S_table globals_types, S_table function_decs, frame * f) {
    // Transform variable declarations as needed
}

void transformVariables(list * l, S_table global_types, S_table function_decs, frame * f) {
    if (l == NULL) return;
    transformVariable((vardec_node *)l->head, global_types, function_decs, f);
    transformVariables(l->next, global_types, function_decs, f);
}

void transformFunction(fundec_node * fundec, S_table globals, S_table functions_rets, frame * f) {
    // Transform function declarations as needed
    transformStmts(fundec->body, globals, functions_rets, f);

    if (fundec->ret == VoidTyNode())
        ListAddLast(RetNode(NULL), fundec->body);
}

void transformFunctions(list * l, S_table global_types, S_table function_decs, S_table frames) {
    if (l == NULL) return;
    fundec_node * fundec = (fundec_node*) l->head;
    frame * f = S_look(frames, S_Symbol(fundec->name));
    assert(f != NULL);
    transformFunction(fundec, global_types, function_decs, f);
    transformFunctions(l->next, global_types, function_decs, frames);
}

void transform(program * p, S_table global_types, S_table function_decs, S_table frames) {
    transformVariables(p->variables, global_types, function_decs, NULL);
    transformFunctions(p->functions, global_types, function_decs, frames);
    transformStmts(p->statements, global_types, function_decs, NULL);
}
