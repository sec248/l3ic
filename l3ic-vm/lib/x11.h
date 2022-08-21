#ifndef _X11_H
#define _X11_H

#include <X11/extensions/XTest.h>
#include <stdint.h>

static Display *disp;

typedef enum ic_mouse_c {
    icmc_leftd,
    icmc_leftu,
    icmc_rightd,
    icmc_rightu
} ic_mouse_c;

void x11_init(void);
void mouse_move(uint16_t x, uint16_t y);
void mouse_event(ic_mouse_c in);

#endif