#ifndef _PARSER_H
#define _PARSER_H

#include "icarr.c"
#include "bytecode.c"
#include "opcodes.h"

#define reset_command { \
    parser->arg_index = 0; \
    parser->argc_to_collect = 0; \
    parser->current_command = vm_null; }

#define push_command { \
    ic_command *command = calloc(1, sizeof(ic_command)); \
    command->command = in; \
    icarr_push(parser->commands, command); }

typedef struct ic_command {
    uint8_t args[4];
    uint8_t command;
} ic_command;

typedef struct ic_jump {
    size_t load_at;
    uint16_t jump_id;
} ic_jump;

typedef struct ic_parser {
    uint8_t current_args[4];
    ic_arr *commands;
    ic_arr *jump_table;
    ic_bytecode *source;
    uint8_t current_command;
    uint8_t argc_to_collect;
    uint8_t arg_index;
} ic_parser;

ic_parser *parser_init(ic_bytecode *source);
void parser_run(ic_parser *parser);
void parser_collect(ic_parser *parser, uint8_t in);
void parser_collect_args(ic_parser *parser, uint8_t in);
void parser_free(ic_parser *parser);

#endif