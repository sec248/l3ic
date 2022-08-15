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