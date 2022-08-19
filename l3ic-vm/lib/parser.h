#ifndef _PARSER_H
#define _PARSER_H

#include "icarr.c"
#include "bytecode.c"
#include "opcodes.h"

#include <stdint.h>

#define reset_command(p) \
    parser->arg_index = 0; \
    parser->argc_to_collect = 0; \
    parser->current_command = vm_null;

typedef struct icvm_command {
    uint8_t args[4];
    uint8_t command;
} icvm_command;

typedef struct icvm_jump {
    size_t load_at;
    uint16_t jump_id;
} icvm_jump;

typedef struct icvm_parser {
    uint8_t current_args[4];
    ic_arr *commands;
    ic_arr *jump_table;
    ic_bytecode *source;
    uint8_t current_command;
    uint8_t argc_to_collect;
    uint8_t arg_index;
} icvm_parser;

icvm_parser *parser_init(ic_bytecode *source);
void parser_run(icvm_parser *parser);
void parser_collect(icvm_parser *parser, uint8_t in);
void parser_collect_args(icvm_parser *parser, uint8_t in);

#endif