#include "reader.c"

int reader(char current) {
    printf("%x\n", current);
    return 1;
}

int main(void) {
    puts("Reading file");
    read_bytecode(".\\src\\test\\test.l3ic", reader);
    puts("Finished");
}