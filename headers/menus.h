//
// Created by Nautilus on 2/2/2025.
//

#ifndef HANDLE_MENUS_H
#define HANDLE_MENUS_H

#include <time.h>

#include "../include/ncursesw/curses.h"

typedef enum {
    MENU_SIGNUP,
    MENU_SIGNIN,
    MENU_MAIN,
    NEW_GAME,
    CONTINUE_GAME,
    MENU_SETTINGS,
    MENU_LEADERBOARD,
    MENU_WIN,
    MENU_LOSE,
    EXIT
} MenuState;

typedef struct {
    char username[100];
    int highscore;
    char password[100];
    char email[100];
    int golds;
    int games;
    time_t experience; // Store as time_t
} Account;

typedef struct {
    char *username;  // Dynamic allocation required
    int highscore;
} User;


extern User signed_in_user;

void signin_user(char *user);
void signin_as_guest();
void show_menu(MenuState state);
MenuState handle_signin_menu(WINDOW *win);
void draw_signin_menu(WINDOW *win, char *username, int password_length, int selected_option);
int signin(char *username, char *password);

MenuState handle_signup_menu(WINDOW *win);
void draw_signup_menu(WINDOW *win, char *username,char *email, int password_length, int selected_option);
int signup(char *username, char *password ,char *email);
int password_check(char *password);
int email_check(char *email);

MenuState handle_main_menu(WINDOW *win);
void draw_main_menu(WINDOW *win, int selected_option);

MenuState handle_settings_menu(WINDOW *win);
void draw_settings_menu(WINDOW *win, int selected_option);


MenuState handle_leaderboard_menu(WINDOW *win);
MenuState handle_new_game(WINDOW *win);

int get_user_stat(const char *username, const char *stat);
void set_user_stat(const char *username, const char *stat, int value);

MenuState win_game_menu(WINDOW *win);
MenuState lose_game_menu(WINDOW *win);

#endif //HANDLE_MENUS_H
