#include "../l3ic-lib/include.h"
#include "reader.c"

int main(int argc, char **argv) {
    if (argc < 2) {
        perror("you must give a file to run.");
        return 1;
    }

    char *input_file = argv[1];
    read_result *file_content = read_source(input_file);
    if (file_content == NULL) {
        perror("can't read file content.");
        return 1;
    }

    ic_bytecode *bytecode = bytecode_from(file_content->memory, file_content->length);
    if (bytecode == NULL) {
        return 1;
    }

    free(file_content->memory);
    free(file_content);

    ic_parser *parser = parser_init(bytecode);
    if (parser == NULL) {
        bytecode_free(bytecode);
        return 1;
    }

    parser_run(parser);

    ic_vm *vm = vm_init(parser);
    if (vm == NULL) {
        parser_free(parser);
        return 1;
    }

    input_init();

    vm_run(vm);
    vm_free(vm);

    input_free();
    
    return 0;
}
