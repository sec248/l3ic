#ifndef _VM_H
#define _VM_H

#include "../reader.c"

#include <windows.h>

#define SET_REG_A 0xAA
#define SET_REG_B 0xBB
#define SET_REG_C 0xCC

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