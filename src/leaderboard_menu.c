#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/ncursesw/ncurses.h"
#include "../headers/menus.h"
#include "../headers/utils.h"
#include <time.h>

#define MAX_USERS 100

int compare_users(const void *a, const void *b) {
    return ((Account *)b)->highscore - ((Account *)a)->highscore;
}

MenuState handle_leaderboard_menu(WINDOW *win) {
    FILE *file = fopen("../data/users.txt", "r");
    if (!file) return MENU_MAIN;

    Account users[MAX_USERS];
    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) && count < MAX_USERS) {
        char username[50], pass[50], email[100];
        int highscore, golds, games;
        time_t experience;

        if (sscanf(line, "%49[^:]:%49[^:]:%99[^:]:%d:%d:%d:%ld",
                   username, pass, email, &highscore, &golds, &games, &experience) == 7) {
            strcpy(users[count].username, username);
            users[count].highscore = highscore;
            users[count].golds = golds;
            users[count].games = games;
            users[count].experience = experience;

            count++;
        }
    }
    fclose(file);

    qsort(users, count, sizeof(Account), compare_users);

    initscr();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_YELLOW);  // Gold
    init_pair(2, COLOR_BLACK, COLOR_CYAN);    // Silver
    init_pair(3, COLOR_BLACK, COLOR_MAGENTA); // Bronze
    init_pair(4, COLOR_WHITE, COLOR_BLUE);    // Player highlight
    noecho();
    curs_set(0);

    int start_y = 7;
    h_centerprint(4, "Leaderboard");
    char caption[200];
    sprintf(caption," %c %-20s %-10s %-8s %-8s %s", '#', "Username", "Highscore", "Golds", "Games", "Experience");
    h_centerprint(6, caption);

    for (int i = 0; i < count; i++) {
        if (signed_in_user.username == NULL) {
            strcpy(signed_in_user.username, "Guest"); // Or handle differently
        }
        if (strcmp(users[i].username, signed_in_user.username) == 0) {
            attron(COLOR_PAIR(4));
        } else if (i == 0) {
            attron(COLOR_PAIR(1));
        } else if (i == 1) {
            attron(COLOR_PAIR(2));
        } else if (i == 2) {
            attron(COLOR_PAIR(3));
        }

        int medal = i + 1;

        char experience_date[20];
        struct tm *tm_info = localtime(&users[i].experience);
        strftime(experience_date, sizeof(experience_date), "%Y-%m-%d", tm_info);

        char record[200];
        if (i == 0) strcat(users[i].username, " (Rogue)");
        if (i == 1) strcat(users[i].username, " (Ace)");
        if (i == 2) strcat(users[i].username, " (Nova)");
        sprintf(record, "%02d %-20s %-10d %-8d %-8d %s",
                 medal, users[i].username, users[i].highscore, users[i].golds, users[i].games, experience_date);

        if (record[0] == '0') record[0] = ' ';
        h_centerprint(start_y + i, record);
        attroff(COLOR_PAIR(1));
        attroff(COLOR_PAIR(2));
        attroff(COLOR_PAIR(3));
        attroff(COLOR_PAIR(4));
    }

    h_centerprint(start_y + count + 2, "Press any key to exit...");
    getch();
    endwin();
    return MENU_MAIN;
}
