#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/ncursesw/ncurses.h"
#include "../headers/menus.h"
#include "../headers/utils.h"
#include <time.h>

#define MAX_USERS 100

MenuState handle_profile_menu(WINDOW *win) {
    initscr();
    start_color();

    noecho();
    curs_set(0);

    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(4, COLOR_WHITE, COLOR_BLUE);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);

    if (signed_in_user.username == NULL) {
        strcpy(signed_in_user.username, "Guest"); // Or handle differently
    }

    if (!strcmp(signed_in_user.username,"Guest")) {
        attron(COLOR_PAIR(1));
        h_centerprint(2, "You signed in as a guest");
        h_centerprint(3, "To visit your profile, please sign in with your credentials");
        attroff(COLOR_PAIR(1));
        h_centerprint(6, "Press any key to exit...");
        refresh();
        getch();
        return MENU_MAIN;
    }

    FILE *file = fopen("../data/users.txt", "r");
    if (!file) return MENU_MAIN;

    Account users[MAX_USERS];
    int count = 0;
    char line[256];
    char file_user[1000], file_pass[1000], file_email[1000];
    int highscore, golds, games;
    long int xp;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^:]:%[^:]:%[^:]:%d:%d:%d:%ld", file_user, file_pass, file_email, &highscore, &golds, &games,
                   &xp) == 7) {
            if (strcmp(signed_in_user.username, file_user) == 0) {
                break;
            }
        }
    }

    fclose(file);

    h_centerprint(2, "User Profile");

    char experience_date[20];
    struct tm *tm_info = localtime(&xp);
    strftime(experience_date, sizeof(experience_date), "%Y-%m-%d", tm_info);

    attron(COLOR_PAIR(5));
    mvprintw(10- 3, 25, "Username: %s", file_user);
    mvprintw(11- 3, 25, "Email: %s", file_email);
    mvprintw(12- 3, 25, "Highscore: %d", highscore);
    mvprintw(13- 3, 25, "Games: %d", games);
    mvprintw(14- 3, 25, "Golds: %d", golds);
    mvprintw(15- 3, 25, "Exp: %s", experience_date);
    attroff(COLOR_PAIR(5));

    h_centerprint(17, "Press any key to exit...");
    refresh();
    getch();
    endwin();
    return MENU_MAIN;
}
