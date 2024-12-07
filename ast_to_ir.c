#define _POSIX_C_SOURCE 200809L
#include "ast_to_ir.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "y.tab.h"

static ir_node * ast_to_ir_expr(exp_node * e, S_table global_types, S_table function_decs, frame * f) {

    if(!e) return Nop();
    switch(e->kind){
        case int_exp: {
            ir_node * ret = Iconst(e->data.ival);
            return ret;
            //assert(0);
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
            if (e->data.un_ops.op == not_op) {
                ir_node * exp = ast_to_ir_expr(e->data.un_ops.e, global_types, function_decs, f);
                ir_node * not_op = Ops(ir_not);
                not_op->tree_ir_1 = exp;
                return not_op;
            }
            assert(0);
        }
        case plus_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.plus_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.plus_ops.right_expr, global_types, function_decs, f);
            ir_node * plus_op = Ops(ir_add);
            plus_op->tree_ir_1 = left_exp;
            plus_op->tree_ir_2 = right_exp;
            return plus_op;
        }
        case minus_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.minus_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.minus_ops.right_expr, global_types, function_decs, f);
            ir_node * minus_op = Ops(ir_sub);
            minus_op->tree_ir_1 = left_exp;
            minus_op->tree_ir_2 = right_exp;
            return minus_op;
        }
        case bor_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * bor_op = Ops(ir_bor);
            bor_op->tree_ir_1 = left_exp;
            bor_op->tree_ir_2 = right_exp;
            return bor_op;
        }
        case band_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * band_op = Ops(ir_band);
            band_op->tree_ir_1 = left_exp;
            band_op->tree_ir_2 = right_exp;
            return band_op;
        }
        case xor_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * xor_op = Ops(ir_xor);
            xor_op->tree_ir_1 = left_exp;
            xor_op->tree_ir_2 = right_exp;
            return xor_op;
        }
        case mul_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * mul_op = Ops(ir_mul);
            mul_op->tree_ir_1 = left_exp;
            mul_op->tree_ir_2 = right_exp;
            return mul_op;
        }
        case div_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * div_op = Ops(ir_div);
            div_op->tree_ir_1 = left_exp;
            div_op->tree_ir_2 = right_exp;
            return div_op;
        }
        case rem_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * mod_op = Ops(ir_mod);
            mod_op->tree_ir_1 = left_exp;
            mod_op->tree_ir_2 = right_exp;
            return mod_op;
        }
        case lt_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * lt_op = Ops(ir_lt);
            lt_op->tree_ir_1 = left_exp;
            lt_op->tree_ir_2 = right_exp;
            return lt_op;
        }
        case le_exp: { // Change
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * gt_op = Ops(ir_gt);
            gt_op->tree_ir_1 = left_exp;
            gt_op->tree_ir_2 = right_exp;

            ir_node * not_op = Ops(ir_not);
            not_op->tree_ir_1 = gt_op;
            return not_op;
        }
        case gt_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * lt_op = Ops(ir_gt);
            lt_op->tree_ir_1 = left_exp;
            lt_op->tree_ir_2 = right_exp;
            return lt_op;
        }
        case ge_exp: { // Change
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * lt_op = Ops(ir_lt);
            lt_op->tree_ir_1 = left_exp;
            lt_op->tree_ir_2 = right_exp;

            ir_node * not_op = Ops(ir_not);
            not_op->tree_ir_1 = lt_op;
            return not_op;
        }
        case eq_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * lt_op = Ops(ir_eq);
            lt_op->tree_ir_1 = left_exp;
            lt_op->tree_ir_2 = right_exp;
            return lt_op;
        }
        case ne_exp: { // Change
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * ne_op = Ops(ir_eq);
            ne_op->tree_ir_1 = left_exp;
            ne_op->tree_ir_2 = right_exp;

            ir_node * not_op = Ops(ir_not);
            not_op->tree_ir_1 = ne_op;
            return not_op;
        }
        case or_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * lt_op = Ops(ir_or);
            lt_op->tree_ir_1 = left_exp;
            lt_op->tree_ir_2 = right_exp;
            return lt_op;
        }
        case and_exp: {
            ir_node * left_exp = ast_to_ir_expr(e->data.or_ops.left_exp, global_types, function_decs, f);
            ir_node * right_exp = ast_to_ir_expr(e->data.or_ops.right_expr, global_types, function_decs, f);
            ir_node * lt_op = Ops(ir_and);
            lt_op->tree_ir_1 = left_exp;
            lt_op->tree_ir_2 = right_exp;
            return lt_op;
        }
        case name_exp: {
            // TODO: If var is local then do ArgLocalRead(pos);
            if (f && S_look(f->indexes, S_Symbol(e->data.namevar))) {
                long pos = (long)S_look(f->indexes, S_Symbol(e->data.namevar));
                //fprintf(stderr, "pos@: %ld\n", pos);
                ir_node * read_node = ArgLocalRead(pos-1);
                return read_node;
            }
            ir_node * read_node = Read(e->data.namevar);
            return read_node;
        }
        case string_exp: {
            char * str = strdup(e->data.strval);
            int len = strlen(str);
            str[len-1] = '\0';
            ir_node * read_node = Sconst(str+1);
            //fprintf(stderr, "%s: len:%ld\n", e->data.strval, strlen(e->data.strval));
            return read_node;
        }
        case funcall_exp: {
            /*ir_label * fun = namedLabel(e->data.funcall_op.name);
            assert (e->data.funcall_op.args_exp == NULL);
            ir_node * call = Call(fun, 0);
            return call;*/

            if (strcmp("exit", e->data.funcall_op.name) == 0) {
                /// hanlde exit
                ir_node * ret = Intrinsic(intrinsic_exit);
                ir_node * arg = ast_to_ir_expr(e->data.funcall_op.args_exp->head, global_types, function_decs, f);
                ret->tree_ir_1 = arg;
                return ret;
            }
            if (strcmp("printint", e->data.funcall_op.name) == 0) {
                /// hanlde exit
                ir_node * ret = Intrinsic(intrinsic_print_int);
                ir_node * arg = ast_to_ir_expr(e->data.funcall_op.args_exp->head, global_types, function_decs, f);
                ret->tree_ir_1 = arg;
                return ret;
            }
            if (strcmp("printstring", e->data.funcall_op.name) == 0) {
                /// hanlde exit
                ir_node * ret = Intrinsic(intrinsic_print_string);
                ir_node * arg = ast_to_ir_expr(e->data.funcall_op.args_exp->head, global_types, function_decs, f);
                ret->tree_ir_1 = arg;
                return ret;
            }

           // assert (s->data.exp_ops.exp->data.funcall_op.args_exp == NULL);
            ir_node * eval_args = Nop();
            list * args = e->data.funcall_op.args_exp;
            int nargs = 0;
            while (args != NULL) {
                exp_node * arg = (exp_node*) args->head;
                ir_node * eval_arg = ast_to_ir_expr(arg, global_types, function_decs, f);
                eval_args = Seq(eval_args, eval_arg);
                args = args->next;
                nargs += 1;
            }

            ir_node * fun_call = Call(namedLabel(e->data.funcall_op.name), nargs);
            fun_call->tree_ir_1 = eval_args;
            return fun_call;
            assert (0);

            assert (0);

            break;

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
            /*
             *  It will be Branch
             *  ir_node * Branch(ir_label * lbl);
             *  jump on zero value on the top of stack
             *  So we might need too add not before the expression -> !(expression)
             *  ir_label * freshLabel();
             */
            ir_label *l1 = freshLabel();
            ir_label *l2 = freshLabel();

            // end eveything
            ir_label *end_label = freshLabel();
            ir_node *end_node = Label(end_label);
            // end node
            ir_node *jump_end_node1 = Jump(end_label);
            ir_node *jump_end_node2 = Jump(end_label);


            ir_node *cond = ast_to_ir_expr(s->data.if_ops.cond, global_types, function_decs, f);
            ir_node *then_nodes = ast_to_ir_stmts(s->data.if_ops.then_stmts, global_types, function_decs, f);
            ir_node *else_nodes = ast_to_ir_stmts(s->data.if_ops.else_stmts, global_types, function_decs, f);


            ir_node * then_label = Label(l1);
            then_label->tree_ir_1 = Seq(then_nodes,jump_end_node1);

            ir_node * else_label = Label(l2);
            else_label->tree_ir_1 = Seq(else_nodes, jump_end_node2);


            ir_node * if_branch = Branch(l2);
            if_branch->tree_ir_1 = cond;       // TODO: Add ! before the cond
            if_branch->tree_ir_2 = then_label;
            if_branch->tree_ir_3 = else_label;

            return Seq(if_branch,end_node);

            assert(0);
        }
        case ret_stmt: {
            if (f == 0){ // Global Scope
                ir_node * ret = Intrinsic(intrinsic_exit);
                ir_node * ex_node = ast_to_ir_expr(s->data.ret_exp, global_types, function_decs, f);
                ret->tree_ir_1 = ex_node;
                return ret;
            } else {    // Function Scope
                ir_node * rt_node = Return();
                // Void returns the int val -474
                ir_node * ex_node = s->data.ret_exp ?
                                    ast_to_ir_expr(s->data.ret_exp, global_types, function_decs, f) :
                                    Iconst(-474);
                rt_node->tree_ir_1 = ex_node;
                return rt_node;
            }
        }
        case exp_stmt: {
            ir_node * exp_node = ast_to_ir_expr(s->data.exp_ops.exp, global_types, function_decs, f);
            switch(s->data.exp_ops.exp->kind) {
                case funcall_exp: {
                    if (strcmp("exit", s->data.exp_ops.exp->data.funcall_op.name) != 0 &&
                        strcmp("printint", s->data.exp_ops.exp->data.funcall_op.name) != 0 &&
                        strcmp("printstring", s->data.exp_ops.exp->data.funcall_op.name) != 0)
                        exp_node = Seq(exp_node, Pop());
                    break;
                }
                default:
                    break;
            }
            return exp_node;
            /*switch(s->data.exp_ops.exp->kind) {
                case funcall_exp:
                    if (strcmp("exit", s->data.exp_ops.exp->data.funcall_op.name) == 0) {
                        /// hanlde exit
                        ir_node * ret = Intrinsic(intrinsic_exit);
                        ir_node * arg = ast_to_ir_expr(s->data.exp_ops.exp->data.funcall_op.args_exp->head, global_types, function_decs, f);
                        ret->tree_ir_1 = arg;
                        return ret;
                    }
                    if (strcmp("printint", s->data.exp_ops.exp->data.funcall_op.name) == 0) {
                        /// hanlde exit
                        ir_node * ret = Intrinsic(intrinsic_print_int);
                        ir_node * arg = ast_to_ir_expr(s->data.exp_ops.exp->data.funcall_op.args_exp->head, global_types, function_decs, f);
                        ret->tree_ir_1 = arg;
                        return ret;
                    }
                    if (strcmp("printstring", s->data.exp_ops.exp->data.funcall_op.name) == 0) {
                        /// hanlde exit
                        ir_node * ret = Intrinsic(intrinsic_print_string);
                        ir_node * arg = ast_to_ir_expr(s->data.exp_ops.exp->data.funcall_op.args_exp->head, global_types, function_decs, f);
                        ret->tree_ir_1 = arg;
                        return ret;
                    }
                   // assert (s->data.exp_ops.exp->data.funcall_op.args_exp == NULL);

                    ir_node * eval_args = Nop();
                    list * args = s->data.exp_ops.exp->data.funcall_op.args_exp;
                    int nargs = 0;
                    while (args != NULL) {
                        exp_node * arg = (exp_node*) args->head;
                        ir_node * eval_arg = ast_to_ir_expr(arg, global_types, function_decs, f);
                        eval_args = Seq(eval_args, eval_arg);
                        args = args->next;
                        nargs += 1;
                    }

                    ir_node * fun_call = Call(namedLabel(s->data.exp_ops.exp->data.funcall_op.name), nargs);
                    fun_call->tree_ir_1 = eval_args;
                    fun_call = Seq(fun_call, Pop());
                    return fun_call;
                    assert (0);
                default:
                    assert (0);
            }*/
            break;

        }
        case assign_stmt: {
            // TODO: If var is local then do ArgLocalRead(int i)
            if (f && S_look(f->indexes, S_Symbol(s->data.assign_ops.name))) {
                long pos = (long)S_look(f->indexes, S_Symbol(s->data.assign_ops.name));
                ir_node * exp =  ast_to_ir_expr(s->data.assign_ops.exp, global_types, function_decs, f);
                ir_node * write  = ArgLocalWrite(pos-1);
                write->tree_ir_1 = exp;
                return write;
            }
            //ir_node * name = NameNode(s->data.assign_ops.name);
            ir_node * exp =  ast_to_ir_expr(s->data.assign_ops.exp, global_types, function_decs, f);
            ir_node * node = Write(s->data.assign_ops.name);
            node->tree_ir_1 = exp;
            return node;
	        assert(0);
        }
        case while_stmt: {
            {

                /* Without this cond our code goes more than 30,000 Line in 09/pass10.bluejay */
                if (s->data.while_ops.otherwise_stmts == NULL) {
                    /*
                     *  L0:
                     *      cond
                     *      branch if zero L1
                     *      {
                     *          Body
                     *          jump L0:
                     *       }
                     *  L1:
                     *
                     */

                    ir_label *l0 = freshLabel(); // 0
                    ir_label *l1 = freshLabel(); // 1


                    ir_node *cond = ast_to_ir_expr(s->data.while_ops.cond, global_types, function_decs, f);

                    ir_node *then_nodes = ast_to_ir_stmts(s->data.while_ops.then_stmts, global_types, function_decs, f);
                    then_nodes = Seq(then_nodes, Jump(l0));

                    ir_node * while_branch = Branch(l1);
                    while_branch->tree_ir_1 = cond;
                    while_branch->tree_ir_2 = then_nodes;
                    while_branch->tree_ir_3 = Label(l1);

                    ir_node * L0 = Label(l0);
                    L0->tree_ir_1 = Nop();

                    return Seq(L0, while_branch);

                }

                ir_label *l1 = freshLabel(); // 0
                ir_label *l2 = freshLabel(); // 1

                // end eveything
                ir_label *end_label = freshLabel(); // 2
                ir_node *end_node = Label(end_label);
                // end node
                ir_node *jump_end_node1 = Jump(end_label);
                ir_node *jump_end_node2 = Jump(end_label);

                // 1st cond node
                ir_node *cond = ast_to_ir_expr(s->data.while_ops.cond, global_types, function_decs, f);

                // 1st then node
                ir_node *then_nodes1 = ast_to_ir_stmts(s->data.while_ops.then_stmts, global_types, function_decs, f);
                ir_node * then_label1 = Label(l1);
                then_label1->tree_ir_1 = then_nodes1;
                {
                    // after then node
                    // while (cond) body

                    // 2nd cond node
                    ir_label *l3 = freshLabel(); // 3
                    ir_node * cond_label2 = Label(l3);
                    ir_node *cond2 = ast_to_ir_expr(s->data.while_ops.cond, global_types, function_decs, f);
                    cond_label2->tree_ir_1 = cond2;



                    // 2nd then node
                    ir_node * jmp_node_cond2 = Jump(l3);
                    ir_node *then_nodes2 = ast_to_ir_stmts(s->data.while_ops.then_stmts, global_types, function_decs, f);
                    then_nodes2 = Seq(then_nodes2, jmp_node_cond2);


                    ir_node * while_branch = Branch(end_label);
                    while_branch->tree_ir_1 = cond_label2;
                    while_branch->tree_ir_2 = then_nodes2;
                    while_branch->tree_ir_3 = jump_end_node2;


                    // join
                    then_label1 = Seq(then_nodes1, while_branch);
                }


                // 1st else node
                ir_node *else_nodes1 = ast_to_ir_stmts(s->data.while_ops.otherwise_stmts, global_types, function_decs, f);
                ir_node * else_label1 = Label(l2);
                else_label1->tree_ir_1 = else_nodes1;


                ir_node * if_branch = Branch(l2);
                if_branch->tree_ir_1 = cond;       // TODO: Add ! before the cond
                if_branch->tree_ir_2 = then_label1;
                if_branch->tree_ir_3 = Seq(else_label1, jump_end_node1);

                return Seq(if_branch, end_node);

            }


            //return while_branch;
        }
        case repeat_stmt: {
           assert (0);


        }
        default:
            assert(0); // Dead code
    }
}


/*
**
**
** Get Rid of this
**
**
*/
/*
static ir_node * ast_to_ir_stmts2(list * l, S_table globals_types, S_table function_decs, frame * f) {
    if (l == NULL)
        return Nop();

    __attribute__ ((unused))
    ir_node * ir1 = ast_to_ir_stmt(l->head, globals_types, function_decs, f);

    __attribute__ ((unused))
    ir_node * ir2 = ast_to_ir_stmts(l->next, globals_types, function_decs, f);

    // TODO combine ir1 with ir2
    ir_node * ret = Seq(ir2, ir1); // TODO: Get rid of this, when creating list we will rem Seq, (because interpreter dont support)
    return ret;
    assert(0);
}*/


static ir_node * ast_to_ir_stmts(list * l, S_table globals_types, S_table function_decs, frame * f) {
    if (l == NULL)
        return Nop();

    __attribute__ ((unused))
    ir_node * ir1 = ast_to_ir_stmt(l->head, globals_types, function_decs, f);

    __attribute__ ((unused))
    ir_node * ir2 = ast_to_ir_stmts(l->next, globals_types, function_decs, f);

    // TODO combine ir1 with ir2; What about general case?
    ir_node * ret = Seq(ir1, ir2); // TODO: Get rid of this, when creating list we will rem Seq, (because interpreter dont support)
    return ret;
    assert(0);
}

static ir_node * ast_to_ir_vars (list * l, S_table global_types, S_table function_decs, frame * f);
extern program p;
static ir_node * ast_to_ir_function(fundec_node * fundec, S_table global_types, S_table function_decs, S_table frames) {
    /* this is always global scope
     * We are going to get the frame info about the function
     */
    frame * f = S_look(frames, S_Symbol(fundec->name));
    assert(f != NULL);

    /*
    **
    **
    **
    **
    ** Everything about the function should be done here
    ** 1. Declation
    ** 2. Body
         A. Declaration
         B. Statements
        We should call here ast_to_ir_vars
    ** 3. Return
    **
    **
    **
    **
    **
    **
    */

    // TODO: How to use function_decs here?


    //assert (f->n_args + f->n_imp + f->n_index == 0);

    ir_label * fun_label = namedLabel(fundec->name);
    // TODO: 1 or -1 should be taken care!!
    //fprintf(stderr, "total-index: %ld\n", f->n_index);
    ir_node  * fun_node = Function(fun_label,f->n_index+f->n_imp);

    ir_node * dec = ast_to_ir_vars(fundec->vardecs, global_types, function_decs, f); // fist local and args
    dec = Seq(dec, ast_to_ir_vars(p.variables, global_types, function_decs, f)); // Implicit
    ir_node * stmnts = ast_to_ir_stmts(fundec->statements, global_types, function_decs, f);

    fun_node->tree_ir_1 = dec;
    fun_node->tree_ir_2 = stmnts;
    //assert(0);

    return fun_node;
}


static ir_node * ast_to_ir_functions(list * l, S_table global_types, S_table function_decs, S_table frames) {
    if (l == NULL) return Nop();
    ir_node * ir1 = ast_to_ir_function(l->head, global_types, function_decs, frames);
    ir_node * ir2 = ast_to_ir_functions(l->next, global_types, function_decs, frames);

    ir_node * ret = Seq(ir1, ir2);
    return ret;
}


static ir_node * ast_to_ir_var (vardec_node * var, S_table global_types, S_table function_decs, frame * f) {

    /*
        This will be called from 2 scopes.
        1. Global
    `	2. Local

        We must make glocal_type = NULL; when in the local scope
        We must make frame = NULL when it the global scope
    */

    // TODO Handle variable declarations here
    if (var->array) assert(0);



    if (f == 0) {   // Global vars
        // TODO: Only int ??
        if (var->implicit) {
            return NULL;
        }
       //  fprintf(stderr, "global:%s, f:%ld, imp:%d, manually:%d\n", var->name, (long)f, var->implicit, (int)var->manually);
        if (var->type->kind == int_ty) {
            ir_node * dec = Reserve(4, var->name, NULL);
            ir_node * init = Write(var->name);
            init->tree_ir_1 = ast_to_ir_expr(var->init, global_types, function_decs, f);
            return Seq(dec, init);
        }
        if (var->type->kind == string_ty) {
            char * str = strdup(var->init->data.strval);
            int len = strlen(str);
            str[len-1] = '\0';
            ir_node * dec = Reserve(strlen(str+1)+1, var->name, str+1);
            ir_node * init = Write(var->name);
            init->tree_ir_1 = ast_to_ir_expr(var->init, global_types, function_decs, f);
            return Seq(dec, init);
        }
    }
    // fprintf(stderr, "local/args/imp:%s, f:%ld, imp:%d, local_arg:%ld, manually:%d\n", var->name, (long)f, var->implicit, (long)S_look(f->args_locs_types, S_Symbol(var->name)), (int)var->manually);
    if (f != 0) { // for function, local + args + implicit
        if( S_look(f->indexes, S_Symbol(var->name)) != NULL  && S_look(f->args, S_Symbol(var->name)) == NULL) {
            if (S_look(f->seen, S_Symbol(var->name)) != NULL ) {
                return NULL;
            }
            S_enter(f->seen, S_Symbol(var->name), (void *) 100);

            long pos = (long)S_look(f->indexes, S_Symbol(var->name));
            if (var->type->kind == int_ty) {
                ir_node * write = ArgLocalWrite(pos-1);
                write->tree_ir_1 = ast_to_ir_expr(var->init, global_types, function_decs, f);
                return write;
            }
            if (var->type->kind == string_ty) {
                ir_node * write = ArgLocalWrite(pos-1);
                write->tree_ir_1 = ast_to_ir_expr(var->init, global_types, function_decs, f);
                return write;
            }
        }
        return NULL;
    }
    assert(0);
    return NULL;

}
static ir_node * ast_to_ir_vars (list * l, S_table global_types, S_table function_decs, frame * f) {

    if (l == NULL)
        return Nop();

    __attribute__ ((unused))
    ir_node * ir1 = ast_to_ir_var(l->head, global_types, function_decs, f);

    __attribute__ ((unused))
    ir_node * ir2 = ast_to_ir_vars(l->next, global_types, function_decs, f);

    // TODO combine ir1 with ir2; What about general case?
    ir_node * ret = Seq(ir1, ir2); // TODO: Get rid of this, when creating list we will rem Seq, (because interpreter dont support)
    return ret;
}




ir_node * ast_to_ir(program* p, S_table globals_types, S_table functions_ret, S_table frames) {

    __attribute__ ((unused))
    ir_node * vars = ast_to_ir_vars(p->variables, globals_types, functions_ret, NULL);


    ir_label *jump_over_functions = freshLabel();

    __attribute__ ((unused))
    ir_node * functions = ast_to_ir_functions(p->functions, globals_types, functions_ret, frames);


    functions = Seq(Jump(jump_over_functions), functions);

    ir_node * stmts = ast_to_ir_stmts(p->statements, globals_types, functions_ret, NULL);

    stmts = Seq(Label(jump_over_functions), stmts);
    // TODO combine vars, functions, and stmts


    /* Always should be exit() */
    ir_node *_exit = Intrinsic(intrinsic_exit);
    ir_node * _arg = Iconst(0);
    _exit->tree_ir_1 = _arg;


    ir_node * ret = Nop(); ret->kind = ir_program;
    ret->tree_ir_1 = vars;
    ret->tree_ir_2 = functions;
    ret->tree_ir_3 = Seq(stmts, _exit);


    
    return ret;


}
