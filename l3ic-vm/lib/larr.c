#include "larr.h"

larr *larr_init(void) {
    larr *arr = malloc(sizeof(larr));
    if (arr == NULL)
        return arr;

    arr->capacity = LARR_PTRLEN * 256;
    arr->length = 0;
    arr->memory = malloc(arr->capacity);

    if (arr->memory == NULL) {
        free(arr);
        return NULL;
    }

    return arr;
}

uint8_t larr_push(larr *arr, void *ptr) {
    if ((arr->capacity - (arr->length * LARR_PTRLEN)) == LARR_PTRLEN) {
        arr->capacity *= 2;
        arr->memory = realloc(arr->memory, arr->capacity);

        if (arr->memory == NULL) {
            free(arr);
            return 0;
        }
    }

    arr->memory[arr->length++] = ptr;
    return 1;
}

void* larr_get(larr *arr, size_t index) {
    return arr->memory[index];
}

void larr_free(larr *arr) {
    free(arr->memory);
    free(arr);
}

void larr_free_in(larr *arr) {
    for (size_t idx = 0; idx < arr->length; idx++) {
        free(arr->memory[idx]);
    }
}