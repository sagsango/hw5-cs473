#include "ir_tree_to_list.h"

#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>

__attribute__ ((unused))
static ir_node * find_last(ir_node * head) {
    if (head->next == NULL)
        return head;
    return find_last(head->next);
}

ir_node * ir_tree_to_list(ir_node * ir) {
    if (ir == NULL) {
        return Nop();
    }

    switch (ir->kind) {
        case ir_nop: {
            return ir;
        }
        // TODO support all IRs, turn them from a tree into a list
        case ir_iconst: {
            return ir;
        }
        case ir_sconst: {
            return ir;
        }
        case ir_array_read: {
            ir_node * idx = ir_tree_to_list(ir->data.array_read.idx);
            find_last(idx)->next = ir;
            return idx;
        }
        case ir_add: {
            // 2 then 1 then op
            ir_node * left_expr = ir_tree_to_list(ir->tree_ir_1);
            ir_node * right_expr = ir_tree_to_list(ir->tree_ir_2);
            find_last(left_expr)->next = right_expr;
            find_last(left_expr)->next = ir;
            return left_expr;
        }
        case ir_sub: {
            // 2 then 1 then op
            ir_node * left_expr = ir_tree_to_list(ir->tree_ir_1);
            ir_node * right_expr = ir_tree_to_list(ir->tree_ir_2);
            find_last(left_expr)->next = right_expr;
            find_last(left_expr)->next = ir;
            return left_expr;
        }
        case ir_mul: {
            ir_node * left_expr = ir_tree_to_list(ir->tree_ir_1);
            ir_node * right_expr = ir_tree_to_list(ir->tree_ir_2);
            find_last(left_expr)->next = right_expr;
            find_last(left_expr)->next = ir;
            return left_expr;
            assert(0);
        }
        case ir_div: {
            ir_node * left_expr = ir_tree_to_list(ir->tree_ir_1);
            ir_node * right_expr = ir_tree_to_list(ir->tree_ir_2);
            find_last(left_expr)->next = right_expr;
            find_last(left_expr)->next = ir;
            return left_expr;
            assert(0);
            assert(0);
        }
        case ir_mod: {
            ir_node * left_expr = ir_tree_to_list(ir->tree_ir_1);
            ir_node * right_expr = ir_tree_to_list(ir->tree_ir_2);
            find_last(left_expr)->next = right_expr;
            find_last(left_expr)->next = ir;
            return left_expr;
            assert(0);
            assert(0);
        }
        case ir_bor: {
            // 2 then 1 then op
            ir_node * left_expr = ir_tree_to_list(ir->tree_ir_1);
            ir_node * right_expr = ir_tree_to_list(ir->tree_ir_2);
            find_last(left_expr)->next = right_expr;
            find_last(left_expr)->next = ir;
            return left_expr;
        }
        case ir_band: {
            // 2 then 1 then op
            ir_node * left_expr = ir_tree_to_list(ir->tree_ir_1);
            ir_node * right_expr = ir_tree_to_list(ir->tree_ir_2);
            find_last(left_expr)->next = right_expr;
            find_last(left_expr)->next = ir;
            return left_expr;
            assert(0);
        }
        case ir_xor: {
            // 2 then 1 then op
            ir_node * left_expr = ir_tree_to_list(ir->tree_ir_1);
            ir_node * right_expr = ir_tree_to_list(ir->tree_ir_2);
            find_last(left_expr)->next = right_expr;
            find_last(left_expr)->next = ir;
            return left_expr;
            assert(0);
        }
        case ir_or: {
            /*
            * <left> : branchz lbl0
            *         iconst(1)
            *         jmp lbl1
            * lbl0 :
            *
            *          <right>:
            * lbl1 :
            */
            ir_label * lbl0 = freshLabel();
            ir_label * lbl1 = freshLabel();
            ir_node * ret = Nop();

            find_last(ret)->next = ir_tree_to_list(ir->tree_ir_1);
            find_last(ret)->next = Branch(lbl0);
            find_last(ret)->next = Iconst(1);
            find_last(ret)->next = Jump(lbl1);
            find_last(ret)->next = Label(lbl0);
            find_last(ret)->next = ir_tree_to_list(ir->tree_ir_2);
            find_last(ret)->next = Label(lbl1);

            return ret;
        }
        case ir_and: {
            /*
             * <left> : branchz lbl0
             * <right>: jump lbl1
             *
             * lbl0 :
             *          iconst(0)
             * lbl1 :
             */
            ir_label * lbl0 = freshLabel();
            ir_label * lbl1 = freshLabel();
            ir_node * ret = Nop();

            find_last(ret)->next = ir_tree_to_list(ir->tree_ir_1);
            find_last(ret)->next = Branch(lbl0);
            find_last(ret)->next = ir_tree_to_list(ir->tree_ir_2);
            find_last(ret)->next = Jump(lbl1);
            find_last(ret)->next = Label(lbl0);
            find_last(ret)->next = Iconst(0);
            find_last(ret)->next = Label(lbl1);

            return ret;
        }
        case ir_eq:
        case ir_lt:
        case ir_gt:
        case ir_ne:
        case ir_le:
        case ir_ge: {
            ir_node * left_expr = ir_tree_to_list(ir->tree_ir_1);
            ir_node * right_expr = ir_tree_to_list(ir->tree_ir_2);
            find_last(left_expr)->next = right_expr;
            find_last(left_expr)->next = ir;
            return left_expr;
        }
        case ir_not: {
            // TODO: Why this is not reversed ???
            ir_node * exp = ir_tree_to_list(ir->tree_ir_1);
            find_last(exp)->next = ir;
            return exp;
        }
        case ir_reserve: { return ir; assert(0); }
        case ir_read: { return ir;assert(0); }
        case ir_write: {
            // TODO: I hope order is correct
            ir_node * exp = ir_tree_to_list(ir->tree_ir_1);
            find_last(exp)->next = ir;
            return exp;
        }
        case ir_array_write: {
            ir_node * index_exp = ir_tree_to_list(ir->data.array_write.idx);
            ir_node * assign_exp = ir_tree_to_list(ir->data.array_write.assign);
            find_last(assign_exp)->next = index_exp;
            find_last(assign_exp)->next = ir;
            return assign_exp;
        }
        case ir_arglocal_read: { return ir; }
        case ir_arglocal_write: {
            ir_node * value = ir_tree_to_list(ir->tree_ir_1);
            find_last(value)->next = ir;
            return value;
        }
        case ir_lbl: {
            ir_node * l = ir_tree_to_list(ir->tree_ir_1);
            find_last(ir)->next = l;
            return ir;
        }
        case ir_jump: {

            return ir;
/*
            // TODO: I hope this is correct
            ir_node * cond = ir_tree_to_list(ir->tree_ir_1);
            ir_node * _then = ir_tree_to_list(ir->tree_ir_2);
            ir_node * _else = ir_tree_to_list(ir->tree_ir_3);
            find_last(cond)->next = _then;
            find_last(cond)->next = _else;
            return cond;
*/
        }
        case ir_branchzero: {
            ir_node * cond = ir_tree_to_list(ir->tree_ir_1);
            ir_node * _then = ir_tree_to_list(ir->tree_ir_2);
            ir_node * _else = ir_tree_to_list(ir->tree_ir_3);

            //ir_label *l3 = freshLabel();
            //ir_node * after_label = Label(l3);

            find_last(cond)->next = ir;
            find_last(cond)->next = _then;
            //find_last(cond)->next = Jump(l3);
            find_last(cond)->next = _else;
            //find_last(cond)->next = Jump(l3);
            //find_last(cond)->next = after_label;
            return cond;
        }
        case ir_function: {
            ir_node * var_decs = ir_tree_to_list(ir->tree_ir_1);
            ir_node * statments = ir_tree_to_list(ir->tree_ir_2);
            find_last(ir)->next = var_decs;
            find_last(ir)->next = statments;
            return ir;
        }
        case ir_call: {

            //assert(ir->data.call_function.vars == 0);

            //If agrs are """"NULL"""" we hve to push an int there
            //as calling convention of the blue jay
            ir_node * null_arg = Iconst(-473);
            // then all the args
            ir_node * args = ir_tree_to_list(ir->tree_ir_1);
            // TODO: How we know the return address?
            ir_node * ret = null_arg;
            find_last(ret)->next = args;
            find_last(ret)->next = ir;
            return ret;
        }
        case ir_ret: {
            // return from the void function
            ir_node * arg;
            arg = ir_tree_to_list(ir->tree_ir_1);
            find_last(arg)->next = ir;
            return arg;
        }
        case ir_intrinsic: {

                // ir_intrinsic
                //          (tree_ir_1) arg
                //
                //      ----> Tree <----
                //
                // [arg] -> ir_intrinsic
                //
                // arg to put on stack and how to take arg from stack

                ir_node * null_arg = Nop(); // Iconst(-473);

                if (ir->data.intrinsic == intrinsic_exit) {
                    ir_node * arg = ir_tree_to_list((ir->tree_ir_1));
                    find_last(arg)->next = ir;
                    null_arg->next = arg;
                    return arg;
                }
                if (ir->data.intrinsic == intrinsic_print_int) {
                    ir_node * arg = ir_tree_to_list((ir->tree_ir_1));
                    find_last(arg)->next = ir;
                    null_arg->next = arg;
                    return arg;
                }
                if (ir->data.intrinsic == intrinsic_print_string) {
                    ir_node * arg = ir_tree_to_list((ir->tree_ir_1));
                    find_last(arg)->next = ir;
                    null_arg->next = arg;
                    return arg;
                }
                assert (0);
        }

        case ir_seq: {
            ir_node *ir1 = ir_tree_to_list(ir->data.seq.o1);
            ir_node *ir2 = ir_tree_to_list(ir->data.seq.o2);

            // ir1 -> ir2 -> ir3
            // ir1  = [op1 -> op2 -> op3]
            // ir2 =  [op4 -> op5 -> op6]

            // ret = [op1 -> op2 -> op3 -> op4 -> op5 -> op6]

            // TODO: Improve for general cases

            find_last(ir1)->next = ir2;
            return ir1;
        }

        case ir_push: { assert(0); }
        case ir_pop: {
            return ir;
        }

        case ir_program: {
            ir_node *vars = ir_tree_to_list(ir->tree_ir_1);
            ir_node *funs = ir_tree_to_list(ir->tree_ir_2);
            ir_node *stms = ir_tree_to_list(ir->tree_ir_3);

            ir_node * ret = Nop();
            find_last(ret)->next = vars;
            find_last(ret)->next = funs;
            find_last(ret)->next = stms;

            return ret;

        }
        default: {
            assert(0); // Not supported
        }
    }
}
