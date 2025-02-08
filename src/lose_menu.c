#include <stdio.h>
#include "../include/ncursesw/ncurses.h"
#include "../headers/menus.h"
#include "../headers/utils.h"

MenuState lose_game_menu(WINDOW *win) {
    clear();
    refresh();
    FILE *file = fopen("../data/score.txt", "r");
    int score;
    fscanf(file, "%d", &score);
    fclose(file);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_RED);

    attron(COLOR_PAIR(1));
    h_centerprint(2, "<<< YOU LOSE >>>");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    h_centerprint(4, "Maybe next time ...");
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

    attron(COLOR_PAIR(1));
    int ART_START = LINES - 21 - 1;
    int i = -1;

    h_centerprint(ART_START + i , "                 ...                              "); i++;
    h_centerprint(ART_START + i , "               ;::::;                             "); i++;
    h_centerprint(ART_START + i , "             ;::::; :;                            "); i++;
    h_centerprint(ART_START + i , "           ;:::::'   :;                           "); i++;
    h_centerprint(ART_START + i , "          ;:::::;     ;.                          "); i++;
    h_centerprint(ART_START + i , "         ,:::::'       ;           OOO\\           "); i++;
    h_centerprint(ART_START + i , "         ::::::;       ;          OOOOO\\          "); i++;
    h_centerprint(ART_START + i , "         ;:::::;       ;         OOOOOOOO         "); i++;
    h_centerprint(ART_START + i , "        ,;::::::;     ;'         / OOOOOOO        "); i++;
    h_centerprint(ART_START + i , "      ;:::::::::`. ,,,;.        /  / DOOOOOO      "); i++;
    h_centerprint(ART_START + i , "    .';:::::::::::::::::;,     /  /     DOOOO     "); i++;
    h_centerprint(ART_START + i , "   ,::::::;::::::;;;;::::;,   /  /        DOOO    "); i++;
    h_centerprint(ART_START + i , "  ;`::::::`'::::::;;;::::: ,#/  /          DOOO   "); i++;
    h_centerprint(ART_START + i , "  :`:::::::`;::::::;;::: ;::#  /            DOOO  "); i++;
    h_centerprint(ART_START + i , "  ::`:::::::`;:::::::: ;::::# /              DOO  "); i++;
    h_centerprint(ART_START + i , "  `:`:::::::`;:::::: ;::::::#/               DOO  "); i++;
    h_centerprint(ART_START + i , "   :::`:::::::`;; ;:::::::::##                OO  "); i++;
    h_centerprint(ART_START + i , "   ::::`:::::::`;::::::::;:::#                OO  "); i++;
    h_centerprint(ART_START + i , "   `:::::`::::::::::::;'`:;::#                O   "); i++;
    h_centerprint(ART_START + i , "    `:::::`::::::::;' /  / `:#                    "); i++;
    h_centerprint(ART_START + i , "     ::::::`:::::;'  /  /   `#                    "); i++;

    refresh();
    attroff(COLOR_PAIR(1));


    h_centerprint(LINES - 1, "Press any key to continue ... ");
    refresh();
    getch();
    return MENU_MAIN;
}
