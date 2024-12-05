#include "ir_pushpop.h"

#include <assert.h>
#include <stdlib.h>

__attribute__ ((unused))
static ir_node * PopReg(int i) {
    ir_node * ret = calloc(1, sizeof(ir_node));
    ret->kind = ir_pop;
    ret->data.iconst = i;
    return ret;
}

__attribute__ ((unused))
static ir_node * PushReg(int i) {
    ir_node * ret = calloc(1, sizeof(ir_node));
    ret->kind = ir_push;
    ret->data.iconst = i;
    return ret;
}

ir_node * addPushPop(ir_node * ir) {
    if (ir == NULL) {
        return NULL;
    }

    ir->next = addPushPop(ir->next);

    __attribute__ ((unused))
    ir_node * next = ir->next;

    switch (ir->kind) {
        case ir_nop: break;
        case ir_iconst: break;
        case ir_sconst: break;
        case ir_add: {
            /*
             *
             * POP 0
             * POP 1
             * ir
             * PUSH 0
             *
             */
            break;
        }
        case ir_sub: break;
        case ir_mul: break;
        case ir_div: break;
        case ir_mod: break;
        case ir_bor: break;
        case ir_band: break;
        case ir_xor: break;
        case ir_eq: break;
        case ir_lt: break;
        case ir_gt: break;
        case ir_or: break;
        case ir_and: break;
        case ir_not: break;
        case ir_reserve: break;
        case ir_read: break;
        case ir_arglocal_read: break;
        case ir_arglocal_write: break;
        case ir_write: break;
        case ir_lbl: break;
        case ir_function: break;
        case ir_jump: break;
        case ir_branchzero: break;
        case ir_call: break;
        case ir_ret: break;
        case ir_intrinsic: break;
        case ir_seq: break;
        case ir_pop: break;
        default: {
            assert(0); // Not supported
        }
    }

    return ir;
}

