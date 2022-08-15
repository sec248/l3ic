#include "./inc/vm.h"

static vm *machine;

_Bool init_vm(const char *file)
{
    machine = calloc(1, sizeof(vm));
    if (machine == NULL)
        return 0;

    machine->source = file;
    return 1;
}

void run_vm(void)
{
    if (machine != NULL)
        read_bytecode(machine->source, handle_command);
}

void free_vm(void)
{
    free(machine);
}

int handle_command(uint8_t bytecode)
{
    if (machine->current_command == 0)
    {
        machine->current_command = bytecode;
        return 1;
    }

    switch (machine->current_command)
    {
    case SET_REG:
        machine->arguments[machine->argc++] = bytecode;

        if (machine->argc == 3)
        {
            uint8_t got_register = machine->arguments[0];
            uint16_t set_value = (machine->arguments[1] << 8) | machine->arguments[2];

            switch (got_register)
            {
            case REG_A:
                machine->reg_a = set_value;
                break;
            case REG_B:
                machine->reg_b = set_value;
                break;
            case REG_C:
                machine->reg_c = set_value;
                break;
            default:
                vm_error("SetReg", "unknown register") break;
            }

            machine->argc = 0;
            machine->current_command = 0;
        }
        break;
    case PUSH_STACK:
        machine->arguments[machine->argc++] = bytecode;

        if (machine->argc == 2)
        {
            uint16_t push_value = (machine->arguments[0] << 8) | machine->arguments[1];
            if (machine->stack_idx == 128)
            {
                vm_error("PushStack", "stack overflow")
            }

            machine->stack[machine->stack_idx++] = push_value;
            machine->argc = 0;
            machine->current_command = 0;
        }
        break;
    default:
        break;
    }

    return 2;
}