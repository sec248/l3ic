#include "vm.h"

ic_vm *vm_init(ic_parser *parser) {
    ic_vm *vm = calloc(1, sizeof(ic_vm));
    if (vm == NULL) {
        return NULL;
    }

    vm->parser = parser;
    return vm;
}

void vm_run(ic_vm *vm) {
    while (vm->idx < vm->parser->commands->length) {
        if (vm_handle(vm) == 0) {
            break;
        }

        vm->idx++;
    }
}

uint8_t vm_handle(ic_vm *vm) {
    ic_command *command = (ic_command *)vm->parser->commands->memory[vm->idx];

    switch (command->command) {
        case vm_set_reg: {
            uint8_t reg = command->args[0];

            if (reg > 6) {
                vm_error("SetReg", "unknown register id")
            }

            uint16_t value = (command->args[1] << 8) | (command->args[2] << 0);
            vm->registers[reg] = value;
            break;
        }
        case vm_swap_reg: {
            uint8_t reg1 = command->args[0];
            uint8_t reg2 = command->args[1];

            if (reg1 > 6 || reg2 > 6) {
                vm_error("SwapReg", "unknown register id")
            }

            uint16_t temp = vm->registers[reg1];
            vm->registers[reg1] = vm->registers[reg2];
            vm->registers[reg2] = temp;
            break;
        }
        case vm_jump_label: {
            uint16_t jump_id = (command->args[0] << 8) | (command->args[1] << 0);

            for (size_t jidx = 0; jidx < vm->parser->jump_table->length; jidx++) {
                ic_jump *jump = (ic_jump *)vm->parser->jump_table->memory[jidx];

                if (jump->jump_id == jump_id) {
                    if (vm->registers[6] != 0) {
                        vm->idx = jump->load_at;
                    }

                    return 1;
                }
            }

            vm_error("JumpLabel", "unknown label id")
            break;
        }
        case vm_dump_info: {
            printf("~[ L3IC DEBUG INFORMATIONS ]~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nRegA = %d\nRegB = %d\nRegC = %d\nRegX = %d\nRegY = %d\nRegZ = %d\nRegI = %d\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",
                vm->registers[0],
                vm->registers[1],
                vm->registers[2],
                vm->registers[3],
                vm->registers[4],
                vm->registers[5],
                vm->registers[6]
            );
            break;
        }
    }

    return 1;
}

void vm_free(ic_vm *vm) {
    parser_free(vm->parser);
    free(vm);
}