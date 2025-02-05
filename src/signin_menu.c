#include <string.h>

#include "../include/ncursesw/ncurses.h"
#include "../headers/menus.h"
#include "../headers/utils.h"
#include <unistd.h>

void draw_signin_menu(WINDOW *win, char *username, int password_length, int selected_option) {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    clear();
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+'); // Create a custom box


    h_centerprint(4, "SIGN IN TO YOUR ROGUE ACCOUNT");
    mvwprintw(win, 1, 1, "%d %d", COLS , LINES);

    if (selected_option == 0) {
        attron(COLOR_PAIR(1));
        char username_field[100];
        int underscores = 16 - strlen(username);
        strcpy(username_field, username);
        for (int i = 0; i < underscores; i++) {
            strcat(username_field, "_");
        }
        mvwprintw(win, 8, (COLS - 26) / 2 + 1, "Username: %s", username_field);
        attroff(COLOR_PAIR(1));
    } else {
        char username_field[100];
        int underscores = 16 - strlen(username);
        strcpy(username_field, username);
        for (int i = 0; i < underscores; i++) {
            strcat(username_field, "_");
        }
        mvwprintw(win, 8, (COLS - 26) / 2 + 1, "Username: %s", username_field);
    }

    if (selected_option == 1) {
        char password_field[100] = "";
        int underscores = 16 - password_length;
        for (int i = 0; i < password_length; i++) {
            strcat(password_field, "*");
        }
        for (int i = 0; i < underscores; i++) {
            strcat(password_field, "_");
        }
        attron(COLOR_PAIR(1));
        mvwprintw(win, 9, (COLS - 26) / 2 + 1, "Password: %s", password_field);
        attroff(COLOR_PAIR(1));
    } else {
        char password_field[100] = "";
        int underscores = 16 - password_length;
        for (int i = 0; i < password_length; i++) {
            strcat(password_field, "*");
        }
        for (int i = 0; i < underscores; i++) {
            strcat(password_field, "_");
        }
        mvwprintw(win, 9, (COLS - 26) / 2 + 1, "Password: %s", password_field);
    }

    if (selected_option == 2) {
        attron(COLOR_PAIR(1));
        h_centerprint(12, "SIGN IN");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(12, "SIGN IN");
    }

    if (selected_option == 3) {
        attron(COLOR_PAIR(1));
        h_centerprint(15, "Forgot your password?");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(15, "Forgot your password?");
    }

    if (selected_option == 4) {
        attron(COLOR_PAIR(1));
        h_centerprint(16, "New to game? Sign up here!");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(16, "New to game? Sign up here!");
    }

    if (selected_option == 5) {
        attron(COLOR_PAIR(1));
        h_centerprint(18, "Login as guest");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(18, "Login as guest");
    }

    refresh();
}

MenuState handle_signin_menu(WINDOW *win) {
    keypad(stdscr, TRUE);
    char username[100] = "";
    char password[100] = "";

    wclear(win);

    int selected_option = 0;
    /*
     * 0: Username
     * 1: Password
     * 2: Signin
     * 3: Forgot Password
     * 4: Signup
     */

    while (TRUE) {
        if (selected_option < 0) selected_option = 0;
        if (selected_option > 5) selected_option = 5;
        draw_signin_menu(win, username, strlen(password), selected_option);
        refresh();
        int c = wgetch(win);
        switch (c) {
            case 10:
                mvwprintw(win, 1, 1, "Filling Field");
                switch (selected_option) {
                    case 0:
                        echo();
                        username[0] = '\0';
                        draw_signin_menu(win, username, strlen(password), selected_option);
                        mvwgetstr(win, 8, (COLS - 26) / 2 + 11, username);
                        break;
                    case 1:
                        noecho();
                        mvwgetstr(win, 9, (COLS - 26) / 2 + 11, password);
                        echo();
                        break;
                    case 2:
                        clear();
                        if (signin(username, password)) {
                            signin_user(username);
                            h_centerprint(7, "Successfully signed in!");
                            refresh();
                            sleep(3);
                            return MENU_MAIN;
                        } else {
                            username[0] = '\0';
                            password[0] = '\0';
                            h_centerprint(7, "Your credential is incorrect!");
                            h_centerprint(8, "Try again");
                            refresh();
                            sleep(3);
                            selected_option = 0;
                            draw_signin_menu(win, username, strlen(password), selected_option);
                        }
                        break;
                    case 3:
                        clear();
                        h_centerprint(7, "No way! ");
                        refresh();
                        sleep(3);
                        return EXIT;
                    case 4:
                        clear();
                        return MENU_SIGNUP;
                    case 5:
                        clear();
                        signin_as_guest();
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


int signin(char *username, char *password) {
    FILE *file = fopen("../data/users.txt", "r");
    if (!file) {
        return 0;
    }

    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        char file_user[1000], file_pass[1000], file_email[1000];
        int highscore, golds, games;
        long int xp;
        if (sscanf(line, "%[^:]:%[^:]:%[^:]:%d:%d:%d:%ld", file_user, file_pass, file_email, &highscore, &golds, &games, &xp) == 7) {
            if (strcmp(username, file_user) == 0 && strcmp(password, file_pass) == 0) {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    return 0;
}
