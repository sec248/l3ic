#ifndef _X11_H
#define _X11_H

#include <X11/Xlib.h>
#include <stdint.h>

static Display *disp;
static Window rwin;

void x11_init(void);
void move_mouse(uint16_t x, uint16_t y);

#endif