#ifndef _INPUT_H
#define _INPUT_H

#include <X11/extensions/XTest.h>
#include <X11/Xutil.h>
#include <stdint.h>

typedef struct ic_cur_pos {
    uint16_t x;
    uint16_t y;
} ic_cur_pos;

typedef struct ic_pixel {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} ic_pixel;

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

static Display *disp;
static Window rwin;

void input_init(void);
void mouse_move(uint16_t x, uint16_t y);
void mouse_event(ic_mouse_c in);
void keyboard_event(unsigned in, _Bool press);
ic_cur_pos mouse_get_cursor(void);
ic_pixel get_screen_pixel(uint16_t x, uint16_t y);
void input_free(void);

#endif
