#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "semantic_analysis_symbols.h"

#define _Exit(a) {  assert(0); _Exit(a); }
void symbolResolutionExpr(exp_node * e, S_table global_types, S_table function_decs, frame * f) {

    if(!e) return;
    switch(e->kind){
        case int_exp: {
            return; // NO variables to check
            //assert(0); // Not implemented
        }
        case binop_exp: {
            assert(0); // Not implemented
        }
        case unop_exp: {
            symbolResolutionExpr(e->data.un_ops.e, global_types, function_decs, f);
            //assert(0); // Not implemented
            break;
        }
        // TODO add more cases for all expressions
        case string_exp: {
            return; // No variable to check
        }
        case plus_exp: {
            exp_node * left_exp = e->data.plus_ops.left_exp;
            exp_node * right_exp = e->data.plus_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case minus_exp: {
            exp_node * left_exp = e->data.minus_ops.left_exp;
            exp_node * right_exp = e->data.minus_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case mul_exp: {
            exp_node * left_exp = e->data.mul_ops.left_exp;
            exp_node * right_exp = e->data.mul_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case div_exp: {
            exp_node * left_exp = e->data.div_ops.left_exp;
            exp_node * right_exp = e->data.div_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case rem_exp: {
            exp_node * left_exp = e->data.rem_ops.left_exp;
            exp_node * right_exp = e->data.rem_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case lt_exp: {
            exp_node * left_exp = e->data.lt_ops.left_exp;
            exp_node * right_exp = e->data.lt_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case le_exp: {
            exp_node * left_exp = e->data.le_ops.left_exp;
            exp_node * right_exp = e->data.le_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case gt_exp: {
            exp_node * left_exp = e->data.gt_ops.left_exp;
            exp_node * right_exp = e->data.gt_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case ge_exp: {
            exp_node * left_exp = e->data.ge_ops.left_exp;
            exp_node * right_exp = e->data.ge_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case eq_exp: {
            exp_node * left_exp = e->data.eq_ops.left_exp;
            exp_node * right_exp = e->data.eq_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case ne_exp: {
            exp_node * left_exp = e->data.ne_ops.left_exp;
            exp_node * right_exp = e->data.ne_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case band_exp: {
            exp_node * left_exp = e->data.band_ops.left_exp;
            exp_node * right_exp = e->data.band_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case bor_exp: {
            exp_node * left_exp = e->data.bor_ops.left_exp;
            exp_node * right_exp = e->data.bor_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case xor_exp: {
            exp_node * left_exp = e->data.xor_ops.left_exp;
            exp_node * right_exp = e->data.xor_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case and_exp: {
            exp_node * left_exp = e->data.and_ops.left_exp;
            exp_node * right_exp = e->data.and_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case or_exp: {
            exp_node * left_exp = e->data.or_ops.left_exp;
            exp_node * right_exp = e->data.or_ops.right_expr;
            symbolResolutionExpr(left_exp, global_types, function_decs, f);
            symbolResolutionExpr(right_exp, global_types, function_decs, f);
            return;
        }
        case name_exp: {
            // check in local;
            // check in global;
            //vardec_node * dec = S_look(global_types, S_Symbol(e->data.namevar));
            //fprintf (stderr, "[%s:%s]\n", dec->name, typeToStr(dec->type));
            if ( S_look(global_types, S_Symbol(e->data.namevar)) == NULL &&
                 (!f || S_look(f->args_locs_types, S_Symbol(e->data.namevar)) == NULL) ) {
                _Exit(73);
            }
            break;
        }
        case funcall_exp: {
            if ( S_look(function_decs, S_Symbol(e->data.funcall_op.name)) == NULL ) {
                _Exit(73);
            }
            list * l = e->data.funcall_op.args_exp;
            while (l) {
                exp_node * exp = (exp_node*) l->head;
                symbolResolutionExpr(exp, global_types, function_decs, f);
                l = l->next;
            }
            break;
        }
        case array_access_exp: {
            if ( S_look(global_types, S_Symbol(e->data.array_access_ops.name)) == NULL &&
                (!f || S_look(f->args_locs_types, S_Symbol(e->data.array_access_ops.name)) == NULL) ) {
                _Exit(73);
            }
            symbolResolutionExpr(e->data.array_access_ops.ind_exp, global_types, function_decs, f);
            break;
        }
        default:
            assert(0); // Should be dead code
    }
}

void symbolResolutionStmts(list * l, S_table locals, S_table function_decs, frame * f);

void symbolResolutionStmt(stmt_node * s, S_table global_types, S_table function_decs, frame * f) {
    if(!s) return;
    switch(s->kind){
        case if_stmt: {
            exp_node * cond_exp = s->data.if_ops.cond;
            list * then_stmts = s->data.if_ops.then_stmts;
            list * else_stmts = s->data.if_ops.else_stmts;

            symbolResolutionExpr(cond_exp, global_types, function_decs, f);
            symbolResolutionStmts(then_stmts, global_types, function_decs, f);
            symbolResolutionStmts(else_stmts, global_types, function_decs, f);

            break;

            //assert(0); // Not implemented
        }
        case ret_stmt: {
            exp_node * ret_exp = s->data.ret_exp;
            symbolResolutionExpr(ret_exp, global_types, function_decs, f);
            break;
            //assert(0); // Not implemented
        }
        case while_stmt: {
            exp_node * cond_exp = s->data.while_ops.cond;
            list * then_stmts = s->data.while_ops.then_stmts;
            list * otherwise_stmts = s->data.while_ops.otherwise_stmts;

            symbolResolutionExpr(cond_exp, global_types, function_decs, f);
            symbolResolutionStmts(then_stmts, global_types, function_decs, f);
            symbolResolutionStmts(otherwise_stmts, global_types, function_decs, f);
            break;
        }
        case repeat_stmt: {
            exp_node * times_expr = s->data.repeat_ops.times;
            list * stmts = s->data.repeat_ops.stmts;

            symbolResolutionExpr(times_expr, global_types, function_decs, f);
            symbolResolutionStmts(stmts, global_types, function_decs, f);

            break;

        }
        case assign_stmt: {
            char * name = s->data.assign_ops.name;
            exp_node * exp = s->data.assign_ops.exp;

            symbolResolutionExpr(exp, global_types, function_decs, f);

            // TODO: global lookup
            if ( (!f || S_look(f->args_locs_types, S_Symbol(name)) == NULL) &&
                S_look(global_types, S_Symbol(name)) == NULL ) {
                _Exit(73);
            }
            break;
        }
        case exp_stmt: {
            exp_node * exp = s->data.exp_ops.exp;
            symbolResolutionExpr(exp, global_types, function_decs, f);
            break;
        }
        case array_assign_stmt: {
            char * name = s->data.array_assign_ops.name;
            exp_node * idx_exp = s->data.array_assign_ops.ind_exp;
            exp_node * assign_exp = s->data.array_assign_ops.assign_exp;

            symbolResolutionExpr(idx_exp, global_types, function_decs, f);
            symbolResolutionExpr(assign_exp, global_types, function_decs, f);

            // TODO: global lookup
            if ( (!f || S_look(f->args_locs_types, S_Symbol(name)) == NULL) &&
                S_look(global_types, S_Symbol(name)) == NULL ) {
                _Exit(73);
                }

            break;
        }
        // TODO add more cases for all expressions
        default:
            assert(0); // Should be dead code
    }
}

void symbolResolutionStmts(list * l, S_table globals_types, S_table function_decs, frame * f) {
    if (l == NULL) return;
    symbolResolutionStmt(l->head, globals_types, function_decs, f);
    symbolResolutionStmts(l->next, globals_types, function_decs, f);
}

void symbolResolutionVariable(vardec_node * vardec, S_table globals_types, S_table function_decs, frame * f) {
    // TODO figure out if this is a global variable or a local variable
    // TODO Hint:  to start, just assume that everything is a global variable
    int global = 1; //vardec->implicit == 0;

    assert (f  == NULL);
    assert (globals_types);

    if (global) {
        // TODO register global variable types in globals_types
        //fprintf (stderr, "dec[%s:%s]\n", vardec->name, typeToStr(vardec->type));
        if (vardec->array) {
            if ( S_look(globals_types, S_Symbol(vardec->name)) != NULL ) {
                _Exit(73);
            }
            S_enter(globals_types,S_Symbol(vardec->name), vardec);
        }
        else {
            symbolResolutionExpr(vardec->init, globals_types, function_decs, f);
            if ( S_look(globals_types, S_Symbol(vardec->name)) != NULL ) {
                /* If global i, j already declared
                 * We addedd i,j, implicit declaration at the end of vardec list
                 * Yes we are going to choose the first (which is not implicit one)
                 * So skip here this i, j, symbol
                 *
                 */
                if (vardec->manually == 1) {
                    return;
                }
                _Exit(73);
            }
            S_enter(globals_types,S_Symbol(vardec->name), vardec);
        }
    } else {
        // TODO register local variable types in the frame
        assert(0); // Not implemented
    }

    // TODO check that all symbols in the variable initialization are known to fail negative tests


}

void symbolResolutionVariables(list * l, S_table global_types, S_table function_decs, frame * f) {
    if (l == NULL) return;
    symbolResolutionVariable((vardec_node *)l->head, global_types, function_decs, f);
    symbolResolutionVariables(l->next, global_types, function_decs, f);
}

void symbolResolutionFunction(fundec_node * fundec, S_table globals, S_table functions_rets, frame * f) {
    if (S_look(functions_rets, S_Symbol(fundec->name)) != NULL) {
        _Exit(73);
    }

    S_enter(functions_rets, S_Symbol(fundec->name), fundec);

    // TODO add each argument type to the f->args_locs_types
    list * l = NULL;
    l = fundec->params;
    while (l) {
        param * p = (param*) l->head;
        f->n_args += 1;
        S_enter(f->args_locs_types, S_Symbol(p->name), p);
        S_enter(f->args, S_Symbol(p->name), p);
        // TODO: check this name is not present
        if (S_look(f->indexes, S_Symbol(p->name)) != NULL ) {
            _Exit(73);
        }
        if (S_look(globals, S_Symbol(p->name)) != NULL ) {
            vardec_node * vardec = S_look(globals, S_Symbol(p->name));
            if (!vardec->implicit) {
                _Exit(73);
            }
        }
        S_enter(f->indexes, S_Symbol(p->name), (void*)f->n_args);
        l = l->next;
    }

    // TODO add each local variable type to f->args_locs_types
    f->n_index = f->n_args;
    l = fundec->vardecs;
    while (l) {
        vardec_node * vardec = (vardec_node*) l->head;
        if (!vardec->array) {
            symbolResolutionExpr(vardec->init, globals, functions_rets, f);
        }
        f->n_index += 1;
        S_enter(f->args_locs_types, S_Symbol(vardec->name), vardec);
        // TODO: check this name is not present
        if (S_look(f->indexes, S_Symbol(vardec->name)) != NULL ) {
            _Exit(73);
        }
        if (S_look(globals, S_Symbol(vardec->name)) != NULL ) {
            vardec_node * gvar = S_look(globals, S_Symbol(vardec->name));
            if (!gvar->implicit) {
                _Exit(73);
            }
        }
        S_enter(f->indexes, S_Symbol(vardec->name), (void*)f->n_index);
        l = l->next;
    }
    // TODO check that the statements in the body of the function only use known variables and functions
    symbolResolutionStmts(fundec->statements, globals, functions_rets, f);
}

void symbolResolutionFunctions(list * l, S_table global_types, S_table function_decs, S_table frames) {
    if (l == NULL) return;
    fundec_node * fundec = (fundec_node*) l->head;

    // Create a new frame
    frame * f = malloc(sizeof(frame));

    // Initialize all memory so we can read it later
    f->args_locs_types = S_empty();
    f->args = S_empty();
    f->indexes = S_empty();
    f->seen = S_empty();
    f->ret = fundec->type;
    f->n_args = 0;
    f->n_index = 0;
    f->n_imp = 0;

    // Add newly computed frame to frames
    S_enter(frames, S_Symbol(fundec->name), f);  // function itself have frame inside frames

    symbolResolutionFunction(fundec, global_types, function_decs, f); // locals + Args
    symbolResolutionFunctions(l->next, global_types, function_decs, frames);
}

void symbolResolution(program * p, S_table global_types, S_table function_decs, S_table frames) {
    symbolResolutionVariables(p->variables, global_types, function_decs, NULL);    // Global Variables
    symbolResolutionFunctions(p->functions, global_types, function_decs, frames);  // Local variable + Args + FuncItself
    symbolResolutionStmts(p->statements, global_types, function_decs, NULL);
}