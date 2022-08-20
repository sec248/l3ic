#include "./lib/vm.c"
#include <stdio.h>

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
}; */ {
    vm_set_reg, 0x02, 0x00, 0xFF,
    vm_dump_info,
    vm_mod_reg, 0x02, 0x00, 0x02,
    vm_dump_info,
};

int main(void) {
    ic_bytecode *bytecode = bytecode_from(debug_bc, 10);
    if (bytecode == NULL) {
        return 1;
    }

    ic_parser *parser = parser_init(bytecode);
    if (parser == NULL) {
        return 1;
    }
    parser_run(parser);

    for (size_t idx = 0; idx < parser->commands->length; idx++) {
        ic_command *command = (ic_command *)parser->commands->memory[idx];
        printf("command: %d, args: %d %d %d %d\n", command->command, command->args[0], command->args[1], command->args[2], command->args[3]);
    }

    ic_vm *vm = vm_init(parser);
    if (vm == NULL) {
        return 1;
    }
    vm_run(vm);

    return 0;
}