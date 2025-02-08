#include <string.h>

#include "../include/ncursesw/ncurses.h"
#include "../headers/menus.h"
#include "../headers/utils.h"
#include "../headers/user.h"
#include <unistd.h>

void draw_main_menu(WINDOW *win, int selected_option) {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    clear();
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+'); // Create a custom box


    h_centerprint(2, "__________                             ");
    h_centerprint(3, "\\______   \\ ____   ____  __ __   ____");
    h_centerprint(4, " |       _//  _ \\ / ___\\|  |  \\_/ __ \\ ");
    h_centerprint(5, " |    |   (  <_> ) /_/  >  |  /\\  ___/ ");
    h_centerprint(6, " |____|_  /\\____/\\___  /|____/  \\___  >");
    h_centerprint(7, "        \\/      /_____/             \\/ ");

    mvwprintw(win, 1, 1, "%d", selected_option);


    char welcome[100] = "Welcome ";

    strcat(welcome, signed_in_user.username);
    h_centerprint(9, welcome);

    if (selected_option == 0) {
        attron(COLOR_PAIR(1));
        h_centerprint(13, "New Game");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(13, "New Game");
    }

    if (selected_option == 1) {
        attron(COLOR_PAIR(1));
        h_centerprint(14, "Continue Game");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(14, "Continue Game");
    }

    if (selected_option == 2) {
        attron(COLOR_PAIR(1));
        h_centerprint(15, "Leaderboard");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(15, "Leaderboard");
    }

    if (selected_option == 3) {
        attron(COLOR_PAIR(1));
        h_centerprint(16, "Settings");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(16, "Settings");
    }

    if (selected_option == 4) {
        attron(COLOR_PAIR(1));
        h_centerprint(17, "Profile");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(17, "Profile");
    }

    if (selected_option == 5) {
        attron(COLOR_PAIR(1));
        h_centerprint(19, "Sign out");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(19, "Sign out");
    }

    refresh();
}

MenuState handle_main_menu(WINDOW *win) {
    keypad(stdscr, TRUE);
    wclear(win);

    int selected_option = 0;

    while (TRUE) {
        if (selected_option < 0) selected_option = 0;
        if (selected_option > 5) selected_option = 5;
        draw_main_menu(win, selected_option);
        refresh();
        int c = wgetch(win);
        switch (c) {
            case 10:
                clear();
                refresh();
                switch (selected_option) {
                    case 0:

                        return NEW_GAME;
                        break;
                    case 1:
                        return CONTINUE_GAME;
                        break;
                    case 2:
                        return MENU_LEADERBOARD;
                        break;
                    case 3:
                        return MENU_SETTINGS;
                    case 4:
                        return MENU_PROFILE;
                    case 5:
                        signed_in_user.username = "Guest";
                        signed_in_user.highscore = 0;
                        return MENU_SIGNIN;
                    default:
                        return EXIT;
                }
            case KEY_DOWN:
                selected_option++;
                continue;
            case KEY_UP:
                selected_option--;
                continue;
            case 'Q':
                return EXIT;
            default:
                break;
        }
    }
}
