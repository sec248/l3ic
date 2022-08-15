#ifndef _CURSOR_H
#define _CURSOR_H

#include <windows.h>
#include <stdint.h>

uint16_t get_cursor_pos_x(void);
uint16_t get_cursor_pos_y(void);
void set_cursor_pos_x(uint16_t);
void set_cursor_pos_y(uint16_t);
void set_cursor_pos(uint16_t, uint16_t);

#endif