#include <stdlib.h>
#include <assert.h>
#include "semantic_analysis_symbols.h"

void symbolResolutionExpr(exp_node * e, S_table global_types, S_table function_decs, frame * f) {

    if(!e) return;
    switch(e->kind){
        case int_exp: {
            assert(0); // Not implemented
        }
        case binop_exp: {
            assert(0); // Not implemented
        }
        case unop_exp: {
            assert(0); // Not implemented
        }
        // TODO add more cases for all expressions
        default:
            assert(0); // Should be dead code
    }
}

void symbolResolutionStmts(list * l, S_table locals, S_table function_decs, frame * f);

void symbolResolutionStmt(stmt_node * s, S_table global_types, S_table function_decs, frame * f) {
    if(!s) return;
    switch(s->kind){
        case if_stmt: {
            assert(0); // Not implemented
        }
        case ret_stmt: {
            assert(0); // Not implemented
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
    int global = 1;

    if (global) {
        // TODO register global variable types in globals_types
    } else {
        // TODO register local variable types in the frame
    }

    // TODO check that all symbols in the variable initialization are known to fail negative tests

    assert(0); // Not implemented
}

void symbolResolutionVariables(list * l, S_table global_types, S_table function_decs, frame * f) {
    if (l == NULL) return;
    symbolResolutionVariable((vardec_node *)l->head, global_types, function_decs, f);
    symbolResolutionVariables(l->next, global_types, function_decs, f);
}

void symbolResolutionFunction(fundec_node * fundec, S_table globals, S_table functions_rets, frame * f) {
    // TODO add each argument type to the f->args_locs_types

    // TODO add each local variable type to f->args_locs_types

    // TODO check that the statements in the body of the function only use known variables and functions

    assert(0); // Not implemented
}

void symbolResolutionFunctions(list * l, S_table global_types, S_table function_decs, S_table frames) {
    if (l == NULL) return;
    fundec_node * fundec = (fundec_node*) l->head;

    // Create a new frame
    frame * f = malloc(sizeof(frame));

    // Initialize all memory so we can read it later
    f->args_locs_types = S_empty();
    f->indexes = S_empty();
    f->ret = NULL;

    // Add newly computed frame to frames
    S_enter(frames, S_Symbol(fundec->name), f);

    symbolResolutionFunction(fundec, global_types, function_decs, f);
    symbolResolutionFunctions(l->next, global_types, function_decs, frames);
}

void symbolResolution(program * p, S_table global_types, S_table function_decs, S_table frames) {
    symbolResolutionVariables(p->variables, global_types, function_decs, NULL);
    symbolResolutionFunctions(p->functions, global_types, function_decs, frames);
    symbolResolutionStmts(p->statements, global_types, function_decs, NULL);
}
