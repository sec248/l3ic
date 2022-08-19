#ifndef _ARRAY_H
#define _ARRAY_H

#include <stdint.h>
#include <stdlib.h>

#define LARR_PTRLEN sizeof(void *)

typedef struct {
    size_t length;
    size_t capacity;
    void** memory;
} larr;

larr *larr_init(void);
uint8_t larr_push(larr *arr, void *ptr);
void *larr_get(larr *arr, size_t index);
void larr_free(larr *arr);
void larr_free_in(larr *arr);

#endif