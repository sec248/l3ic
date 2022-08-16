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
        case CURSOR_GET_POS_X:
            push_stack(get_cursor_pos_x());
            reset_command_vm();
            break;
        case CURSOR_GET_POS_Y:
            push_stack(get_cursor_pos_y());
            reset_command_vm();
            break;
        case CURSOR_SET_POS_X:
            set_cursor_pos_x(pop_stack());
            reset_command_vm();
            break;
        case CURSOR_SET_POS_Y:
            set_cursor_pos_y(pop_stack());
            reset_command_vm();
            break;
        case CURSOR_SET_POS:
        {
            uint16_t posX = pop_stack();
            uint16_t posY = pop_stack();

            set_cursor_pos(posX, posY);
            reset_command_vm();
            break;
        }
        case MOUSE_LEFT_PRESS:
            __mouse_input(MOUSEEVENTF_LEFTDOWN)
                reset_command_vm();
            break;
        case MOUSE_LEFT_RELEASE:
            __mouse_input(MOUSEEVENTF_LEFTUP)
                reset_command_vm();
            break;
        case MOUSE_RIGHT_PRESS:
            __mouse_input(MOUSEEVENTF_RIGHTDOWN)
                reset_command_vm();
            break;
        case MOUSE_RIGHT_RELEASE:
            __mouse_input(MOUSEEVENTF_RIGHTUP)
                reset_command_vm();
            break;
        case KEY_PRESS:
            __keyboard_input(pop_stack(), NULL)
                reset_command_vm();
            break;
        case KEY_RELEASE:
            __keyboard_input(pop_stack(), 1)
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