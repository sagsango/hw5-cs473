#include <stdlib.h>
#include <assert.h>
#include "semantic_analysis_types.h"

ty_node * typeCheckExpr(exp_node * e, S_table global_types, S_table function_decs, frame * f) {

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

void typeCheckStmts(list * l, S_table locals, S_table function_decs, frame * f);

void typeCheckStmt(stmt_node * s, S_table global_types, S_table function_decs, frame * f) {
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

void typeCheckStmts(list * l, S_table globals_types, S_table function_decs, frame * f) {
    if (l == NULL) return;
    typeCheckStmt(l->head, globals_types, function_decs, f);
    typeCheckStmts(l->next, globals_types, function_decs, f);
}

void typeCheckVariable(vardec_node * vardec, S_table globals_types, S_table function_decs, frame * f) {
    // TODO ensure that variable initialization expression has the same type as the variable definition

    assert(0); // Not implemented
}

void typeCheckVariables(list * l, S_table global_types, S_table function_decs, frame * f) {
    if (l == NULL) return;
    typeCheckVariable((vardec_node *)l->head, global_types, function_decs, f);
    typeCheckVariables(l->next, global_types, function_decs, f);
}

void typeCheckFunction(fundec_node * fundec, S_table globals_types, S_table functions_rets, frame * f) {
    // TODO ensure that the body of the function is well typed
    // TODO ensure local variables are initialized with the correct type

    assert(0); // Not implemented
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
