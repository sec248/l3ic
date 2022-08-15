#ifndef _VM_H
#define _VM_H

#include "../reader.c"

#include <windows.h>

#define REG_A 0x01
#define REG_B 0x02
#define REG_C 0x03

#define SET_REG 0x10

#define vm_error(command, message)     \
    fprintf(stderr, "[l3ic-vm : %s]: %s.\n", command, message); \
    return -1;

typedef struct
{
    const char *source;
    uint8_t current_command;
    uint8_t argc;
    uint8_t arguments[4];
    uint16_t reg_a;
    uint16_t reg_b;
    uint16_t reg_c;
} vm;

_Bool init_vm(const char *);
void run_vm(void);
void free_vm(void);

int handle_command(uint8_t);

#endif