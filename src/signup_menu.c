#include <string.h>

#include "../include/ncursesw/ncurses.h"
#include "../headers/menus.h"
#include "../headers/utils.h"
#include <unistd.h>
#include <ctype.h>
#include <time.h>

void draw_signup_menu(WINDOW *win, char *username, char *email, int password_length, int selected_option) {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    clear();
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+'); // Create a custom box


    h_centerprint(4, "WELCOME TO ROGUE");
    mvwprintw(win, 1, 1, "%d", selected_option);

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
        char email_field[100];
        int underscores = 30 - strlen(email);
        strcpy(email_field, email);
        for (int i = 0; i < underscores; i++) {
            strcat(email_field, "_");
        }
        mvwprintw(win, 10, (COLS - 26) / 2 + 1, "Email   : %s", email_field);
        attroff(COLOR_PAIR(1));
    } else {
        char email_field[100];
        int underscores = 30 - strlen(email);
        strcpy(email_field, email);
        for (int i = 0; i < underscores; i++) {
            strcat(email_field, "_");
        }
        mvwprintw(win, 10, (COLS - 26) / 2 + 1, "Email   : %s", email_field);
    }
    if (selected_option == 3) {
        attron(COLOR_PAIR(1));
        h_centerprint(12, "SIGN UP");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(12, "SIGN UP");
    }


    if (selected_option == 4) {
        attron(COLOR_PAIR(1));
        h_centerprint(15, "Have an account? Sign in here!");
        attroff(COLOR_PAIR(1));
    } else {
        h_centerprint(15, "Have an account? Sign in here!");
    }

    refresh();
}

MenuState handle_signup_menu(WINDOW *win) {
    keypad(stdscr, TRUE);
    char username[100] = "";
    char email[100] = "";
    char password[100] = "";

    wclear(win);

    int selected_option = 0;
    /*
     * 0: Username
     * 1: Password
     * 2: Signup
     * 3 Signin
     */

    while (TRUE) {
        if (selected_option < 0) selected_option = 0;
        if (selected_option > 4) selected_option = 4;
        draw_signup_menu(win, username, email, strlen(password), selected_option);
        refresh();
        int c = wgetch(win);
        switch (c) {
            case 10:
                mvwprintw(win, 1, 1, "Hey!");
                switch (selected_option) {
                    case 0:
                        echo();
                        username[0] = '\0';
                        draw_signup_menu(win, username, email, strlen(password), selected_option);
                        mvwgetstr(win, 8, (COLS - 26) / 2 + 11, username);
                        break;
                    case 1:
                        noecho();
                        mvwgetstr(win, 9, (COLS - 26) / 2 + 11, password);
                        echo();
                        break;
                    case 2:
                        echo();
                        email[0] = '\0';
                        draw_signup_menu(win, username, email, strlen(password), selected_option);
                        mvwgetstr(win, 10, (COLS - 26) / 2 + 11, email);
                        break;
                    case 3:
                        clear();
                        if (!password_check(password)) {
                            username[0] = '\0';
                            password[0] = '\0';
                            email[0] = '\0';
                            h_centerprint(7, "Password is not strong enough");
                            h_centerprint(8, "Try again");
                            refresh();
                            sleep(3);
                            clear();
                            selected_option = 0;
                            draw_signup_menu(win, username, email, strlen(password), selected_option);
                            break;
                        }

                        if (!email_check(email)) {
                            username[0] = '\0';
                            password[0] = '\0';
                            email[0] = '\0';
                            h_centerprint(7, "Email format is not true");
                            h_centerprint(8, "Try again");
                            refresh();
                            sleep(3);
                            selected_option = 0;
                            draw_signup_menu(win, username, email, strlen(password), selected_option);
                            break;
                        }

                        if (signup(username, password, email)) {
                            h_centerprint(7, "Successfully signed up!");
                            h_centerprint(8, "Now you can sign in to your account");
                            refresh();
                            sleep(3);
                            return MENU_SIGNIN;
                        } else {
                            username[0] = '\0';
                            password[0] = '\0';
                            email[0] = '\0';
                            h_centerprint(7, "Username already taken");
                            h_centerprint(8, "Try again");
                            refresh();
                            sleep(3);
                            selected_option = 0;
                            draw_signup_menu(win, username, email, strlen(password), selected_option);
                        }
                        break;
                    case 4:
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

int password_check(char *password) {
    int has_digit = 0, has_lower = 0, has_upper = 0;
    int length = strlen(password);

    if (length < 8) {
        return 0; // Password too short
    }

    for (int i = 0; i < length; i++) {
        if (isdigit(password[i])) has_digit = 1;
        if (islower(password[i])) has_lower = 1;
        if (isupper(password[i])) has_upper = 1;
    }

    return (has_digit && has_lower && has_upper);
}


int email_check(char *email) {
    int at_count = 0;
    const char *at_ptr = NULL;
    const char *dot_ptr = NULL;

    int length = strlen(email);
    if (length < 5) return 0; // Too short to be a valid email

    for (int i = 0; i < length; i++) {
        if (email[i] == '@') {
            at_count++;
            at_ptr = &email[i];
        } else if (email[i] == '.' && at_ptr) {
            dot_ptr = &email[i];
        }
    }

    // Valid email format conditions:
    return (at_count == 1) && // Exactly one '@'
           (at_ptr > email) && // '@' is not the first character
           (dot_ptr > at_ptr + 1) && // '.' comes after '@' and not immediately
           (dot_ptr < email + length - 1); // '.' is not the last character
}

int signup(char *username, char *password, char *email) {
    FILE *file = fopen("../data/users.txt", "r"); // Open file in read mode to check for existing usernames
    if (file == NULL) {
        return 0;
    }

    char line[100 + 100 + 3];
    // Check if username already exists
    while (fgets(line, sizeof(line), file)) {
        char *user = strtok(line, ":");
        if (user && strcmp(user, username) == 0) {
            fclose(file);
            return 0; // Username is already taken, exit function
        }
    }
    fclose(file);

    // Open the file in append mode to add new user
    file = fopen("../data/users.txt", "a");
    if (file == NULL) {
        return 0;
    }

    // Prepare the user credentials in the format "user:pass:0"
    char user_entry[100 + 100 + 3]; // +3 for ":" and ":0" at the end
    // User : Pass : Email : High Score : Gold : Games : Experience
    time_t now;
    time(&now);
    snprintf(user_entry, sizeof(user_entry), "%s:%s:%s:0:0:0:%ld\n", username, password, email, now);

    // Write the user entry to the file
    fprintf(file, "%s", user_entry);
    fclose(file);

    return 1;
}
