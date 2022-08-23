#include "./lib/vm.c"
#include <stdio.h>
#include <X11/keysym.h>

static uint8_t debug_bc[] = /* { 
    // set reg i to 1 so can jump
    0x01, 0x06, 0x00, 0x01,
    // test set reg
    0x01, 0x01, 0x00, 0xaa,
    // test set reg
    0x01, 0x05, 0xff, 0xff,
    // set label
    0x03, 0x00, 0x00,
    // swap
    0x02, 0x01, 0x05,
    // debug
    0xff,
    // jump label
    0x04, 0x00, 0x00,
}; */ /* {
    vm_mouse_pos,
    vm_dump_info,
    vm_set_reg, REG_X, 0x00, XK_A,
    vm_key_press,
    vm_key_release,
}; */
{
    vm_set_reg, REG_X, 0x00, 0xFF,
    vm_dump_info,
    vm_copy_reg, REG_Y, REG_X,
    vm_dump_info
};

int main(void) {
    input_init();

    ic_bytecode *bytecode = bytecode_from(debug_bc, 9);
    if (bytecode == NULL) {
        return 1;
    }

    ic_parser *parser = parser_init(bytecode);
    if (parser == NULL) {
        bytecode_free(bytecode);
        return 1;
    }

    parser_run(parser);

    ic_vm *vm = vm_init(parser);
    if (vm == NULL) {
        parser_free(parser);
        return 1;
    }

    vm_run(vm);
    vm_free(vm);

    input_free();
    
    return 0;
}