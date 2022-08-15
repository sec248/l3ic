#ifndef _VM_H
#define _VM_H

#include "../reader.c"

#include <windows.h>

#define NO_COMMAND 0x00
#define PUSH_STACK 0xA0
#define POP_STACK 0xA1

#define vm_error(command, message)                              \
    fprintf(stderr, "[l3ic-vm : %s]: %s.\n", command, message); \
    return -1;

typedef struct
{
    const char *source;
    uint8_t current_command;
    uint8_t argc;
    uint8_t stack_idx;
    uint8_t arguments[4];
    uint16_t stack[255];
} vm;

_Bool init_vm(const char *);
void run_vm(void);
void free_vm(void);
void reset_command_vm(void);

uint16_t pop_stack(void);
void push_stack(uint16_t);

int handle_command(uint8_t);

#endif