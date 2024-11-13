#define _POSIX_C_SOURCE 200809L
#include "ast_to_ir.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

__attribute__ ((unused))
static ir_node * ast_to_ir_expr(exp_node * e, S_table global_types, S_table function_decs, frame * f) {

    if(!e) return Nop();
    switch(e->kind){
        case int_exp: {
            assert(0);
        }
        case binop_exp: {
            switch(e->data.bin_ops.op) {
                case plus_op: {
                    assert(0);
                }
                default:
                    assert(0);
            }
            assert(0);
        }
        case unop_exp: {
            assert(0);
        }
        default:
            assert(0); // Dead code
    }
}

static ir_node * ast_to_ir_stmts(list * l, S_table globals_types, S_table function_decs, frame * f);

static ir_node * ast_to_ir_stmt(stmt_node * s, S_table global_types, S_table function_decs, frame * f) {
    if(!s) return Nop();
    switch(s->kind){
        case if_stmt: {
            assert(0);
        }
        case ret_stmt: {
            assert(0);
        }
        default:
            assert(0); // Dead code
    }
}

static ir_node * ast_to_ir_stmts(list * l, S_table globals_types, S_table function_decs, frame * f) {
    if (l == NULL)
        return Nop();

    __attribute__ ((unused))
    ir_node * ir1 = ast_to_ir_stmt(l->head, globals_types, function_decs, f);

    __attribute__ ((unused))
    ir_node * ir2 = ast_to_ir_stmts(l->next, globals_types, function_decs, f);

    // TODO combine ir1 with ir2
    assert(0);
}

static ir_node * ast_to_ir_functions(list * l, S_table global_types, S_table function_decs, S_table frames) {

    ir_node * ret = Nop();

    while (l != NULL) {
        __attribute__ ((unused))
        fundec_node * fundec = (fundec_node*) l->head;

        frame * f = S_look(frames, S_Symbol(fundec->name));
        assert(f != NULL);

        // TODO handle function definitions here


        l = l->next;
    }

    return ret;
}

static ir_node * ast_to_ir_vars (list * l, S_table global_types, S_table function_decs, frame * f) {

    ir_node * ret = Nop();

    while (l != NULL) {
        __attribute__ ((unused))
        vardec_node * var = (vardec_node*) l->head;

        // TODO Handle variable declarations here

        l = l->next;
    }

    return ret;
}

ir_node * ast_to_ir(program* p, S_table globals_types, S_table functions_ret, S_table frames) {

    __attribute__ ((unused))
    ir_node * vars = ast_to_ir_vars(p->variables, globals_types, functions_ret, NULL);

    __attribute__ ((unused))
    ir_node * functions = ast_to_ir_functions(p->functions, globals_types, functions_ret, frames);

    ir_node * stmts = ast_to_ir_stmts(p->statements, globals_types, functions_ret, NULL);

    // TODO combine vars, functions, and stmts

    return stmts;
}
