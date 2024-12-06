#include <stdlib.h>
#include <assert.h>
#include "semantic_analysis_types.h"
#include <stdio.h>

#define _Exit(a) {  assert(0); _Exit(a); }

ty_node * typeCheckExpr(exp_node * e, S_table global_types, S_table function_decs, frame * f) {

    switch(e->kind){
        case int_exp: {
            return IntTyNode();
            //assert(0); // Not implemented
        }
        case binop_exp: {
            assert(0); // Not implemented
        }
        case unop_exp: {
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(e->data.un_ops.e, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case string_exp: {
            return StringTyNode();
        }
        case name_exp : {
            vardec_node * vardec = NULL;
            if (f) {
                vardec = (vardec_node *) S_look(f->args_locs_types, S_Symbol(e->data.namevar));
                if (vardec != NULL) {
                    return vardec->type;
                }
            }
            vardec = (vardec_node*) S_look(global_types, S_Symbol(e->data.namevar));
            if (vardec != NULL) {
                return vardec->type;
            }
            _Exit(73);
            // assert (vardec); // TODO: check in frame or local variables
            return vardec->type;
        }
        case plus_exp: {
            exp_node * left_exp = e->data.plus_ops.left_exp;
            exp_node * right_exp = e->data.plus_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case minus_exp: {
            exp_node * left_exp = e->data.minus_ops.left_exp;
            exp_node * right_exp = e->data.minus_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case mul_exp: {
            exp_node * left_exp = e->data.mul_ops.left_exp;
            exp_node * right_exp = e->data.mul_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case div_exp: {
            exp_node * left_exp = e->data.div_ops.left_exp;
            exp_node * right_exp = e->data.div_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case rem_exp: {
            exp_node * left_exp = e->data.rem_ops.left_exp;
            exp_node * right_exp = e->data.rem_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case lt_exp: {
            exp_node * left_exp = e->data.lt_ops.left_exp;
            exp_node * right_exp = e->data.lt_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case le_exp: {
            exp_node * left_exp = e->data.le_ops.left_exp;
            exp_node * right_exp = e->data.le_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case gt_exp: {
            exp_node * left_exp = e->data.gt_ops.left_exp;
            exp_node * right_exp = e->data.gt_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case ge_exp: {
            exp_node * left_exp = e->data.ge_ops.left_exp;
            exp_node * right_exp = e->data.ge_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case eq_exp: {
            exp_node * left_exp = e->data.eq_ops.left_exp;
            exp_node * right_exp = e->data.eq_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case ne_exp: {
            exp_node * left_exp = e->data.ne_ops.left_exp;
            exp_node * right_exp = e->data.ne_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case band_exp: {
            exp_node * left_exp = e->data.band_ops.left_exp;
            exp_node * right_exp = e->data.band_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case bor_exp: {
            exp_node * left_exp = e->data.bor_ops.left_exp;
            exp_node * right_exp = e->data.bor_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case xor_exp: {
            exp_node * left_exp = e->data.xor_ops.left_exp;
            exp_node * right_exp = e->data.xor_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case and_exp: {
            exp_node * left_exp = e->data.and_ops.left_exp;
            exp_node * right_exp = e->data.and_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case or_exp: {
            exp_node * left_exp = e->data.or_ops.left_exp;
            exp_node * right_exp = e->data.or_ops.right_expr;
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(left_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            actual = typeCheckExpr(right_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            return actual;
        }
        case funcall_exp: {
            fundec_node * fundec = S_look(function_decs, S_Symbol(e->data.funcall_op.name));
            list * l1 = fundec->params;
            list * l2 = e->data.funcall_op.args_exp;
            while (1) {
                if (l1 == NULL && l2 == NULL) break;
                if (l1 == NULL || l2 == NULL) _Exit(73);
                param * p = (param*) l1->head;
                ty_node * expected = p->ty;
                exp_node * ex = (exp_node*) l2->head;
                ty_node * actual = typeCheckExpr(ex, global_types, function_decs, f);
                if (expected != actual) {
                    _Exit(73);
                }
                l1 = l1->next;
                l2 = l2->next;
            }
            return fundec->type;
        }
        case array_access_exp: {
            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(e->data.array_access_ops.ind_exp, global_types, function_decs, f);
            if (expected != actual) {
                _Exit(73);
            }
            vardec_node * vardec = NULL;
            if (f) {
                vardec = (vardec_node *) S_look(f->args_locs_types, S_Symbol(e->data.array_access_ops.name));
                if (vardec != NULL) {
                    return vardec->type;
                }
            }
            vardec = (vardec_node*) S_look(global_types, S_Symbol(e->data.array_access_ops.name));
            if (vardec != NULL) {
                return vardec->type;
            }
            _Exit(73);

        }
        // TODO add more cases for all expressions
        default:
            assert(0); // Should be dead code
    }
}

void typeCheckStmts(list * l, S_table locals, S_table function_decs, frame * f);

void typeCheckStmt(stmt_node * s, S_table global_types, S_table function_decs, frame * f) {
    if(!s) return;
    switch(s->kind){
        case if_stmt: {
            exp_node * cond_exp = s->data.if_ops.cond;
            list * then_stmts = s->data.if_ops.then_stmts;
            list * else_stmts = s->data.if_ops.else_stmts;

            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(s->data.if_ops.cond, global_types, function_decs, f);
            if (expected != actual) {
                exit(73);
            }

            typeCheckExpr(cond_exp, global_types, function_decs, f);
            typeCheckStmts(then_stmts, global_types, function_decs, f);
            typeCheckStmts(else_stmts, global_types, function_decs, f);
            break;
        }
        case ret_stmt: {
            // TODO function returning diff values
            ty_node * expected = NULL;
            if (f == NULL) {
                expected = IntTyNode();
            } else {
                expected = f->ret;
            }
            ty_node * actual;
            if (s->data.ret_exp != NULL) {
                actual = typeCheckExpr(s->data.ret_exp, global_types, function_decs, f);
            } else {
                actual = VoidTyNode();
            }
            if (expected != actual) {
                //assert (0);
                exit(73);
            }
            break;
        }
        case while_stmt: {
            exp_node * cond_exp = s->data.while_ops.cond;
            list * then_stmts = s->data.while_ops.then_stmts;
            list * otherwise_stmts = s->data.while_ops.otherwise_stmts;

            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(s->data.while_ops.cond, global_types, function_decs, f);
            if (expected != actual) {
                exit(73);
            }

            typeCheckExpr(cond_exp, global_types, function_decs, f);
            typeCheckStmts(then_stmts, global_types, function_decs, f);
            typeCheckStmts(otherwise_stmts, global_types, function_decs, f);
            break;

        }
        case repeat_stmt: {
            exp_node * times_expr = s->data.repeat_ops.times;
            list * stmts = s->data.repeat_ops.stmts;

            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(s->data.repeat_ops.times, global_types, function_decs, f);
            if (expected != actual) {
                exit(73);
            }

            typeCheckExpr(times_expr, global_types, function_decs, f);
            typeCheckStmts(stmts, global_types, function_decs, f);
            break;
        }
        case assign_stmt: {
            char * name = s->data.assign_ops.name;
            exp_node * exp = s->data.assign_ops.exp;

            // TODO: function lookup
            vardec_node * vardec;
            if (f) {
                vardec = S_look(f->args_locs_types, S_Symbol(name));
                if (vardec != NULL) { // local
                    ty_node * expected = vardec->type;
                    ty_node * actual = typeCheckExpr(exp, global_types, function_decs, f);
                    if (expected != actual) {
                        _Exit(73);
                    }
                    break;
                }
            }
            vardec = S_look(global_types, S_Symbol(name));
            if (vardec != NULL) {
                ty_node * expected = vardec->type;
                ty_node * actual = typeCheckExpr(exp, global_types, function_decs, f);
                if (expected != actual) {
                    _Exit(73);
                }
                break;
            }
            _Exit(73);
        }
        case exp_stmt: {
            exp_node * exp = s->data.exp_ops.exp;
            typeCheckExpr(exp, global_types, function_decs, f);
            break;
        }
        case array_assign_stmt: {
            char * name = s->data.array_assign_ops.name;
            exp_node * assign_exp = s->data.array_assign_ops.assign_exp;
            exp_node * idx_exp = s->data.array_assign_ops.ind_exp;

            ty_node * expected = IntTyNode();
            ty_node * actual = typeCheckExpr(idx_exp, global_types, function_decs, f);
            if (expected != actual) {
                exit(73);
            }

            // TODO: function lookup
            vardec_node * vardec;
            if (f) {
                vardec = S_look(f->args_locs_types, S_Symbol(name));
                if (vardec != NULL) { // local
                    ty_node * expected = vardec->type;
                    ty_node * actual = typeCheckExpr(assign_exp, global_types, function_decs, f);
                    if (expected != actual) {
                        _Exit(73);
                    }
                    break;
                }
            }
            vardec = S_look(global_types, S_Symbol(name));
            if (vardec != NULL) {
                ty_node * expected = vardec->type;
                ty_node * actual = typeCheckExpr(assign_exp, global_types, function_decs, f);
                if (expected != actual) {
                    _Exit(73);
                }
                break;
            }
            _Exit(73);
        }
        // TODO add more cases for all expressions
        default:
            assert(0); // Should be dead code
    }
}

void typeCheckStmts(list * l, S_table globals_types, S_table function_decs, frame * f) {
    if (l == NULL) return;
    typeCheckStmt(l->head, globals_types, function_decs, f);
    typeCheckStmts(l->next, globals_types, function_decs, f);
}

void typeCheckVariable(vardec_node * vardec, S_table globals_types, S_table function_decs, frame * f) {
    // TODO ensure that variable initialization expression has the same type as the variable definition
    if (vardec->array) {
        /*
         *  No need to check anything;
         *  We dont support the array initialization
         *  We only support array size known at compile time so it should be NUMBER,
         *  Which already checked by parser
         */
    } else {
        ty_node * expected = vardec->type;
        ty_node * actual = typeCheckExpr(vardec->init, globals_types, function_decs, f);
        if (expected != actual) {
            _Exit(73);
        }
    }
    //assert(0); // Not implemented
}

void typeCheckVariables(list * l, S_table global_types, S_table function_decs, frame * f) {
    if (l == NULL) return;
    typeCheckVariable((vardec_node *)l->head, global_types, function_decs, f);
    typeCheckVariables(l->next, global_types, function_decs, f);
}

void typeCheckFunction(fundec_node * fundec, S_table globals_types, S_table functions_rets, frame * f) {
    // TODO ensure that the body of the function is well typed
    // TODO ensure local variables are initialized with the correct type
    typeCheckVariables(fundec->vardecs, globals_types, functions_rets, f);
    typeCheckStmts(fundec->statements, globals_types, functions_rets, f);
    // TODO return value typecheck
   // assert(0); // Not implemented
}

void typeCheckFunctions(list * l, S_table global_types, S_table function_decs, S_table frames) {
    if (l == NULL) return;
    fundec_node * fundec = (fundec_node*) l->head;
    frame * f = S_look(frames, S_Symbol(fundec->name));
    assert(f);
    typeCheckFunction(fundec, global_types, function_decs, f);
    typeCheckFunctions(l->next, global_types, function_decs, frames);
}

void typeCheck(program * p, S_table global_types, S_table function_decs, S_table frames) {
    typeCheckVariables(p->variables, global_types, function_decs, NULL);
    typeCheckFunctions(p->functions, global_types, function_decs, frames);
    typeCheckStmts(p->statements, global_types, function_decs, NULL);
}