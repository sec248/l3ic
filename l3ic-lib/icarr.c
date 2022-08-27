#include "icarr.h"

ic_arr *icarr_init(void) {
    ic_arr *arr = malloc(sizeof(ic_arr));
    if (arr == NULL)
        return NULL;

    arr->capacity = sizeof(void *) * 256;
    arr->length = 0;
    arr->memory = malloc(arr->capacity);

    if (arr->memory == NULL) {
        free(arr);
        return NULL;
    }

    return arr;
}

uint8_t icarr_push(ic_arr *arr, void *ptr) {
    if ((arr->capacity - (arr->length * sizeof(void *))) <= sizeof(void *)) {
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

void* icarr_get(ic_arr *arr, size_t index) {
    return arr->memory[index];
}

void icarr_free(ic_arr *arr) {
    free(arr->memory);
    free(arr);
}

void icarr_free_in(ic_arr *arr) {
    for (size_t idx = 0; idx < arr->length; idx++) {
        free(arr->memory[idx]);
    }
}
