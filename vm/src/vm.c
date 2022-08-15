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

uint16_t pop_stack(void)
{
    uint16_t number = machine->stack[--machine->stack_idx];
    machine->stack[machine->stack_idx] = 0;

    return number;
}

void push_stack(uint16_t number)
{
    machine->stack[machine->stack_idx++] = number;
}

void reset_command_vm(void)
{
    machine->argc = 0;
    machine->current_command = 0;
}

int handle_command(uint8_t bytecode)
{
    switch (machine->current_command)
    {
    case NO_COMMAND:
        // all commands in this scope must be no argument commands
        switch (bytecode)
        {
        case POP_STACK:
            pop_stack();
            reset_command_vm();
            break;
        default:
            machine->current_command = bytecode;
            break;
        }
        break;
    // all commands below this must be argument required commands
    case PUSH_STACK:
        machine->arguments[machine->argc++] = bytecode;

        if (machine->argc == 2)
        {
            uint16_t push_value = (machine->arguments[0] << 8) | machine->arguments[1];

            push_stack(push_value);
            reset_command_vm();
        }
        break;
    default:
        break;
    }

    return 1;
}