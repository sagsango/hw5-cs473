#include <stdio.h>
#include "ast.h"
#include "frames.h"

void framesFunction(fundec_node * fundec, S_table globals, S_table functions_rets, S_table frames) {
    // Get frame created during symbol resolution
    __attribute__ ((unused))
        frame * f = S_look(frames, S_Symbol(fundec->name));

    // TODO add each argument position to indexes
    // TODO add each local variable position to indexes
    // TODO don't forget implicit variables!

}

void framesFunctions(list * l, S_table global_types, S_table function_decs, S_table frames) {
    if (l == NULL) return;
    fundec_node * fundec = (fundec_node*) l->head;
    framesFunction(fundec, global_types, function_decs, frames);
    framesFunctions(l->next, global_types, function_decs, frames);
}

void frames(program * p, S_table global_types, S_table function_decs, S_table frames) {
    framesFunctions(p->functions, global_types, function_decs, frames);
}
