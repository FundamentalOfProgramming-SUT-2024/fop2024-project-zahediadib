#include <stdio.h>
#include "../include/ncursesw/ncurses.h"
#include "../headers/menus.h"
#include "../headers/utils.h"

MenuState win_game_menu(WINDOW *win) {
    clear();
    refresh();
    FILE *file = fopen("../data/score.txt", "r");
    int score;
    fscanf(file, "%d", &score);
    fclose(file);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);

    attron(COLOR_PAIR(1));
    h_centerprint(2, "<<< YOU WIN >>>");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    h_centerprint(4, "\"The harder the battle, the sweeter the victory.\"");
    h_centerprint(5, "Les Brown");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    char temp[20];
    sprintf(temp, "Your score: %d", score);
    h_centerprint(7, temp);
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    h_centerprint(11, "Developed by Nautilus");
    h_centerprint(12, "Contact:  @zahediadib");
    h_centerprint(13, "GitHub:   /zahediadib");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    int ART_START = LINES - 20 - 1;
    int i = 0;
    h_centerprint(ART_START + i, "*******************************************************************************");
    i++;
    h_centerprint(ART_START + i, "          |                   |                  |                     |       ");
    i++;
    h_centerprint(ART_START + i, " _________|________________.=\"\"_;=.______________|_____________________|_______");
    i++;
    h_centerprint(ART_START + i, "|                   |  ,-\"_,=\"\"     `\"=.|                  |                   ");
    i++;
    h_centerprint(ART_START + i, "|___________________|__\"=._o`\"-._        `\"=.______________|___________________");
    i++;
    h_centerprint(ART_START + i, "          |                `\"=._o`\"=._      _`\"=._                     |       ");
    i++;
    h_centerprint(ART_START + i, " _________|_____________________:=._o \"=._.\"_.-=\"'\"=.__________________|_______");
    i++;
    h_centerprint(ART_START + i,
                  "|                   |    __.--\" , ; `\"=._o.\" ,-\"\"\"-._ \".   |                   ");
    i++;
    h_centerprint(ART_START + i, "|___________________|_._\"  ,. .` ` `` ,  `\"-._\"-._   \". '__|___________________");
    i++;
    h_centerprint(ART_START + i,
                  "          |           |o`\"=._` , \"` `; .\". ,  \"-._\"-._; ;              |       ");
    i++;
    h_centerprint(ART_START + i,
                  " _________|___________| ;`-.o`\"=._; .\" ` '`.\"\\` . \"-._ /_______________|_______");
    i++;
    h_centerprint(ART_START + i, "|                   | |o;    `\"-.o`\"=._``  '` \" ,__.--o;   |                   ");
    i++;
    h_centerprint(ART_START + i, "|___________________|_| ;     (#) `-.o `\"=.`_.--\"_o.-; ;___|___________________");
    i++;
    h_centerprint(ART_START + i, "____/______/______/___|o;._    \"      `\".o|o_.--\"    ;o;____/______/______/____");
    i++;
    h_centerprint(ART_START + i, "/______/______/______/_\"=._o--._        ; | ;        ; ;/______/______/______/_");
    i++;
    h_centerprint(ART_START + i, "____/______/______/______/__\"=._o--._   ;o|o;     _._;o;____/______/______/____");
    i++;
    h_centerprint(ART_START + i, "/______/______/______/______/____\"=._o._; | ;_.--\"o.--\"_/______/______/______/_");
    i++;
    h_centerprint(ART_START + i, "____/______/______/______/______/_____\"=.o|o_.--\"\"___/______/______/______/____");
    i++;
    h_centerprint(ART_START + i, "/______/______/______/______/______/______/______/______/______/______/Nautilus");
    i++;
    h_centerprint(ART_START + i, "*******************************************************************************");
    i++;
    refresh();
    attroff(COLOR_PAIR(3));


    h_centerprint(LINES - 1, "Press any key to continue ... ");
    refresh();
    getch();
    return MENU_MAIN;
}
