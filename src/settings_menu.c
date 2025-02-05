#include <string.h>

#include "../include/ncursesw/ncurses.h"
#include "../headers/menus.h"
#include "../headers/utils.h"
#include "../headers/user.h"
#include <unistd.h>

void draw_settings_menu(WINDOW *win, int selected_option) {
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

    h_centerprint(9, "Settings");

    if (selected_option == 0) {
        attron(COLOR_PAIR(1));
        h_centerprint(13, "Hero Color");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(13, "Hero Color");
    }

    if (selected_option == 1) {
        attron(COLOR_PAIR(1));
        h_centerprint(14, "Difficulty");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(14, "Difficulty");
    }

    if (selected_option == 2) {
        attron(COLOR_PAIR(1));
        h_centerprint(16, "Return to Main Menu");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(16, "Return to Main Menu");
    }

    refresh();
}

MenuState handle_settings_menu(WINDOW *win) {
    keypad(stdscr, TRUE);
    wclear(win);

    int selected_option = 0;

    while (TRUE) {
        if (selected_option < 0) selected_option = 0;
        if (selected_option > 2) selected_option = 2;
        draw_settings_menu(win, selected_option);
        refresh();
        int c = wgetch(win);
        switch (c) {
            case 10:
                clear();
                refresh();
                switch (selected_option) {
                    case 0:
                        clear();
                        refresh();

                        h_centerprint(3, "Hero Color");

                        h_centerprint(6, "1. White");
                        h_centerprint(7, "2. Blue");
                        h_centerprint(8, "3. Green");
                        h_centerprint(9, "4. Yellow");
                        h_centerprint(10, "5. Magenta");
                        h_centerprint(12, "<< Enter the number of color you want >>");
                        noecho();
                        char color = getch();
                        if (color > '5') color = '5';
                        if (color < '1') color = '1';
                        FILE *filec = fopen("../data/color.txt", "w");
                        char score_c[10];
                        sprintf(score_c, "%c", color);
                        fwrite(score_c, sizeof(score_c), 1, filec);
                        fclose(filec);
                        echo();
                        return MENU_SETTINGS;
                        break;
                    case 1:
                        clear();
                        refresh();

                        h_centerprint(3, "Difficulty");

                        h_centerprint(6, "1. Easy");
                        h_centerprint(7, "2. Medium");
                        h_centerprint(8, "3. Hard");
                        h_centerprint(10, "<< Enter the number of difficulty you want >>");
                        noecho();
                        char diff = getch();
                        if (diff > '3') diff = '3';
                        if (diff < '1') diff = '1';
                        FILE *filed = fopen("../data/diff.txt", "w");
                        char score_d[10];
                        sprintf(score_d, "%c", diff);
                        fwrite(score_d, sizeof(score_d), 1, filed);
                        fclose(filed);
                        echo();
                        return MENU_SETTINGS;
                        break;
                    case 2:
                        return MENU_MAIN;
                        break;
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
