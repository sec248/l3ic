#include "x11.h"

void x11_init(void) {
    disp = XOpenDisplay(0);
	rwin = XRootWindow(disp, XDefaultScreen(disp));
}

void move_mouse(uint16_t x, uint16_t y) {
    XWarpPointer(disp, None, rwin, 0, 0, 0, 0, x, y);
    XFlush(disp);
}