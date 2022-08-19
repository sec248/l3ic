#ifndef _BYTECODE_H
#define _BYTECODE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct ic_bytecode {
    size_t length;
    size_t capacity;
    uint8_t *memory;
} ic_bytecode;

ic_bytecode *bytecode_init(void);
uint8_t bytecode_push(ic_bytecode *arr, uint8_t in);
uint8_t bytecode_get(ic_bytecode *arr, size_t index);
void bytecode_free(ic_bytecode *arr);

#endif