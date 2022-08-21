#ifndef _OPCODES_H
#define _OPCODES_H

typedef enum ic_opcodes {
    vm_null,
    vm_set_reg,
    vm_swap_reg,
    vm_add_reg,
    vm_sub_reg,
    vm_mul_reg,
    vm_div_reg,
    vm_mod_reg,
    vm_set_label,
    vm_jump_label,
    vm_mouse_move,
    // opcodes below are constant, which means you shouldn't change that.
    vm_mouse_right_up,
    vm_mouse_right_down,
    vm_mouse_left_up,
    vm_mouse_left_down,
    // opcodes above are constant, which means you shouldn't change that.
    vm_dump_info = 255
} ic_opcodes;

#endif