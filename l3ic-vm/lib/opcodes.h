#ifndef _OPCODES_H
#define _OPCODES_H

typedef enum icvm_opcodes {
    vm_null,
    set_reg,
    swap_reg,
    add_label
} icvm_opcodes;

#endif