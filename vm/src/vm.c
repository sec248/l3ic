#include "./inc/vm.h"

static vm *machine;

_Bool init_vm(const char *file)
{
    machine = malloc(sizeof(vm));
    if (machine == NULL)
        return 0;

    machine->source = file;
    machine->current_command = 0;
    machine->argc = 0;

    machine->arguments[0] = 0;
    machine->arguments[1] = 0;
    machine->arguments[2] = 0;
    machine->arguments[3] = 0;

    machine->reg_a = 0;
    machine->reg_b = 0;
    machine->reg_c = 0;

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
    case SET_REG_A:
    case SET_REG_B:
    case SET_REG_C:
        machine->arguments[machine->argc++] = bytecode;

        if (machine->argc == 2)
        {
            uint16_t set_value = (machine->arguments[0] << 8) | machine->arguments[1];

            if (machine->current_command == SET_REG_A)
            {
                machine->reg_a = set_value;
            }
            else if (machine->current_command == SET_REG_B)
            {
                machine->reg_b = set_value;
            }
            else
            {
                machine->reg_c = set_value;
            }

            machine->argc = 0;
            machine->current_command = 0;
        }
        break;
    default:
        break;
    }

    return 2;
}