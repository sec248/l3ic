#include "./lib/parser.c"
#include <stdio.h>

#define DEBUG_BC

#ifdef DEBUG_BC
static uint8_t debug_bc[] = { 
    // test set reg
    0x01, 0xff, 0xdd, 0xaa, 
    //useless
    0xdd,
    // set label
    0x03, 0xff, 0xff,
    // test move reg
    0x02, 0xaf, 0x53,
};
#endif

int main(void) {
    #ifdef DEBUG_BC
    ic_bytecode *bytecode = bytecode_from(debug_bc, 14);
    if (bytecode == NULL) {
        return 1;
    }
    #endif

    icvm_parser *parser = parser_init(bytecode);
    if (parser == NULL) {
        return 1;
    }

    parser_run(parser);

    bytecode_free(bytecode);

    for (size_t idx = 0; idx < parser->commands->length; idx++) {
        icvm_command *command = (icvm_command *)parser->commands->memory[idx];
        printf("command: %d | args: %d, %d, %d, %d\n", command->command, command->args[0], command->args[1], command->args[2], command->args[3]);
    }

    for (size_t idx = 0; idx < parser->jump_table->length; idx++) {
        icvm_jump *jump = (icvm_jump *)parser->jump_table->memory[idx];
        printf("jump at %I64d with id %d\n", jump->load_at, jump->jump_id);
    }

    icarr_free_in(parser->commands);
    icarr_free(parser->commands);

    icarr_free_in(parser->jump_table);
    icarr_free(parser->jump_table);

    return 0;
}