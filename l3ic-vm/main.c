#include "./lib/larr.c"
#include <stdio.h>

int main(void) {
    int a = 1337;
    char c = 'A';

    larr* arr = larr_init();
    larr_push(arr, &a);
    larr_push(arr, &c);

    printf("first: %d second: %c\n", *(int*)larr_get(arr, 0), *(char*)larr_get(arr, 1));

    larr_free(arr);
}