#include "./lib/parser.c"
#include <stdio.h>

int main(void) {
    ic_bytecode *bytecode = bytecode_init();
    if (bytecode == NULL) {
        return 1;
    }

    bytecode_push(bytecode, 0x01);
    bytecode_push(bytecode, 0xFF);
    bytecode_push(bytecode, 0xDD);
    bytecode_push(bytecode, 0xAA);
    bytecode_push(bytecode, 0x02);
    bytecode_push(bytecode, 0xAA);
    bytecode_push(bytecode, 0xFF);

    icvm_parser *parser = parser_init(bytecode);
    if (parser == NULL) {
        return 1;
    }

    parser_run(parser);

    bytecode_free(bytecode);

    for (size_t idx = 0; idx < parser->commands->length; idx++) {
        icvm_command *command = (icvm_command *)parser->commands->memory[idx];
        printf("command: %d | args, %d, %d, %d, %d\n", command->command, command->args[0], command->args[1], command->args[2], command->args[3]);
    }

    icarr_free_in(parser->commands);
    icarr_free(parser->commands);

    icarr_free_in(parser->jump_table);
    icarr_free(parser->jump_table);

    return 0;
}