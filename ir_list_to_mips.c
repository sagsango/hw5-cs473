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
    //fprintf(stderr, "%s\n", label);
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
        case ir_nop: {
            break;
        }
        case ir_iconst: {
            //emitInstruction("li $v0, %d", "ICONST", ir->data.iconst);
            /* TODO: PUSH on register */
            emitInstruction("li $v0, %d", "ASSIGN the reg", ir->data.iconst);
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_sconst:         { assert(0); }
        case ir_add: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("add $v0, $v0, $v1", "v0 = v0 + v1");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_sub: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("sub $v0, $v0, $v1", "v0 = v0 - v1");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_mul: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("mul $v0, $v0, $v1", "v0 = v0 * v1");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_div: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("div $v0, $v1", "v0 % v1");
            emitInstruction("mflo $v0", "v0 = lo");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_mod: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("div $v0, $v1", "v0 % v1");
            emitInstruction("mfhi $v0", "v0 = lo");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_bor:            {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("or $v0, $v0, $v1", "v0 = v0 | v1");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_band: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("and $v0, $v0, $v1", "v0 = v0 & v1");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_xor: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("xor $v0, $v0, $v1", "v0 = v0 ^ v1");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_or:             { assert(0); }
        case ir_and:            { assert(0); }
        case ir_eq: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("seq $v0, $v0, $v1", "v0 = v0 == v1");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_lt: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("slt $v0, $v0, $v1", "v0 = v0 < v1");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_gt: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v1, ($sp)", "LOAD @sp");
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("sgt $v0, $v0, $v1", "v0 = v0 > v1");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
        }
        case ir_not: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("sltiu $v0, $v0, 1", "v0 = !v0");
            emitInstruction("sw $v0, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
            assert(0);
        }
        case ir_reserve: {
            /* Already reserved in the .data section */
            break;
        }
        case ir_read: {
            emitInstruction("la $v0, %s", "LOAD @", ir->data.read_write.name);
            emitInstruction("lw $v1, ($v0)", "LOAD @v0");
            emitInstruction("sw $v1, ($sp)", "STORE @sp");
            emitInstruction("sub $sp, $sp, 4", "DEC sp");
            break;
            assert(0);
        }
        case ir_write: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("la $v1, %s", "LOAD @", ir->data.read_write.name);
            emitInstruction("sw $v0, ($v1)", "STORE @v1");
            break;
            assert(0);
        }
        case ir_arglocal_read:  { assert(0); }
        case ir_arglocal_write: { assert(0); }
        case ir_lbl: {
            emitLabel(ir->data.lbl->name, "LABEL");
            break;
        }
        case ir_jump: {
            emitInstruction("j %s", "JUMP", ir->data.lbl->name);
            break;
        }
        case ir_branchzero: {
            emitInstruction("add $sp, $sp, 4", "INC sp");
            emitInstruction("lw $v0, ($sp)", "LOAD @sp");
            emitInstruction("beq $v0, $zero, %s", "BRANCH if 0", ir->data.lbl->name);
            break;
        }
        case ir_call:           { assert(0); }
        case ir_function:       { assert(0); }
        case ir_ret:            { assert(0); }
        case ir_intrinsic: {
            switch(ir->data.intrinsic) {
                case intrinsic_exit: {
                    //TODO: POP in a register, then systems call
                    /*
                     *  emitInstruction("move $a0, $v0", "EXIT syscall arg");
                     *  emitInstruction("li $v0, 17", "EXIT syscall number");
                     *  emitInstruction("syscall", "EXIT system call");
                    */
                    emitInstruction("add $sp, $sp, 4", "INC sp");
                    emitInstruction("lw $a0, ($sp)", "LOAD @sp");
                    emitInstruction("li $v0, 17", "EXIT syscall number");
                    emitInstruction("syscall", "EXIT system call");
                    break;
                }
                case intrinsic_print_int: {
                    //TODO: POP in a register, then systems call
                    /*emitInstruction("move $a0, $v0", "PRINTINT syscall arg");
                    emitInstruction("li $v0, 1", "PRINTINT syscall number");
                    emitInstruction("syscall", "PRINTINT system call");*/
                    emitInstruction("add $sp, $sp, 4", "INC sp");
                    emitInstruction("lw $a0, ($sp)", "LOAD @sp");
                    emitInstruction("li $v0, 1", "EXIT syscall number");
                    emitInstruction("syscall", "EXIT system call");
                    break;
                }
                default:
                    assert(0);
            }
            break;
        }
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
        switch (ir->kind) {
            case ir_reserve: {
                emitInstruction("%s: .space %d", "Allocate Space", ir->data.reserve.name, ir->data.reserve.size);
                break;
            }
            default: {
                /* Nothing to do */
                break;
            }
        }
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
