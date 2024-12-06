#include <stdio.h>
#include "ast.h"
#include "frames.h"
#include <stdlib.h>
#include <assert.h>


void framesFunction(fundec_node * fundec, list *gvars, S_table globals, S_table functions_rets, S_table frames) {
    // Get frame created during symbol resolution

    frame * f = S_look(frames, S_Symbol(fundec->name));
    assert (f);
    f->n_imp = f->n_index;
    while (gvars) {
        vardec_node * vardec = (vardec_node*) gvars->head;
        if (vardec->implicit && (!vardec->manually || ((vardec_node*)S_look(globals, S_Symbol(vardec->name)))->manually == 1) && S_look(f->args_locs_types, S_Symbol(vardec->name)) == NULL) {
            f->n_imp += 1;
            S_enter(f->args_locs_types, S_Symbol(vardec->name), vardec);
            // TODO: check this name is not present
            S_enter(f->indexes, S_Symbol(vardec->name), (void*)f->n_imp);
        }
        gvars = gvars->next;
    }

    // TODO add each argument position to indexes
    // TODO add each local variable position to indexes
    // TODO don't forget implicit variables!

}

void framesFunctions(list * l, list *gvars, S_table global_types, S_table function_decs, S_table frames) {
    if (l == NULL) return;
    fundec_node * fundec = (fundec_node*) l->head;
    framesFunction(fundec, gvars, global_types, function_decs, frames);
    framesFunctions(l->next, gvars, global_types, function_decs, frames);
}

void frames(program * p, S_table global_types, S_table function_decs, S_table frames) {
    framesFunctions(p->functions, p->variables, global_types, function_decs, frames);
}