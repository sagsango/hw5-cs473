#define _POSIX_C_SOURCE 200809L // enable strdup

#include "ir_list_to_mips.h"

#include <assert.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

static FILE * out;

  /*
   * L43:
   *
   */
__attribute__ ((unused))
static void emitLabel(char * label, char * comment, ...) {
    static char buffer[1024];
    va_list argp;

    assert(comment != NULL && strcmp("",comment));
    assert(label != NULL);

    va_start(argp, comment);
    vsnprintf(buffer, sizeof(buffer), label, argp);
    va_end(argp);
    fprintf(out, "%s:\n", buffer);
    fflush(out);
}

/*
 *  ("li $v0, %d", "", ir->iconst)
 */
__attribute__ ((unused))
static void emitInstruction(char * instruction, char * comment, ...) {
    static char buffer[1024];

    va_list argp;
    assert(comment != NULL && strcmp("",comment));
    assert(instruction != NULL);

    va_start(argp, comment);
    vsnprintf(buffer, sizeof(buffer), instruction, argp);
    va_end(argp);
    fprintf(out, "\t\t%s\t\t\t# %s\n", buffer, comment);
    fflush(out);
}

static void mips_ir_translate(ir_node * ir) {
    if (ir == NULL) {
        return;
    }

    switch (ir->kind) {
        case ir_nop:            { assert(0); }
        case ir_iconst:         { assert(0); }
        case ir_sconst:         { assert(0); }
        case ir_add:            { assert(0); }
        case ir_sub:            { assert(0); }
        case ir_mul:            { assert(0); }
        case ir_div:            { assert(0); }
        case ir_mod:            { assert(0); }
        case ir_bor:            { assert(0); }
        case ir_band:           { assert(0); }
        case ir_xor:            { assert(0); }
        case ir_or:             { assert(0); }
        case ir_and:            { assert(0); }
        case ir_eq:             { assert(0); }
        case ir_lt:             { assert(0); }
        case ir_gt:             { assert(0); }
        case ir_not:            { assert(0); }
        case ir_reserve:        { assert(0); }
        case ir_read:           { assert(0); }
        case ir_write:          { assert(0); }
        case ir_arglocal_read:  { assert(0); }
        case ir_arglocal_write: { assert(0); }
        case ir_lbl:            { assert(0); }
        case ir_jump:           { assert(0); }
        case ir_branchzero:     { assert(0); }
        case ir_call:           { assert(0); }
        case ir_function:       { assert(0); }
        case ir_ret:            { assert(0); }
        case ir_intrinsic:      { assert(0); }
        case ir_seq:            { assert(0); }
        case ir_push:           { assert(0); }
        case ir_pop:            { assert(0); }
        default: {
            assert(0); // Not supported
        }
    }

    mips_ir_translate(ir->next);
}

__attribute__ ((unused))
static void mips_ir_variables(ir_node * ir) {
    while (ir != NULL) {
        // TODO Generate MIPS code for variables and strings

        ir = ir->next;
    }
}

// generate MIPS from IR
void mips_ir(ir_node * ir, const char * o) {
    out = fopen(o, "w");

    fprintf(out, ".data\n");
    fflush(out);
    mips_ir_variables(ir);

    fprintf(out, ".text\n");
    fprintf(out, ".globl main\n");
    fprintf(out, "main:\n");
    fflush(out);
    mips_ir_translate(ir);

    fclose(out);
}
