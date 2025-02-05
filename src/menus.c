//
// Created by Nautilus on 2/2/2025.
//

#include "../headers/menus.h"

#include <stdlib.h>
#include <string.h>

User signed_in_user = {"Guest", 0};

#include <string.h>
#include <stdlib.h>

void signin_user(char *user) {
    // Allocate memory for the username and copy the string
    signed_in_user.username = strdup(user); // Use strdup to allocate and copy the string

    if (signed_in_user.username == NULL) {
        // Handle memory allocation failure if needed
        return;
    }

    FILE *file = fopen("../data/users.txt", "r");
    if (!file) {
        return;
    }

    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        char file_user[1000], file_pass[1000];
        int highscore;
        if (sscanf(line, "%[^:]:%[^:]:%d", file_user, file_pass, &highscore) == 3) {
            if (strcmp(user, file_user) == 0) {
                fclose(file);
                signed_in_user.highscore = highscore;
                return; // User found, exit function
            }
        }
    }

    fclose(file);
}


void signin_as_guest() {
    // Free any existing username memory
    if (signed_in_user.username != NULL) {
        signed_in_user.username = NULL;
    }

    // Set it to a static "Guest" string
    signed_in_user.username = strdup("Guest");
    signed_in_user.highscore = 0;
}


void show_menu(MenuState state) {
}

int get_user_stat(const char *username, const char *stat) {
    FILE *file = fopen("../data/users.txt", "r");
    if (!file) return -1;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char uname[50], pass[50], email[100];
        int highscore, golds, games;
        time_t experience;

        if (sscanf(line, "%49[^:]:%49[^:]:%99[^:]:%d:%d:%d:%ld",
                   uname, pass, email, &highscore, &golds, &games, &experience) == 7) {
            if (strcmp(uname, username) == 0) {
                fclose(file);
                if (strcmp(stat, "highscore") == 0) return highscore;
                else if (strcmp(stat, "golds") == 0) return golds;
                else if (strcmp(stat, "games") == 0) return games;
            }
        }
    }
    fclose(file);
    return -1;
}

void set_user_stat(const char *username, const char *stat, int value) {
    FILE *file = fopen("../data/users.txt", "r");
    if (!file) return;

    Account users[100];
    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), file) && count < 100) {
        char uname[100], pass[100], email[100];
        int highscore, golds, games;
        time_t experience;

        if (sscanf(line, "%99[^:]:%99[^:]:%99[^:]:%d:%d:%d:%ld",
                   uname, pass, email, &highscore, &golds, &games, &experience) == 7) {
            strcpy(users[count].username, uname);
            strcpy(users[count].password, pass);
            strcpy(users[count].email, email);
            users[count].highscore = highscore;

            users[count].golds = golds;
            users[count].games = games;
            users[count].experience = experience;
            count++;
        }
    }
    fclose(file);

    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(stat, "highscore") == 0) users[i].highscore = value;
            else if (strcmp(stat, "golds") == 0) users[i].golds = value;
            else if (strcmp(stat, "games") == 0) users[i].games = value;
            break;
        }
    }

    file = fopen("../data/users.txt", "w");
    if (!file) return;
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s:%s:%s:%d:%d:%d:%ld\n",
                users[i].username, users[i].password, users[i].email,
                users[i].highscore, users[i].golds, users[i].games, users[i].experience);
    }
    fclose(file);
}
