#include "vm.h"
#include "input.c"

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

            if (reg > REG_COUNT - 1) {
                vm_error("SetReg", UNKNOWN_REG_ID)
            }

            uint16_t value = (command->args[1] << 8) | (command->args[2] << 0);
            vm->registers[reg] = value;
            break;
        }
        case vm_swap_reg: {
            uint8_t reg1 = command->args[0];
            uint8_t reg2 = command->args[1];

            if (reg1 > REG_COUNT - 1 || reg2 > REG_COUNT - 1) {
                vm_error("SwapReg", UNKNOWN_REG_ID)
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
                    if (vm->registers[REG_I] != 0) {
                        vm->idx = jump->load_at;
                    }

                    return 1;
                }
            }

            vm_error("JumpLabel", UNKNOWN_LABEL_ID)
            break;
        }
        case vm_add_reg: {
            __vm_math_h("AddReg", +)
        }
        case vm_sub_reg: {
            __vm_math_h("SubReg", -)
        }
        case vm_mul_reg: {
            __vm_math_h("MulReg", *)
        }
        case vm_div_reg: {
            __vm_math_h("DivReg", /)
        }
        case vm_mod_reg: {
            __vm_math_h("ModReg", %)
        }
        case vm_mouse_move: {
            uint16_t mouse_x = vm->registers[REG_X];
            uint16_t mouse_y = vm->registers[REG_Y];

            mouse_move(mouse_x, mouse_y);
            break;
        }
        case vm_mouse_scrolld_up:
        case vm_mouse_scrolld_down:
        case vm_mouse_scrollu_up:
        case vm_mouse_scrollu_down:
        case vm_mouse_middle_up:
        case vm_mouse_middle_down:
        case vm_mouse_right_up:
        case vm_mouse_right_down:
        case vm_mouse_left_up:
        case vm_mouse_left_down: {
            mouse_event(20 - command->command);
            break;
        }
        case vm_mouse_pos: {
            ic_cur_pos pos = mouse_get_cursor();

            vm->registers[REG_X] = pos.x;
            vm->registers[REG_Y] = pos.y;
            break;
        }
        case vm_key_press: {
            keyboard_event(vm->registers[REG_X], 1);
            break;
        }
        case vm_key_release: {
            keyboard_event(vm->registers[REG_X], 0);
            break;
        }
        case vm_dump_info: {
            printf("~[ L3IC DEBUG INFORMATIONS ]~\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nRegA = %d\nRegB = %d\nRegC = %d\nRegX = %d\nRegY = %d\nRegZ = %d\nRegI = %d\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",
                vm->registers[REG_A],
                vm->registers[REG_B],
                vm->registers[REG_C],
                vm->registers[REG_X],
                vm->registers[REG_Y],
                vm->registers[REG_Z],
                vm->registers[REG_I]
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