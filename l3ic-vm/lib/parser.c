#include "parser.h"
#include <stdio.h>

icvm_parser *parser_init(ic_bytecode *source) {
    icvm_parser *parser = calloc(1, sizeof(icvm_parser));
    parser->current_command = vm_null;
    parser->source = source;

    parser->commands = icarr_init();
    if (parser->commands == NULL) {
        free(parser);
        return NULL;
    }

    parser->jump_table = icarr_init();
    if (parser->commands == NULL) {
        free(parser->commands);
        free(parser);
        return NULL;
    }

    return parser;
}

void parser_run(icvm_parser *parser) {
    for (size_t idx = 0; idx < parser->source->length; idx++) {
        parser_collect(parser, parser->source->memory[idx]);
    }
}

void parser_collect(icvm_parser *parser, uint8_t in) {
    if (parser->current_command == 0) {
        parser->current_command = in;

        switch (in) {
            case set_reg:
                parser->argc_to_collect = 3;
                break;
            case swap_reg:
                parser->argc_to_collect = 2;
                break;
            case add_label:
                parser->argc_to_collect = 2;
                break;
            default:
                reset_command(parser)
                break;
        }
    } else {
        parser_collect_args(parser, in);
    }
}

void parser_collect_args(icvm_parser *parser, uint8_t in) {
    parser->current_args[parser->arg_index++] = in;

    if (parser->argc_to_collect == parser->arg_index) {
        if (parser->current_command == add_label) {
            icvm_jump *jump = calloc(1, sizeof(icvm_jump));

            jump->jump_id = (parser->current_args[0] << 8) | (parser->current_args[1] << 0);
            if (parser->commands->length == 0) {
                jump->load_at = 0;
            } else {
                jump->load_at = parser->commands->length - 1;
            }

            icarr_push(parser->jump_table, jump);

            reset_command(parser)
        } else {
            icvm_command *command = calloc(1, sizeof(icvm_command));

            command->args[0] = parser->current_args[0];
            command->args[1] = parser->current_args[1];
            command->args[2] = parser->current_args[2];
            command->args[3] = parser->current_args[3];

            command->command = parser->current_command;

            icarr_push(parser->commands, command);

            reset_command(parser)
        }
    }
}