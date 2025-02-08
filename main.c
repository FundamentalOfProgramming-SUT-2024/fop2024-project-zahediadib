#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "headers/game.h"
#include "./include/ncursesw/ncurses.h"
#include "headers/menus.h"



int main(void) {

    srand(time(NULL));
    initscr();
    // getch();
    cbreak();
    noecho();
    if (!has_colors()) {
        endwin();
        return 1;
    }
    curs_set(0);
    mvprintw(5, 5, "Loading ...");
    refresh();
    usleep(300000);

    MenuState state = MENU_SIGNIN;
    while (true) {
        int br = 0;
        switch (state) {
            case MENU_SIGNIN:
                state = handle_signin_menu(stdscr); // استفاده از پنجره پیش‌فرض stdscr
                break;
            case MENU_SIGNUP:
                state = handle_signup_menu(stdscr);
                break;
            case MENU_MAIN:
                state = handle_main_menu(stdscr);
                break;
            case MENU_LEADERBOARD:
                state = handle_leaderboard_menu(stdscr);
                break;
            case MENU_PROFILE:
                state = handle_profile_menu(stdscr);
                break;
            case NEW_GAME:
                if (strcmp(signed_in_user.username, "Guest")) {
                    set_user_stat(signed_in_user.username, "games",
                                  get_user_stat(signed_in_user.username, "games") + 1);
                }
                reset_game();
                init_map();
                state = handle_new_game(stdscr);
                break;

            case MENU_WIN:
                state = win_game_menu(stdscr);
                break;
            case MENU_LOSE:
                state = lose_game_menu(stdscr);
                break;
            case MENU_SETTINGS:
                state = handle_settings_menu(stdscr);
                break;
            case EXIT:
                br = 1;
                break;
            default:
                br = 1;
                break;
        }
        if (br) break;

    }
    endwin();

    return 1;
}
