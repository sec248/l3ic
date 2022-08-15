#include "vm.c"
#define DEBUG_MODE 1

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    const char *file = argv[1];

    init_vm(file);
    run_vm();

    if (DEBUG_MODE)
        for (size_t index = 0; index < 256; index++)
            printf("[stack + %lu]: %d\n", index, machine->stack[index]);

    free_vm();

    return 0;
}