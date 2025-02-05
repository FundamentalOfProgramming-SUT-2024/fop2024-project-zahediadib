//
// Created by Nautilus on 2/2/2025.
//

#include "../headers/utils.h"
#include <string.h>
#include "../include/ncursesw/curses.h"



void h_centerprint(int y, char *s) {
    mvprintw(y, (COLS - strlen(s)) / 2 + 1, "%s", s);
}

void v_centerprint(int x, char *s) {
    mvprintw((LINES) / 2 + 1, x,  "%s", s);
}

void hv_centerprint( char *s) {
    mvprintw((LINES) / 2 + 1, (COLS - strlen(s)) / 2 + 1, "%s", s);
}