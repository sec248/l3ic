#include "bytecode.h"

ic_bytecode *bytecode_init(void) {
    ic_bytecode *arr = malloc(sizeof(ic_bytecode));
    if (arr == NULL)
        return arr;

    arr->capacity = 1024;
    arr->length = 0;
    arr->memory = malloc(arr->capacity);

    if (arr->memory == NULL) {
        free(arr);
        return NULL;
    }

    return arr;
}

uint8_t bytecode_push(ic_bytecode *arr, uint8_t in) {
    if ((arr->capacity - arr->length) <= 1) {
        arr->capacity *= 2;
        arr->memory = realloc(arr->memory, arr->capacity);

        if (arr->memory == NULL) {
            free(arr);
            return 0;
        }
    }

    arr->memory[arr->length++] = in;
    return 1;
}

uint8_t bytecode_get(ic_bytecode *arr, size_t index) {
    return arr->memory[index];
}

void bytecode_free(ic_bytecode *arr) {
    free(arr->memory);
    free(arr);
}