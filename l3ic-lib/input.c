#include "input.h"

void input_init(void) {
    disp = XOpenDisplay(0);
	rwin = XRootWindow(disp, XDefaultScreen(disp));
}

void mouse_move(uint16_t x, uint16_t y) {
    XTestFakeMotionEvent(disp, 0, x, y, CurrentTime);
    XFlush(disp);
}

void mouse_event(ic_mouse_c in) {
    switch (in) {
        case icmc_leftd:
            XTestFakeButtonEvent(disp, 1, True, CurrentTime);
            break;
        case icmc_leftu:
            XTestFakeButtonEvent(disp, 1, False, CurrentTime);
            break;
        case icmc_rightd:
            XTestFakeButtonEvent(disp, 3, True, CurrentTime);
            break;
        case icmc_rightu:
            XTestFakeButtonEvent(disp, 3, False, CurrentTime);
            break;
        case icmc_middled:
            XTestFakeButtonEvent(disp, 2, True, CurrentTime);
            break;
        case icmc_middleu:
            XTestFakeButtonEvent(disp, 2, False, CurrentTime);
            break;
        case icmc_scrollud:
            XTestFakeButtonEvent(disp, 4, True, CurrentTime);
            break;
        case icmc_scrolluu:
            XTestFakeButtonEvent(disp, 4, False, CurrentTime);
            break;
        case icmc_scrolldd:
            XTestFakeButtonEvent(disp, 5, True, CurrentTime);
            break;
        case icmc_scrolldu:
            XTestFakeButtonEvent(disp, 5, False, CurrentTime);
            break;
        default:
            break;
    }

    XFlush(disp);
}

void keyboard_event(unsigned in, _Bool press) {
    XTestFakeKeyEvent(disp, XKeysymToKeycode(disp, in), press, CurrentTime);
    XFlush(disp);
}

ic_cur_pos mouse_get_cursor(void) {
    int win_x, win_y, root_x, root_y = 0;
    unsigned int mask = 0;
    Window child_win, root_win;
    XQueryPointer(disp, rwin, &child_win, &root_win, &root_x, &root_y, &win_x, &win_y, &mask);

    ic_cur_pos cursor_pos = {
        .x = root_x,
        .y = root_y
    };

    return cursor_pos;
}

ic_pixel get_screen_pixel(uint16_t x, uint16_t y) {
    XColor color;
    XImage *image;

    image = XGetImage(disp, XRootWindow(disp, XDefaultScreen(disp)), x, y, 1, 1, AllPlanes, XYPixmap);
    color.pixel = XGetPixel(image, 0, 0);
    XFree(image);

    XQueryColor (disp, XDefaultColormap(disp, XDefaultScreen(disp)), &color);
    
    ic_pixel pixel = {
        .r = color.red / 256,
        .g = color.green / 256,
        .b = color.blue / 256
    };

    return pixel;
}

void input_free(void) {
    XCloseDisplay(disp);

    disp = None;
	rwin = None;
}
