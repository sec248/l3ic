#include "vm.c"

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;

    const char *file = argv[1];

    init_vm(file);
    run_vm();

    printf("reg a: %d\n", machine->reg_a);
    printf("reg b: %d\n", machine->reg_b);
    printf("reg c: %d\n", machine->reg_c);
    
    free_vm();

    return 0;
}