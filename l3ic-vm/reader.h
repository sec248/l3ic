#ifndef _VM_READER
#define _VM_READER

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct read_result {
    size_t length;
    uint8_t *memory;
} read_result;

read_result *read_source(char *path);

#endif
