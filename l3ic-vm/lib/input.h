#ifndef _INPUT_H
#define _INPUT_H

typedef struct ic_cur_pos {
    uint16_t x;
    uint16_t y;
} ic_cur_pos;

typedef enum ic_mouse_c {
    icmc_scrollud,
    icmc_scrolluu,
    icmc_scrolldd,
    icmc_scrolldu,
    icmc_middled,
    icmc_middleu,
    icmc_leftd,
    icmc_leftu,
    icmc_rightd,
    icmc_rightu
} ic_mouse_c;

#if defined(__linux__)

#include <X11/extensions/XTest.h>
#include <stdint.h>

static Display *disp;
static Window rwin;

void input_init(void);
void mouse_move(uint16_t x, uint16_t y);
void mouse_event(ic_mouse_c in);
ic_cur_pos mouse_get_cursor(void);
void input_free(void);

#elif defined(_WIN32)

#include <windows.h>
#include <stdint.h>

void input_init(void);
void mouse_move(uint16_t x, uint16_t y);
void mouse_event(ic_mouse_c in);
ic_cur_pos mouse_get_cursor(void);
void input_free(void);

#endif
#endif