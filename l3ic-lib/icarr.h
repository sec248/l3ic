#ifndef _ICARR_H
#define _ICARR_H

#include <stdint.h>
#include <stdlib.h>

typedef struct ic_arr {
    size_t length;
    size_t capacity;
    void** memory;
} ic_arr;

ic_arr *icarr_init(void);
uint8_t icarr_push(ic_arr *arr, void *ptr);
void *icarr_get(ic_arr *arr, size_t index);
void icarr_free(ic_arr *arr);
void icarr_free_in(ic_arr *arr);

#endif