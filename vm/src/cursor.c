#include "./inc/cursor.h"

uint16_t get_cursor_pos_x(void)
{
    POINT out;
    GetCursorPos(&out);

    return out.x;
}

uint16_t get_cursor_pos_y(void)
{
    POINT out;
    GetCursorPos(&out);

    return out.y;
}

void set_cursor_pos_x(uint16_t xPos)
{
    SetCursorPos(xPos, get_cursor_pos_y());
}

void set_cursor_pos_y(uint16_t yPos)
{
    SetCursorPos(get_cursor_pos_x(), yPos);
}

void set_cursor_pos(uint16_t xPos, uint16_t yPos)
{
    SetCursorPos(xPos, yPos);
}
