#ifndef _VM_H
#define _VM_H

#include "parser.c"
#include <stdio.h>

#define REG_A 0
#define REG_B 1
#define REG_C 2
#define REG_X 3
#define REG_Y 4
#define REG_Z 5
#define REG_I 6
#define REG_COUNT 7

#define UNKNOWN_REG_ID "unknown register id"
#define UNKNOWN_LABEL_ID "unknown label id"

#define vm_error(command, message) \
    fprintf(stderr, "[%s:%I64lu]: %s.", command, vm->idx, message); \
    return 0;

#define __vm_math_h(name, op) \
    uint8_t reg = command->args[0]; \
    if (reg > REG_COUNT - 1) { vm_error(name, UNKNOWN_REG_ID) } \
    uint16_t value = (command->args[1] << 8) | (command->args[2] << 0); \
    vm->registers[reg] op##= value; \
    break; \

typedef struct ic_vm {
    uint16_t registers[7];
    ic_parser *parser;
    size_t idx;
} ic_vm;

ic_vm *vm_init(ic_parser *parser);
void vm_run(ic_vm *vm);
uint8_t vm_handle(ic_vm *vm);
void vm_free(ic_vm *vm);

#endif