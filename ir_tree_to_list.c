#include "ir_tree_to_list.h"

#include <assert.h>
#include <stdlib.h>

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
        case ir_iconst: { assert(0); }
        case ir_sconst: { assert(0); }
        case ir_add: { assert(0); }
        case ir_sub: { assert(0); }
        case ir_mul: { assert(0); }
        case ir_div: { assert(0); }
        case ir_mod: { assert(0); }
        case ir_bor: { assert(0); }
        case ir_band: { assert(0); }
        case ir_xor: { assert(0); }
        case ir_or: { assert(0); }
        case ir_and: { assert(0); }
        case ir_eq: { assert(0); }
        case ir_lt: { assert(0); }
        case ir_gt: { assert(0); }
        case ir_not: { assert(0); }
        case ir_reserve: { assert(0); }
        case ir_read: { assert(0); }
        case ir_write: { assert(0); }
        case ir_arglocal_read: { assert(0); }
        case ir_arglocal_write: { assert(0); }
        case ir_lbl: { assert(0); }
        case ir_jump: { assert(0); }
        case ir_branchzero: { assert(0); }
        case ir_function: { assert(0); }
        case ir_call: { assert(0); }
        case ir_ret: { assert(0); }
        case ir_intrinsic: { assert(0); }

        case ir_seq: { assert(0); }

        case ir_push: { assert(0); }
        case ir_pop: { assert(0); }
        default: {
            assert(0); // Not supported
        }
    }
}
