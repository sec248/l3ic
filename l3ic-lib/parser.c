#include "parser.h"

ic_parser *parser_init(ic_bytecode *source) {
    ic_parser *parser = calloc(1, sizeof(ic_parser));
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

void parser_run(ic_parser *parser) {
    for (size_t idx = 0; idx < parser->source->length; idx++) {
        parser_collect(parser, parser->source->memory[idx]);
    }
}

void parser_collect(ic_parser *parser, uint8_t in) {
    if (parser->current_command == vm_null) {
        parser->current_command = in;

        switch (in) {
            case vm_set_reg: // irc
            case vm_add_reg: // irc
            case vm_sub_reg: // irc
            case vm_mul_reg: // irc
            case vm_div_reg: // irc
            case vm_mod_reg: // irc
                parser->argc_to_collect = 3;
                break;
            case vm_stack_push: // irc
            case vm_copy_reg: // irc
            case vm_swap_reg: // irc
            case vm_set_label: // irc
            case vm_jump_label: // irc
            case vm_compare_bigger: // irc
            case vm_compare_smaller: // irc
            case vm_compare_equal: // irc
                parser->argc_to_collect = 2;
                break;
            case vm_stack_pop: // irc
            case vm_stack_push_reg: // irc
                parser->argc_to_collect = 1;
                break;
            case vm_key_press: // irc
            case vm_key_release: // irc
            case vm_mouse_pos: // irc
            case vm_mouse_scrolld_up: // irc
            case vm_mouse_scrolld_down: // irc
            case vm_mouse_scrollu_up: // irc
            case vm_mouse_scrollu_down: // irc
            case vm_mouse_middle_up: // irc
            case vm_mouse_middle_down: // irc
            case vm_mouse_right_up: // irc
            case vm_mouse_right_down: // irc
            case vm_mouse_left_up: // irc
            case vm_mouse_left_down: // irc
			case vm_get_pixel_rgb: // irc
			case vm_mouse_move: // irc
            case vm_dump_info: // irc
            case vm_sleep: // irc
            case vm_reverse_cond: // irc
                push_command
                reset_command
                break;
            default:
                reset_command
                break;
        }
    } else {
        parser_collect_args(parser, in);
    }
}

void parser_collect_args(ic_parser *parser, uint8_t in) {
    parser->current_args[parser->arg_index++] = in;

    if (parser->argc_to_collect == parser->arg_index) {
        if (parser->current_command == vm_set_label) {
            ic_jump *jump = calloc(1, sizeof(ic_jump));

            jump->jump_id = (parser->current_args[0] << 8) | (parser->current_args[1] << 0);
            if (parser->commands->length == 0) {
                jump->load_at = 0;
            } else {
                jump->load_at = parser->commands->length - 1;
            }

            icarr_push(parser->jump_table, jump);
            reset_command
        } else {
            ic_command *command = calloc(1, sizeof(ic_command));

            command->args[0] = parser->current_args[0];
            command->args[1] = parser->current_args[1];
            command->args[2] = parser->current_args[2];
            command->args[3] = parser->current_args[3];

            command->command = parser->current_command;

            icarr_push(parser->commands, command);
            reset_command
        }
    }
}

void parser_free(ic_parser *parser) {
    icarr_free_in(parser->commands);
    icarr_free_in(parser->jump_table);

    bytecode_free(parser->source);
    icarr_free(parser->commands);
    icarr_free(parser->jump_table);
    free(parser);
}
