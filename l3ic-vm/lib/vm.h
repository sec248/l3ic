#ifndef _VM_H
#define _VM_H

#include "parser.c"
#include <stdio.h>

#define UNKNOWN_REG_ID "unknown register id"
#define UNKNOWN_LABEL_ID "unknown label id"

#define vm_error(command, message) \
    fprintf(stderr, "[%s:%I64u]: %s.", command, vm->idx, message); \
    return 0;

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