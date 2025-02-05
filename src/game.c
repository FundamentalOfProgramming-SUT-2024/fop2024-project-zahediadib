#include "../headers/game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../headers/menus.h"
#include "../include/ncursesw/ncurses.h"

#define MAX_SIZE 100
#define HEIGHT 30
#define WIDTH 100
#define ROOM_MIN_SIZE 5
#define ROOM_MAX_SIZE 13
#define ROOM_COUNT 6
#define CORRIDOR_VISIBLE 1
#define MAX_PILLAR 3
#define MAX_TRAP 3
#define MAX_FOOD 3
#define LOCKED_PASS_LEN 4
#define PASS_TIMEOUT 10
#define MAX_HEALTH 100
#define HEALTH_R 1
#define HUNGER_R 5
#define HEALTH_TIME 20
#define MAX_GOLD 1000


struct ROOM {
    int x, y, height, width, type;
};

struct locked_door {
    int x, y;
    int state;
};

struct secret_door {
    int x, y;
    int state;
};

struct trap {
    int x, y;
    int state;
};

struct food {
    int x, y;
    char *name;
    int color;
    int state;
    int fresh;
};

struct gold {
    int x, y;
    int type;
    int state;
};

struct picked_up {
    int x, y;
    char *name;
    int state;
};

struct picked_up_food {
    int count;
    char *name;
};

struct weapon {
    int x, y;
    char symbol;
    int state;
    int num_collect;
};

struct talisman {
    int x, y;
    int type;
    int state;
    char *name;
};

struct monster {
    int x, y;
    int health;
    int max_health;
    char type;
    int num;
    int state;
    int movement_num;
    int movement_state;
    int level;
};

// structs

char map[HEIGHT][WIDTH];
bool visible[HEIGHT][WIDTH];
bool visited[HEIGHT][WIDTH];
bool trap_visible[HEIGHT][WIDTH];

int hero_color = 1;
char password[5];
time_t password_show_time = 0;

struct locked_door locked[50];
int locked_door_count = 0;

struct secret_door hidden_doors[50];
int secret_door_count = 0;

struct trap traps[50];
int traps_count = 0;

int first = 1;
int level = 1;
bool master_key[5] = {false};
bool first_key[5] = {true};
bool master_keys_broken[5] = {false};

int health = 100;
int hunger = 100;
struct food foods[100];
int food_count = 0;

struct picked_up pocket[100];
int pocket_count;

time_t last_health_update = 0;
time_t last_hunger_update = 0;


struct picked_up_food pocket_food[9];
struct gold golds[MAX_FOOD];
int gold_count = 0;
int gold = 0;
int score = 0;

struct weapon weapons[50];
struct weapon *weapon_in_hand;
int weapon_count = 0;
int wield_choice = 'm';

struct talisman talismans[50];
int talisman_count = 0;
struct ROOM rooms[10][ROOM_COUNT];
int room_count[10] = {0};
int g_state = 0;

struct monster monsters[40];
int monster_count = 0;

int talisman_time_track = 0;
int food_time_out = 50;
int weapon_rate = 1;
int num_of_blocks = 1;

bool used_talisman = false;
bool used_magic_food = false;

char last_direction[3];
bool long_range_weapon = false;

double difficulty_coefficient = 1;

void reset_game() {
    locked_door_count = 0;
    secret_door_count = 0;
    traps_count = 0;
    health = 100;
    hunger = 100;
    first = 1;
    level = 1;
    food_count = 0;
    pocket_count = 0;
    last_health_update = 0;
    last_hunger_update = 0;
    gold_count = 0;
    gold = 0;
    score = 0;
    weapon_count = 0;
    wield_choice = 'm';
    talisman_count = 0;
    for (int i = 0; i < 10; i++) {
        room_count[i] = 0;
    }
    monster_count = 0;
    talisman_time_track = 0;
    food_time_out = 50;
    weapon_rate = 1;
    num_of_blocks = 1;
    used_talisman = false;
    used_magic_food = false;
    difficulty_coefficient = 1;
}


void show_level() {
    attron(COLOR_PAIR(2));
    mvprintw(LINES - 1, 0, "Level: %d", level);
    attroff(COLOR_PAIR(2));
    refresh();
}

void show_gold() {
    attron(COLOR_PAIR(5));
    mvprintw(LINES - 1, COLS / 2 + 12, "Gold: %d", gold);
    attroff(COLOR_PAIR(5));
    refresh();
}

void alert(char *command, int arg) {
    move(0, 0);
    if (strcmp(command, "key broke") == 0) {
        printw("The Master Key broke :(\n");
    } else if (strcmp(command, "fix key") == 0) {
        printw("Would you like to exchange 2 broken Master Keys to enter? (Y/N)\n");
    } else if (strcmp(command, "key fixed") == 0) {
        printw("2 Master Keys have been exchanged. You can now enter.\n");
    } else if (strcmp(command, "picked up key") == 0) {
        attron(COLOR_PAIR(5));
        printw("You picked up a Master Key!\n");
        attroff(COLOR_PAIR(5));
    } else if (strcmp(command, "cheat code M") == 0) {
        attron(COLOR_PAIR(5));
        printw("You have entered into full vision mode.");
        attroff(COLOR_PAIR(5));
    } else if (strcmp(command, "trap around") == 0) {
        attron(COLOR_PAIR(2));
        printw("There are %d traps around you.", arg);
        attroff(COLOR_PAIR(2));
    } else if (strcmp(command, "secret door around") == 0) {
        attron(COLOR_PAIR(2));
        printw("There are %d secret doors around you.", arg);
        attroff(COLOR_PAIR(2));
    } else if (strcmp(command, "picked up food") == 0) {
        attron(COLOR_PAIR(9));
        printw("You picked up some %s!", foods[arg].name);
        attroff(COLOR_PAIR(9));
    } else if (strcmp(command, "picked up gold") == 0) {
        char type[10];
        int added_gold;
        if (arg == 3) {
            strcpy(type, "Skygold");
            added_gold = 100;
        } else {
            strcpy(type, "Stargold");
            added_gold = 50;
        }
        gold += added_gold;
        show_gold();
        attron(COLOR_PAIR(5));
        mvprintw(0, 0, "You picked up a bag of %s", type);
        mvprintw(1, 0, "earned %d more gold!", added_gold);
        attroff(COLOR_PAIR(5));
    } else if (strcmp(command, "picked up weapon") == 0) {
        char weapon_name[20];

        if (arg == 1) strcpy(weapon_name, "Mace");
        else if (arg == 2) strcpy(weapon_name, "Daggger");
        else if (arg == 3) strcpy(weapon_name, "Magic Wand");
        else if (arg == 4) strcpy(weapon_name, "Normal Arrow");
        else strcpy(weapon_name, "Sword");

        printw("You picked up a %s!", weapon_name);
    } else if (strcmp(command, "picked up potion") == 0) {
        char name[20];
        if (arg == 0) strcpy(name, "Healing Salve");
        else if (arg == 1) strcpy(name, "Mask of Madness");
        else strcpy(name, "Boot of Travel");

        printw("You picked up The %s!", name);
    } else if (strcmp(command, "ate food") == 0) {
        attron(COLOR_PAIR(9));
        if (arg == 0) printw("You successfully consumed the food!");
        else if (arg == 1) printw("The Legendary food has doubled your damaging skills!");
        else if (arg == 2) printw("The Magical food has doubled your speed!");
        attroff(COLOR_PAIR(9));
    } else if (strcmp(command, "took weapon") == 0) {
        attron(COLOR_PAIR(9));
        printw("You are now carrying the weapon!");
        attroff(COLOR_PAIR(9));
    } else if (strcmp(command, "enter room") == 0) {
        if (arg == 1) printw("You have entered to Enchant Room!");
        else if (arg == 2) printw("You have entered to Treasure Room!");
    } else if (strcmp(command, "picked up treasure") == 0) {
        attron(COLOR_PAIR(5));
        mvprintw(0, 0, "You've opened the Ancient chest, and golden light floods the room.");
        mvprintw(1, 0, "The Legendary Treasure is yours!");
        attroff(COLOR_PAIR(5));
    } else if (strcmp(command, "attack") == 0) {
        if (arg == 0) {
            attron(COLOR_PAIR(2));
            printw("The Demon attacks!");
            attroff(COLOR_PAIR(2));
        } else if (arg == 1) {
            attron(COLOR_PAIR(2));
            printw("The Fire Breathing Monster scorches you with a blast of flames!");
            attroff(COLOR_PAIR(2));
        } else if (arg == 2) {
            attron(COLOR_PAIR(2));
            printw("The Giant swings it's fist at you!");
            attroff(COLOR_PAIR(2));
        } else if (arg == 3) {
            attron(COLOR_PAIR(2));
            printw("The Snake hisses and attacks!");
            attroff(COLOR_PAIR(2));
        } else if (arg == 4) {
            attron(COLOR_PAIR(2));
            printw("The Undead damages you greatly!");
            attroff(COLOR_PAIR(2));
        }
    } else if (strcmp(command, "monster dead") == 0) {
        int type = monsters[arg].num;
        if (type == 0) {
            attron(COLOR_PAIR(9));
            printw("You beated the Demon!");
            attroff(COLOR_PAIR(9));
            score += 100;
        } else if (type == 1) {
            attron(COLOR_PAIR(9));
            printw("Fire Fire !!! No more Fire breathe monster");
            attroff(COLOR_PAIR(9));
            score += 200;
        } else if (type == 2) {
            attron(COLOR_PAIR(9));
            printw("You defeated the monster Giant!");
            attroff(COLOR_PAIR(9));
            score += 300;
        } else if (type == 3) {
            attron(COLOR_PAIR(9));
            printw("Snake no Snake!");
            score += 400;
            attroff(COLOR_PAIR(9));
        } else if (type == 4) {
            attron(COLOR_PAIR(9));
            printw("The Undeed collapses into a pile of bones!");
            attroff(COLOR_PAIR(9));
            score += 600;
        }
    } else if (strcmp(command, "player attack") == 0) {
        int type = monsters[arg].num;
        if (type == 0) {
            attron(COLOR_PAIR(9));
            printw("You attacked The Demon! (%d%% remaining)",
                   monsters[arg].health * 100 / monsters[arg].max_health);
            attroff(COLOR_PAIR(9));
        } else if (type == 1) {
            attron(COLOR_PAIR(9));
            printw("You hit the Fire Breathing Monster! (%d%% remaining)",
                   monsters[arg].health * 100 / monsters[arg].max_health);
            attroff(COLOR_PAIR(9));
        } else if (type == 2) {
            attron(COLOR_PAIR(9));
            printw("You do a great number on The Giant! (%d%% remaining)",
                   monsters[arg].health * 100 / monsters[arg].max_health);
            attroff(COLOR_PAIR(9));
        } else if (type == 3) {
            attron(COLOR_PAIR(9));
            printw("You attacked the Snake! (%d%% remaining)",
                   monsters[arg].health * 100 / monsters[arg].max_health);
            attroff(COLOR_PAIR(9));
        } else if (type == 4) {
            attron(COLOR_PAIR(9));
            printw("You attacked the Undeed! (%d%% remaining)",
                   monsters[arg].health * 100 / monsters[arg].max_health);
            attroff(COLOR_PAIR(9));
        }
    } else if (strcmp(command, "low health") == 0) {
        attron(COLOR_PAIR(9));
        printw("Your vision's blurry. Eat something!");
        attroff(COLOR_PAIR(9));
    } else if (strcmp(command, "no monster") == 0) {
        printw("There are no monsters around you.");
    } else if (strcmp(command, "no weapon") == 0) {
        printw("You're not carrying any weapon!");
    } else if (strcmp(command, "weapon drop") == 0) {
        char weapon[20];
        if (arg == 0) strcpy(weapon, "Dagger");
        else if (arg == 1) strcpy(weapon, "Magic Wand");
        else strcpy(weapon, "Normal Arrow");
        attron(COLOR_PAIR(2));
        printw("You dropped the %s!", weapon);
        attroff(COLOR_PAIR(2));
    } else if (strcmp(command, "monster frozen") == 0) {
        char name[30];
        if (monsters[arg].type == 'D') strcpy(name, "Demon");
        else if (monsters[arg].type == 'F') strcpy(name, "Fire Breathing Monster");
        else if (monsters[arg].type == 'G') strcpy(name, "Giant");
        else if (monsters[arg].type == 'S') strcpy(name, "Snake");
        else if (monsters[arg].type == 'U') strcpy(name, "Undeed");
        attron(COLOR_PAIR(2));
        printw("Your magic wand paralyzed The %s!", name);
        attroff(COLOR_PAIR(2));
    } else if (strcmp(command, "weapon in bag") == 0) {
        char weapon[20];
        if (arg == 'd') strcpy(weapon, "Dagger");
        else if (arg == '~') strcpy(weapon, "Magic Wand");
        else if (arg == '!') strcpy(weapon, "Sword");
        else if (arg == 'm') strcpy(weapon, "Mace");
        else strcpy(weapon, "Normal Arrow");

        printw("You put the %s in your backpack!", weapon);
    } else if (strcmp(command, "put in bag") == 0) {
        attron(COLOR_PAIR(2));
        mvprintw(0, 0, "You're already carrying a weapon!");
        mvprintw(1, 0, "Put the weapon in your bag!");
        attroff(COLOR_PAIR(2));
    } else if (strcmp(command, "took potion") == 0) {
        char name[30];
        if (arg == 0) strcpy(name, "Healing Salve");
        else if (arg == 1) strcpy(name, "Boot of Travel");
        else if (arg == 2) strcpy(name, "Mask of Madness");
        attron(COLOR_PAIR(9));
        mvprintw(0, 0, "You used %s!", name);
        if (arg == 0) mvprintw(1, 0, "Your health begins to recover!");
        else if (arg == 1) mvprintw(1, 0, "You move like lightning!");
        else mvprintw(1, 0, "Your weapons are now twice as deadly!");
        attroff(COLOR_PAIR(9));
    } else if (strcmp(command, "potion time over") == 0) {
        printw("The talisman's effects begin to wear off!");
    } else if (strcmp(command, "ate spoiled food") == 0) {
        attron(COLOR_PAIR(2));
        printw("The food was spoiled. You feel sick...");
        attroff(COLOR_PAIR(2));
    } else if (strcmp(command, "no long range weapon") == 0) {
        attron(COLOR_PAIR(2));
        printw("Select a direction first!");
        attroff(COLOR_PAIR(2));
    } else if (strcmp(command, "password") == 0) {
        attron(COLOR_PAIR(4));
        printw("You special passkey is here (Use it to open doors): %d", arg);
        attroff(COLOR_PAIR(4));
    }
    printw("                                                 ");
    refresh();
    getch();
}

void init_map() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            map[i][j] = ' ';
            visible[i][j] = false;
        }
    }
}

bool room_overlap(struct ROOM r1, struct ROOM r2) {
    return !(r1.x + r1.width < r2.x || r1.x > r2.x + r2.width || r1.y + r1.height < r2.y || r1.y > r2.y + r2.height);
}

void add_room(struct ROOM room) {
    for (int y = room.y; y < room.y + room.height; y++) {
        for (int x = room.x; x < room.x + room.width; x++) {
            if (y == room.y || y == room.y + room.height - 1) {
                map[y][x] = '-';
            } else if (x == room.x || x == room.x + room.width - 1) {
                map[y][x] = '|';
            } else {
                map[y][x] = '.';
            }
        }
    }
}

void add_pillar(struct ROOM room) {
    int pillar_count = 0;

    for (int y = room.y; y < room.y + room.height; y++) {
        if (pillar_count >= MAX_PILLAR) break;
        for (int x = room.x; x < room.x + room.width; x++) {
            if (pillar_count >= MAX_PILLAR) break;
            if (rand() % 30 == 0 && map[y][x] == '.' && (
                    map[y][x + 1] != '+' && map[y][x - 1] != '+' && map[y + 1][x] != '+' && map[y - 1][x] != '+')) {
                map[y][x] = 'O';
                pillar_count++;
            }
        }
    }
}

void add_trap(struct ROOM room) {
    int type = room.type;
    int prob, max;
    if (type == 2) {
        prob = 5;
        max = 15;
    } else {
        prob = 50;
        max = 3;
    }
    for (int y = room.y; y < room.y + room.height; y++) {
        if (traps_count >= max) break;
        for (int x = room.x; x < room.x + room.width; x++) {
            if (traps_count >= max) break;
            if (rand() % prob == 0 && map[y][x] == '.') {
                traps[traps_count].x = x;
                traps[traps_count].y = y;
                traps[traps_count].state = 0;
                traps_count++;
            }
        }
    }
}

void add_stairs(struct ROOM room) {
    bool stairs_placed = false;
    for (int y = room.y; y < room.y + room.height; y++) {
        if (stairs_placed) return;
        for (int x = room.x; x < room.x + room.width; x++) {
            if (stairs_placed) return;
            if (rand() % 20 == 0 && map[y][x] == '.') {
                attron(COLOR_PAIR(9));
                map[y][x] = '<';
                attroff(COLOR_PAIR(9));
                stairs_placed = true;
                refresh();
            }
        }
    }

    if (!stairs_placed) {
        int center_x = room.x + room.width / 2;
        int center_y = room.y + room.height / 2;
        map[center_y][center_x] = '<';
    }
}

char *get_food_name(int color) {
    char *name[] = {
        "Glowberry",
        "Slightly Moldy Cheese", "Emberfruit", "Mystic Mushroom", "Moonflower Nectar", "Shadow Apple",
        "Golden Loaf", "Dragon Pepper", "Ethereal Jelly"
    };
    if (color == 5) {
        int which = rand() % 3;
        return name[which];
    } else if (color == 2) {
        int which = 3 + rand() % 3;
        return name[which];
    } else {
        int which = 6 + rand() % 3;
        return name[which];
    }
}

void add_food(struct ROOM room) {
    for (int y = room.y; y < room.y + room.height; y++) {
        for (int x = room.x; x < room.x + room.width; x++) {
            if (rand() % 50 == 0 && map[y][x] == '.') {
                int color = rand() % 3;
                if (color == 0) {
                    color = 5;
                    foods[food_count].fresh = 1;
                } else if (color == 1) {
                    color = 2;
                    foods[food_count].fresh = 0;
                } else {
                    color = 6;
                    foods[food_count].fresh = 1;
                }
                foods[food_count].color = color;
                map[y][x] = '%';
                foods[food_count].x = x;
                foods[food_count].y = y;
                foods[food_count].name = get_food_name(color);
                foods[food_count].state = -1;
                food_count++;
            }
        }
    }
}

void add_gold(struct ROOM room) {
    for (int y = room.y; y < room.y + room.height; y++) {
        for (int x = room.x; x < room.x + room.width; x++) {
            if (rand() % 50 == 0 && map[y][x] == '.') {
                int color = rand() % 10;
                if ((color % 3) == 0) {
                    color = 3;
                } else {
                    color = 5;
                }
                golds[gold_count].type = color;
                map[y][x] = '$';
                golds[gold_count].x = x;
                golds[gold_count].y = y;
                golds[gold_count].state = -1;
                gold_count++;
            }
        }
    }
}

void add_weapon(struct ROOM room) {
    for (int y = room.y; y < room.y + room.height; y++) {
        for (int x = room.x; x < room.x + room.width; x++) {
            if (rand() % 50 == 0 && map[y][x] == '.') {
                int type = rand() % 4;
                char symbol;
                int num;
                if (type == 0) {
                    symbol = 'd';
                    num = 10;
                } else if (type == 1) {
                    symbol = '~';
                    num = 8;
                } else if (type == 2) {
                    symbol = 'a';
                    num = 20;
                } else {
                    symbol = '!';
                    num = 1;
                }
                if (weapon_count == 0) {
                    symbol = 'm';
                    num = 1;
                }
                weapons[weapon_count].symbol = symbol;
                if (weapon_count) map[y][x] = symbol;
                weapons[weapon_count].x = x;
                weapons[weapon_count].y = y;
                weapons[weapon_count].state = -1;
                weapons[weapon_count].num_collect = num;
                weapon_count++;
            }
        }
    }
    if (level == 1) {
        weapon_in_hand = &weapons[0];
    }
}

void add_talisman(struct ROOM room) {
    int prob;
    int type = room.type;
    if (type == 1) prob = 10;
    else prob = 50;
    for (int y = room.y; y < room.y + room.height; y++) {
        for (int x = room.x; x < room.x + room.width; x++) {
            if (rand() % prob == 0 && map[y][x] == '.') {
                int talisman_type = rand() % 3;

                map[y][x] = 'p';
                talismans[talisman_count].x = x;
                talismans[talisman_count].y = y;
                talismans[talisman_count].type = talisman_type;
                talismans[talisman_count].state = -1;
                talisman_count++;
            }
        }
    }
}

void add_monster(struct ROOM room) {
    int prob;
    if (level == 1) prob = difficulty_coefficient * 50;
    else if (level == 2) prob = difficulty_coefficient * 30;
    else if (level == 3) prob = difficulty_coefficient * 25;
    else prob = difficulty_coefficient * 20;

    for (int y = room.y; y < room.y + room.height; y++) {
        for (int x = room.x; x < room.x + room.width; x++) {
            int type = rand() % 10;
            char symbol = 'D';
            if (type == 0 || type == 2 || type == 3) {
                symbol = 'D'; //D
                monsters[monster_count].health = 5;
                monsters[monster_count].max_health = 5;
                monsters[monster_count].num = 0;
            } else if (type == 4 || type == 5) {
                symbol = 'F'; //F
                monsters[monster_count].health = 10;
                monsters[monster_count].max_health = 10;
                monsters[monster_count].num = 1;
            } else if (type == 6 || type == 7) {
                symbol = 'G'; //G
                monsters[monster_count].health = 15;
                monsters[monster_count].max_health = 15;
                monsters[monster_count].num = 2;
            } else if (type == 8) {
                symbol = 'S'; //S
                monsters[monster_count].health = 20;
                monsters[monster_count].max_health = 20;
                monsters[monster_count].num = 3;
            } else if (type == 9) {
                symbol = 'U'; //U
                monsters[monster_count].health = 30;
                monsters[monster_count].max_health = 30;
                monsters[monster_count].num = 4;
            }
            if (rand() % prob == 0 && map[y][x] == '.') {
                monsters[monster_count].level = level;
                monsters[monster_count].x = x;
                monsters[monster_count].y = y;
                monsters[monster_count].type = symbol;
                map[y][x] = symbol;
                monsters[monster_count].state = 0;
                monsters[monster_count].movement_num = 0;
                monsters[monster_count].movement_state = 0;
                monster_count++;
            }
        }
    }
}

void corridor(int x1, int y1, int x2, int y2) {
    if (x1 < 2) x1 = 2;
    if (y1 < 2) y1 = 2;
    if (x2 < 2) x2 = 2;
    if (y2 < 2) y2 = 2;

    if (rand() % 2) {
        while (x1 != x2) {
            if ((map[y1][x1] == '|' || map[y1][x1] == '-')) {
                map[y1][x1] = '+';
            } else if (map[y1][x1] == ' ') {
                map[y1][x1] = '#';
            }
            x1 += (x2 > x1) ? 1 : -1;
        }

        while (y1 != y2) {
            if ((map[y1][x1] == '|' || map[y1][x1] == '-')) {
                map[y1][x1] = '+';
            } else if (map[y1][x1] == ' ') {
                map[y1][x1] = '#';
            }
            y1 += (y2 > y1) ? 1 : -1;
        }
    } else {
        bool door_placed = false;
        while (y1 != y2) {
            if (!door_placed || (map[y1][x1] == '|' || map[y1][x1] == '-')) {
                map[y1][x1] = '+';
                door_placed = true;
            } else if (map[y1][x1] == ' ') {
                map[y1][x1] = '#';
            }
            y1 += (y2 > y1) ? 1 : -1;
        }

        while (x1 != x2) {
            if (!door_placed || (map[y1][x1] == '|' || map[y1][x1] == '-')) {
                map[y1][x1] = '+';
                door_placed = true;
            } else if (map[y1][x1] == ' ') {
                map[y1][x1] = '#';
            }
            x1 += (x2 > x1) ? 1 : -1;
        }
    }
}

void add_hidden_door(struct ROOM room) {
    for (int y = room.y; y < room.y + room.height; y++) {
        if (map[y][room.x] == '+') {
            hidden_doors[secret_door_count].x = room.x;
            hidden_doors[secret_door_count].y = y;
            hidden_doors[secret_door_count].state = 0;
            secret_door_count++;
            attron(COLOR_PAIR(5));
            map[y][room.x] = '|';
            attroff(COLOR_PAIR(5));
            refresh();
        }
    }
    for (int y = room.y; y < room.y + room.height; y++) {
        if (map[y][room.x + room.width - 1] == '+') {
            hidden_doors[secret_door_count].x = room.x + room.width - 1;
            hidden_doors[secret_door_count].y = y;
            hidden_doors[secret_door_count].state = 0;
            secret_door_count++;
            attron(COLOR_PAIR(5));
            map[y][room.x + room.width - 1] = '|';
            attroff(COLOR_PAIR(5));
            refresh();
        }
    }

    for (int x = room.x; x < room.x + room.width; x++) {
        if (map[room.y][x] == '+') {
            hidden_doors[secret_door_count].x = x;
            hidden_doors[secret_door_count].y = room.y;
            hidden_doors[secret_door_count].state = 0;
            secret_door_count++;
            attron(COLOR_PAIR(5));
            map[room.y][x] = '-';
            attroff(COLOR_PAIR(5));
            refresh();
        }
    }

    for (int x = room.x; x < room.x + room.width; x++) {
        if (map[room.y + room.height - 1][x] == '+') {
            hidden_doors[secret_door_count].x = x;
            hidden_doors[secret_door_count].y = room.y + room.height - 1;
            hidden_doors[secret_door_count].state = 0;
            secret_door_count++;
            attron(COLOR_PAIR(5));
            map[room.y + room.height - 1][x] = '-';
            attroff(COLOR_PAIR(5));
            refresh();
        }
    }
}

void add_treasure(struct ROOM room) {
    bool treasure = false;
    for (int y = room.y; y < room.y + room.height; y++) {
        if (treasure) return;
        for (int x = room.x; x < room.x + room.width; x++) {
            if (treasure) return;
            if (rand() % 20 == 0 && map[y][x] == '.') {
                attron(COLOR_PAIR(9));
                map[y][x] = 'T';
                attroff(COLOR_PAIR(9));
                treasure = true;
                refresh();
            }
        }
    }

    if (!treasure) {
        int center_x = room.x + room.width / 2;
        int center_y = room.y + room.height / 2;
        map[center_y][center_x] = 'T';
    }
}

void add_master_key(struct ROOM room) {
    bool key_placed = false;
    for (int y = room.y; y < room.y + room.height; y++) {
        if (key_placed) break;
        for (int x = room.x; x < room.x + room.width; x++) {
            if (key_placed) break;
            if (rand() % 20 == 0 && map[y][x] == '.') {
                map[y][x] = '*';
                key_placed = true;
            }
        }
    }

    if (!key_placed) {
        int center_x = room.x + room.width / 3;
        int center_y = room.y + room.height / 3;
        map[center_y][center_x] = '*';
    }
}

void locked_door(struct ROOM room) {
    int door_x[100], door_y[100];
    for (int y = room.y; y < room.y + room.height; y++) {
        if (map[y][room.x] == '+' || map[y][room.x] == '?') {
            locked[locked_door_count].x = room.x;
            locked[locked_door_count].y = y;
            locked[locked_door_count].state = 0;
            locked_door_count++;
            attron(COLOR_PAIR(2));
            map[y][room.x] = '@';
            attroff(COLOR_PAIR(2));
        }
    }

    for (int y = room.y; y < room.y + room.height; y++) {
        if (map[y][room.x + room.width - 1] == '+' || map[y][room.x + room.width - 1] == '?') {
            locked[locked_door_count].x = room.x + room.width - 1;
            locked[locked_door_count].y = y;
            locked[locked_door_count].state = 0;
            locked_door_count++;
            attron(COLOR_PAIR(2));
            map[y][room.x + room.width - 1] = '@';
            attroff(COLOR_PAIR(2));
            //refresh();
        }
    }

    for (int x = room.x; x < room.x + room.width; x++) {
        if (map[room.y][x] == '+' || map[room.y][x] == '?') {
            locked[locked_door_count].x = x;
            locked[locked_door_count].y = room.y;
            locked[locked_door_count].state = 0;
            locked_door_count++;
            attron(COLOR_PAIR(2));
            map[room.y][x] = '@';
            attroff(COLOR_PAIR(2));
            //refresh();
        }
    }

    for (int x = room.x; x < room.x + room.width; x++) {
        if (map[room.y + room.height - 1][x] == '+' || map[room.y + room.height - 1][x] == '?') {
            locked[locked_door_count].x = x;
            locked[locked_door_count].y = room.y + room.height - 1;
            locked[locked_door_count].state = 0;
            locked_door_count++;
            attron(COLOR_PAIR(2));
            map[room.y + room.height - 1][x] = '@';
            attroff(COLOR_PAIR(2));
            //refresh();
        }
    }


    int hint_x, hint_y;
    do {
        hint_x = room.x + 1 + rand() % (room.width - 2);
        hint_y = room.y + 1 + rand() % (room.height - 2);
    } while (map[hint_y][hint_x] != '.');

    attron(COLOR_PAIR(5));
    map[hint_y][hint_x] = '&';
    attroff(COLOR_PAIR(5));
    refresh();
}

int set_color(char tile, int x, int y) {
    if (tile == 'D' || tile == 'F' || tile == 'G' || tile == 'S' || tile == 'U') {
        return 2;
    } else if (tile == '@') {
        for (int j = 0; j < locked_door_count; j++) {
            if (locked[j].x == x && locked[j].y == y) {
                if (locked[j].state == 0) return 2;
                else return 9;
            }
        }
    } else if (tile == '?') {
        for (int k = 0; k < secret_door_count; k++) {
            if (hidden_doors[k].x == x && hidden_doors[k].y == y) {
                if (hidden_doors[k].state == 0) return 10;
                else return 5;
            }
        }
    } else if (tile == '<') {
        return 9;
    } else if (tile == '^') {
        for (int n = 0; n < traps_count; n++) {
            if (traps[n].x == x && traps[n].y == y) {
                if (traps[n].state == 0) return 10;
                else return 6;
            }
        }
    } else if (tile == '%') {
        for (int p = 0; p < food_count; p++) {
            if (foods[p].x == x && foods[p].y == y) {
                return foods[p].color;
            }
        }
    } else if (tile == 'p') {
        return 6;
    } else if (tile == '|' || tile == '-') {
        for (int i = 0; i < room_count[level]; i++) {
            if ((x >= rooms[level][i].x && x <= rooms[level][i].x + rooms[level][i].width) && (
                    y >= rooms[level][i].y && y <= rooms[level][i].y + rooms[level][i].height)) {
                if (rooms[level][i].type == 2) return 5;
                else if (rooms[level][i].type == 1) return 6;
                else return 10;
            }
        }
    } else if (tile == '$') {
        for (int m = 0; m < gold_count; m++) {
            if (golds[m].x == x && golds[m].y == y) {
                return golds[m].type;
            }
        }
    } else if (tile == 'T') {
        return 5;
    } else if (map[y][x] == 'm' || map[y][x] == 'd' || map[y][x] == '~' || map[y][x] ==
               'a' || map[y][x] == '!') {
        return 4;
    } else if (tile == '&') return 5;
    else if (tile == '*') return 5;
    return 10;
}

void render_map() {
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            if (visible[j][i]) {
                // wchar_t display_char = determine_char(map[j][i]);
                int color = set_color(map[j][i], i, j);
                attron(COLOR_PAIR(color));
                mvaddch(j, i, map[j][i]);
                attroff(COLOR_PAIR(color));
            } else {
                mvaddch(j, i, ' ');
            }
        }
    }
    refresh();
}

void health_bar(int health) {
    if (health > 100) health = 100;
    int filled = (health * 20) / MAX_HEALTH;
    move(LINES - 1, COLS - 20 - 10);
    addch('[');
    for (int i = 0; i < 20; i++) {
        if (i < filled) {
            attron(COLOR_PAIR(9));
            addch('=');
            attroff(COLOR_PAIR(9));
            refresh();
        } else {
            attron(COLOR_PAIR(9));
            addch(' ');
            attroff(COLOR_PAIR(9));
            refresh();
        }
    }
    addch(']');
    mvprintw(LINES - 1, COLS - 39, "Health: ");
    mvprintw(LINES - 1, COLS - 8, "%d %% ", (health * 100) / MAX_HEALTH);
    refresh();
}

void hunger_bar(int hunger) {
    if (hunger > 100) hunger = 100;

    int filled = (hunger * 20) / MAX_HEALTH;
    move(LINES - 1, COLS - 20 - 10 - 56 - 30);
    addch('[');
    for (int i = 0; i < 20; i++) {
        if (i < filled) {
            attron(COLOR_PAIR(2));
            addch('=');
            attroff(COLOR_PAIR(2));
            //refresh();
        } else {
            attron(COLOR_PAIR(2));
            addch(' ');
            attroff(COLOR_PAIR(2));
            //refresh();
        }
    }
    addch(']');
    char state[10];
    mvprintw(LINES - 1, COLS - 39 - 56 - 30, "Hunger: ");
    if (hunger <= 100 && hunger > 80) strcpy(state, " Full");
    else if (hunger <= 80 && hunger > 60) strcpy(state, " Good");
    else if (hunger <= 60 && hunger > 40) strcpy(state, " Hungry");
    else if (hunger <= 40 && hunger > 20) strcpy(state, " Starving");
    else if (hunger <= 20 && hunger > 0) strcpy(state, " Dying");

    mvprintw(LINES - 1, COLS - 8 - 56 - 30, "%s", state);
    refresh();
}

void lose_health(int value) {
    health -= value;
    health_bar(health);
}

void hunger_update() {
    time_t current_time;
    time(&current_time);

    if (difftime(current_time, last_hunger_update) >= HEALTH_TIME) {
        hunger -= HUNGER_R;

        if (hunger < 0) {
            hunger = 0;
        }
        last_hunger_update = current_time;
    }
}

void health_update(int double_speed) {
    time_t current_time;
    time(&current_time);

    if (difftime(current_time, last_health_update) >= HEALTH_TIME && hunger >= 80) {
        int speed = 1;
        if (double_speed && talisman_time_track) speed = 2;
        health += speed * HEALTH_R;

        if (health < 0) {
            health = 0;
        }
        last_health_update = current_time;
    } else if (difftime(current_time, last_health_update) >= HEALTH_TIME && hunger < 80) {
        health -= HEALTH_R;

        if (health < 0) {
            health = 0;
        }
        last_health_update = current_time;
    }
}

void reveal_room(struct ROOM room) {
    for (int y = room.y; y < room.y + room.height; y++) {
        for (int x = room.x; x < room.x + room.width; x++) {
            visible[y][x] = true;
        }
    }
    if (room.type != 0) alert("enter room", room.type);
}

void reveal_corridor(int px, int py) {
    for (int dy = -CORRIDOR_VISIBLE; dy <= CORRIDOR_VISIBLE; dy++) {
        for (int dx = -CORRIDOR_VISIBLE; dx <= CORRIDOR_VISIBLE; dx++) {
            int nx = dx + px;
            int ny = dy + py;
            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT) {
                if (map[ny][nx] == '#' || map[ny][nx] == '+') {
                    visible[ny][nx] = true;
                }
            }
        }
    }
}

void reveal_door(int ny, int nx) {
    int which_door = -1;
    for (int i = 0; i < secret_door_count; i++) {
        if (hidden_doors[i].x == nx && hidden_doors[i].y == ny) {
            which_door = i;
            hidden_doors[i].state = 1;
        }
    }
    if (which_door != -1 && hidden_doors[which_door].state) {
        attron(COLOR_PAIR(2));
        map[ny][nx] = '?';
        attroff(COLOR_PAIR(2));
        refresh();
    }
    render_map();
}

void reveal_trap(int ny, int nx) {
    int which_trap = 0;
    for (int i = 0; i < traps_count; i++) {
        if (traps[i].x == nx && traps[i].y == ny) {
            which_trap = i;
            traps[i].state = 1;
        }
    }

    if (traps[which_trap].state) {
        attron(COLOR_PAIR(2));
        map[ny][nx] = '^';
        attroff(COLOR_PAIR(2));
        refresh();
    }

    lose_health(5);
}

void player_in_room(int px, int py, struct ROOM rooms[], int room_count) {
    for (int i = 0; i < room_count; i++) {
        struct ROOM room = rooms[i];
        if (px >= room.x && px < room.x + room.width &&
            py >= room.y && py < room.y + room.height) {
            reveal_room(room);
        }
    }
    reveal_corridor(px, py);
}

void init_colors() {
    init_pair(9, COLOR_GREEN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_RED);
    init_pair(10, COLOR_WHITE, COLOR_BLACK);
    init_pair(11, COLOR_BLACK, COLOR_YELLOW);
    init_pair(12, COLOR_BLACK, COLOR_GREEN);


    init_pair(21, COLOR_WHITE, COLOR_BLACK);
    init_pair(22, COLOR_BLUE, COLOR_BLACK);
    init_pair(23, COLOR_GREEN, COLOR_BLACK);
    init_pair(24, COLOR_YELLOW, COLOR_BLACK);
    init_pair(25, COLOR_MAGENTA, COLOR_BLACK);
}

void spoil_food() {
    for (int j = 0; j < food_count; j++) {
        if (foods[j].fresh == 1 && foods[j].state == 0) foods[j].fresh = 0; //turn to normal
        else if (foods[j].fresh == 0 && foods[j].state == 0) foods[j].fresh = -1; //rotten
    }
    food_time_out = 50;
}

void reveal_whole_map() {
    for (int j = 0; j < HEIGHT; j++) {
        for (int i = 0; i < WIDTH; i++) {
            int color = set_color(map[j][i], i, j);
            attron(COLOR_PAIR(color));
            mvaddch(j, i, map[j][i]);
            attroff(COLOR_PAIR(color));
        }
    }
    refresh();
    alert("cheat code M", 0);
    getch();
}

void search_around(int ny, int nx) {
    bool trap = false;
    int trap_num = 0;
    bool secret_door = false;
    int door_num = 0;
    for (int j = ny - 1; j <= ny + 1; j++) {
        for (int i = nx - 1; i <= nx + 1; i++) {
            if (i != nx || j != ny) {
                if (map[j][i] == '?') {
                    secret_door = true;
                    door_num++;
                } else if (map[j][i] == '^') {
                    trap = true;
                    trap_num++;
                }
            }
        }
    }

    if (trap) alert("trap around", trap_num);
    if (secret_door) alert("secret door around", door_num);
}

void healing_salve() {
    health += 15;

    health_bar(health);
}

void mask_of_madness() {
    weapon_rate = 2;
    talisman_time_track = 10;
}

void boot_of_travel() {
    num_of_blocks = 2;
    talisman_time_track = 10;
}

void talisman_choice(int type) {
    for (int i = 0; i < talisman_count; i++) {
        if (talismans[i].type == type && talismans[i].state == 0) {
            talismans[i].state = 1;
            alert("took potion", type);
            used_talisman = true;
            break;
        }
    }
    if (type == 0) healing_salve();
    else if (type == 1) boot_of_travel();
    else mask_of_madness();
    talisman_time_track = 10;
}

void talisman_window() {
    int height = 12, width = 40;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

    WINDOW *potion = newwin(height, width, start_y, start_x);
    wclear(potion);
    box(potion, 0, 0);

    int len = strlen("** TALISMANS **");
    mvwprintw(potion, 1, (width - len) / 2, "** TALISMANS **");

    int salve = 0, madness = 0, boot = 0;
    for (int i = 0; i < talisman_count; i++) {
        if (talismans[i].type == 0 && talismans[i].state == 0) salve++;
        if (talismans[i].type == 1 && talismans[i].state == 0) madness++;
        if (talismans[i].type == 2 && talismans[i].state == 0) boot++;
    }

    int salve_id = 0, madness_id = 0, boot_id = 0;
    int identifier = 1;
    if (salve != 0) {
        mvwprintw(potion, identifier + 1, 1, "%d. %d Healing Salve", identifier, salve);
        salve_id = identifier++;
    }
    if (madness != 0) {
        mvwprintw(potion, identifier + 1, 1, "%d. %d Mask of Madness", identifier, madness);
        madness_id = identifier++;
    }
    if (boot != 0) {
        mvwprintw(potion, identifier + 1, 1, "%d. %d Boot of Travel", identifier, boot);
        boot_id = identifier++;
    }
    if (salve == 0 && madness == 0 && boot == 0) {
        char text[] = "You don't have any talismans to use!";
        int x = (width - strlen(text)) / 2;
        mvwprintw(potion, 4, x, "%s", text);
    }

    wrefresh(potion);
    int choice = wgetch(potion) - '0';

    if (choice == salve_id) talisman_choice(0);
    else if (choice == madness_id) talisman_choice(2);
    else if (choice == boot_id) talisman_choice(1);
    wclear(potion);
    delwin(potion);
}

void food_choice(char *name) {
    for (int i = 0; i < food_count; i++) {
        if (strcmp(foods[i].name, name) == 0 && foods[i].state == 0) {
            if (foods[i].fresh == 0 || foods[i].fresh == 1) {
                int type = 0;
                if (foods[i].fresh == 1 && foods[i].color == 5) {
                    mask_of_madness();
                    type = 1;
                } else if (foods[i].fresh == 1 && foods[i].color == 6) {
                    boot_of_travel();
                    type = 2;
                    used_magic_food = true;
                }
                foods[i].state = 1;
                health += 5;
                hunger += 5;
                health_bar(health);
                hunger_bar(hunger);
                alert("ate food", type);
                break;
            } else {
                foods[i].state = 1;
                health -= 5;
                hunger -= 5;
                health_bar(health);
                hunger_bar(hunger);
                alert("ate spoiled food", 0);
                break;
            }
        }
    }
    food_time_out = 50;
}

void food_window() {
    int win_h = 10, win_w = 50;
    int start_y = (LINES - win_h) / 2;
    int start_x = (COLS - win_w) / 2;

    WINDOW *food = newwin(win_h, win_w, start_y, start_x);
    wclear(food);
    box(food, 0, 0);

    int ex_berry = 0, eth_berry = 0, pie = 0, amb = 0, cheese = 0, biscuit = 0, steak = 0, apple = 0, meat = 0;
    for (int i = 0; i < food_count; i++) {
        if (strcmp(foods[i].name, "Glowberry") == 0 && foods[i].state == 0) ex_berry++;
        else if (strcmp(foods[i].name, "Slightly Moldy Cheese") == 0 && foods[i].state == 0) eth_berry++;
        else if (strcmp(foods[i].name, "Emberfruit") == 0 && foods[i].state == 0) pie++;
        else if (strcmp(foods[i].name, "Mystic Mushroom") == 0 && foods[i].state == 0) amb++;
        else if (strcmp(foods[i].name, "Moonflower Nectar") == 0 && foods[i].state == 0) cheese++;
        else if (strcmp(foods[i].name, "Shadow Apple") == 0 && foods[i].state == 0) biscuit++;
        else if (strcmp(foods[i].name, "Shadow Apple") == 0 && foods[i].state == 0) steak++;
        else if (strcmp(foods[i].name, "Dragon Pepper") == 0 && foods[i].state == 0) meat++;
        else if (strcmp(foods[i].name, "Ethereal Jelly") == 0 && foods[i].state == 0) apple++;
    }
    wattron(food, COLOR_PAIR(6));
    int len = strlen("** FOOD **");
    mvwprintw(food, 1, (win_w - len) / 2, "** FOOD **");
    wattroff(food, COLOR_PAIR(6));

    int ex_berry_id = 0, eth_berry_id = 0, pie_id = 0, amb_id = 0, cheese_id = 0, biscuit_id = 0, steak_id = 0, apple_id
            = 0, meat_id = 0;
    int identifier = 1;
    if (ex_berry != 0) {
        mvwprintw(food, identifier + 1, 1, "%d. %d Glowberry", identifier, ex_berry);
        ex_berry_id = identifier;
        identifier++;
    }
    if (eth_berry != 0) {
        mvwprintw(food, identifier + 1, 1, "%d. %d Slightly Moldy Cheese", identifier, eth_berry);
        eth_berry_id = identifier;
        identifier++;
    }
    if (pie != 0) {
        mvwprintw(food, identifier + 1, 1, "%d. %d Emberfruit", identifier, pie);
        pie_id = identifier;
        identifier++;
    }
    if (amb != 0) {
        mvwprintw(food, identifier + 1, 1, "%d. %d Mystic Mushroom", identifier, amb);
        amb_id = identifier;
        identifier++;
    }
    if (cheese != 0) {
        mvwprintw(food, identifier + 1, 1, "%d. %d Moonflower Nectar", identifier, cheese);
        cheese_id = identifier;
        identifier++;
    }
    if (biscuit != 0) {
        mvwprintw(food, identifier + 1, 1, "%d. %d Shadow Apple", identifier, biscuit);
        biscuit_id = identifier;
        identifier++;
    }
    if (steak != 0) {
        mvwprintw(food, identifier + 1, 1, "%d. %d Golden Loaf", identifier, steak);
        steak_id = identifier;
        identifier++;
    }
    if (apple != 0) {
        mvwprintw(food, identifier + 1, 1, "%d. %d Dragon Pepper", identifier, apple);
        apple_id = identifier;
        identifier++;
    }
    if (meat != 0) {
        mvwprintw(food, identifier + 1, 1, "%d. %d Ethereal Jelly", identifier, meat);
        meat_id = identifier;
        identifier++;
    }

    if (ex_berry == 0 && eth_berry == 0 && pie == 0 && amb == 0 && cheese == 0 && biscuit == 0 && steak == 0 && apple ==
        0 && meat == 0) {
        char text[50] = "You don't have any food to consume!";
        int x = (win_w - strlen(text)) / 2;
        mvwprintw(food, 4, x, "%s", text);
    }

    wrefresh(food);

    int choice = getch();
    choice = choice - '0';
    if (choice == ex_berry_id) food_choice("Glowberry");
    else if (choice == eth_berry_id) food_choice("Slightly Moldy Cheese");
    else if (choice == pie_id) food_choice("Emberfruit");
    else if (choice == amb_id) food_choice("Mystic Mushroom");
    else if (choice == cheese_id) food_choice("Moonflower Nectar");
    else if (choice == biscuit_id) food_choice("Shadow Apple");
    else if (choice == steak_id) food_choice("Shadow Apple");
    else if (choice == meat_id) food_choice("Dragon Pepper");
    else if (choice == apple_id) food_choice("Ethereal Jelly");

    if (choice == 'q') return;
}

void quick_eat() {
    mvprintw(0, 0, "What food would you like to eat? (press * for the list)");
    refresh();
    getch();
    food_window();
}

void quick_talisman_use() {
    mvprintw(0, 0, "What potion would you like to drink? (press * for the list)");
    refresh();
    getch();
    talisman_window();
}

void weapon_in_backpack() {
    weapon_in_hand->state = 0;
    wield_choice = '0';
}

void weapon_choice(char symbol) {
    if (weapon_in_hand->symbol == symbol) return;

    weapon_in_backpack();

    for (int i = 0; i < weapon_count; i++) {
        if (weapons[i].symbol == symbol && weapons[i].state == 0) {
            weapons[i].state = 1;
            weapon_in_hand = &weapons[i];
            wield_choice = symbol;
            break;
        }
    }
}

void weapon_window() {
    int win_height = 12, win_width = 50;
    int start_y = (LINES - win_height) / 2;
    int start_x = (COLS - win_width) / 2;

    WINDOW *arsenal = newwin(win_height, win_width, start_y, start_x);
    wclear(arsenal);
    box(arsenal, 0, 0);

    int len = strlen("** ARSENAL **");
    mvwprintw(arsenal, 1, (win_width - len) / 2, "** ARSENAL **");

    for (int i = 2; i < win_height - 1; i++) {
        mvwaddch(arsenal, i, 24, '|');
    }

    int dag = 0, wand = 0, arrow = 0, sword = 0;
    for (int i = 0; i < weapon_count; i++) {
        if (weapons[i].symbol == 'd' && weapons[i].state != -1) dag += weapons[i].num_collect;
        if (weapons[i].symbol == '~' && weapons[i].state != -1) wand += weapons[i].num_collect;
        if (weapons[i].symbol == 'a' && weapons[i].state != -1) arrow += weapons[i].num_collect;
        if (weapons[i].symbol == '!' && weapons[i].state != -1) sword += weapons[i].num_collect;
        // if (weapons[i].symbol == 'm' && weapons[i].state != -1) mace += weapons[i].num_collect;
    }

    int identifier = 1;
    int short_y = 3, long_y = 3;

    mvwprintw(arsenal, short_y, 5, "Melee Weapons:");
    mvwprintw(arsenal, long_y, 30, "Ranged Weapons:");

    short_y += 2;
    long_y += 2;
    //int color = 10;

    int mac_id = 0, dag_id = 0, wand_id = 0, arrow_id = 0, sword_id = 0;

    if (1) {
        int color = 10;
        if ('m' == wield_choice) color = 6;
        wattron(arsenal, COLOR_PAIR(color));
        //mac_id = identifier;
        mvwprintw(arsenal, short_y++, 5, "[%c] Mace (%d)", 'm', 1);
        wattroff(arsenal, COLOR_PAIR(color));
        wattron(arsenal, COLOR_PAIR(2));
        mvwprintw(arsenal, short_y++, 5, "damage = 5");
        wattroff(arsenal, COLOR_PAIR(2));
    }
    if (dag > 0) {
        int color = 10;
        if ('d' == wield_choice) color = 6;
        wattron(arsenal, COLOR_PAIR(color));
        //dag_id = identifier;
        mvwprintw(arsenal, long_y++, 30, "[%c] Dagger (%d)", 'd', dag);
        wattroff(arsenal, COLOR_PAIR(color));
        wattron(arsenal, COLOR_PAIR(2));
        mvwprintw(arsenal, long_y++, 30, "distance = 5, damage = 5");
        wattroff(arsenal, COLOR_PAIR(2));
    }
    if (sword > 0) {
        int color = 10;
        if ('!' == wield_choice) color = 6;
        wattron(arsenal, COLOR_PAIR(color));
        //sword_id = identifier;
        mvwprintw(arsenal, short_y++, 5, "[%c] Sword (%d)", '!', sword);
        wattroff(arsenal, COLOR_PAIR(color));
        wattron(arsenal, COLOR_PAIR(2));
        mvwprintw(arsenal, short_y++, 5, "damage = 10");
        wattroff(arsenal, COLOR_PAIR(2));
    }
    if (wand > 0) {
        int color = 10;
        if ('~' == wield_choice) color = 6;
        wattron(arsenal, COLOR_PAIR(color));
        //wand_id = identifier;
        mvwprintw(arsenal, long_y++, 30, "[%c] Magic Wand (%d)", '~', wand);
        wattroff(arsenal, COLOR_PAIR(color));
        wattron(arsenal, COLOR_PAIR(2));
        mvwprintw(arsenal, long_y++, 30, "distance = 10, damage = 12");
        wattroff(arsenal, COLOR_PAIR(2));
    }
    if (arrow > 0) {
        int color = 10;
        if ('a' == wield_choice) color = 6;
        wattron(arsenal, COLOR_PAIR(color));
        //arrow_id = identifier;
        mvwprintw(arsenal, long_y++, 30, "[%c] Normal Arrow (%d)", 'a', arrow);
        wattroff(arsenal, COLOR_PAIR(color));
        wattron(arsenal, COLOR_PAIR(2));
        mvwprintw(arsenal, long_y++, 30, "distance = 5, damage = 5");
        wattroff(arsenal, COLOR_PAIR(2));
    }

    wrefresh(arsenal);

    int choice = wgetch(arsenal);
    if (wield_choice != '0') {
        alert("put in bag", 0);
        wclear(arsenal);
        delwin(arsenal);
        return;
    }
    if (choice == 'm' || choice == 'd' || choice == '!' || choice == '~' || choice ==
        'a') {
        weapon_choice(choice);
        wield_choice = choice;
        alert("took weapon", 0);
    }
    wclear(arsenal);
    delwin(arsenal);
    refresh();
}

void inventory_window() {
    int height = 10, width = 50;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

    WINDOW *inventory = newwin(height, width, start_y, start_x);
    keypad(inventory, TRUE);
    wclear(inventory);
    box(inventory, 0, 0);

    const char *options[] = {"WEAPONS", "FOODS", "TALISMANS"};
    int selected = 0;

    while (1) {
        int num_options = 3;
        wclear(inventory);
        box(inventory, 0, 0);
        mvwprintw(inventory, 1, (width - strlen("** INVENTORY **")) / 2, "** INVENTORY **");

        for (int i = 0, x = 5; i < num_options; i++, x += 15) {
            if (i == selected) {
                wattron(inventory, COLOR_PAIR(4));
                wattron(inventory, A_UNDERLINE);
                mvwprintw(inventory, 6, x, " %s ", options[i]);
                wattroff(inventory, A_UNDERLINE);
                wattroff(inventory, COLOR_PAIR(4));
            } else {
                wattron(inventory, COLOR_PAIR(10));
                mvwprintw(inventory, 6, x, " %s ", options[i]);
                wattroff(inventory, COLOR_PAIR(10));
            }
        }

        wrefresh(inventory);
        int key = wgetch(inventory);

        if (key == KEY_RIGHT) {
            selected = (selected + 1) % num_options;
        } else if (key == KEY_LEFT) {
            selected = (selected - 1 + num_options) % num_options;
        } else if (key == '\n') {
            break;
        } else if (key == 27) {
            wclear(inventory);
            delwin(inventory);
            return;
        }
    }

    wclear(inventory);
    delwin(inventory);

    switch (selected) {
        case 0: {
            weapon_window();
            break;
        }
        case 1: {
            food_window();
            break;
        }
        case 2: {
            talisman_window();
            break;
        }
    }
}

bool is_ranged_weapon(char type) {
    if (type == 'd' ||
        type == 'a' ||
        type == '~') {
        return true;
    }
    return false;
}

void drop_weapon(int x, int y, struct weapon *weapon) {
    weapon->x = x;
    weapon->y = y;
    weapon->state = 0;
    map[y][x] = weapon->symbol;
    weapon->num_collect--;
    if (weapon->num_collect == 0) weapon->state = -1;
}

void monster_health_check(struct monster *monster) {
    if (monster->health <= 0) monster->state = 1;
    else monster->state = 0;
}

void attack(int mx, int my, char type) {
    if (talisman_time_track == 0) weapon_rate = 1;
    int damage = weapon_rate * 5;
    if (type == 'd') damage = weapon_rate * 12;
    else if (type == '~') damage = weapon_rate * 15;
    else if (type == 'a') damage = weapon_rate * 5;
    else if (type == '!') damage = weapon_rate * 10;

    for (int i = 0; i < monster_count; i++) {
        if (monsters[i].state == 0 && monsters[i].level == level && monsters[i].x == mx && monsters[i].y == my) {
            if (type == '~') {
                monsters[i].movement_state = 1;
                alert("monster frozen", i);
            }
            monsters[i].health -= damage;
            alert("player attack", i);
            if (weapon_in_hand->symbol != 'm' && weapon_in_hand->symbol != '!')
                weapon_in_hand->
                        num_collect--;
            monster_health_check(&monsters[i]);
            if (monsters[i].state) {
                map[my][mx] = '.';
                alert("monster dead", i);
                if (weapon_in_hand->num_collect == 0) weapon_in_hand->state = -1;
            }
        }
    }
}

void ranged_attack(int px, int py, const char *direction, int type) {
    int distance;
    char symbol;

    if (type == 0) {
        // Dagger
        distance = 5;
        symbol = 'd';
    } else if (type == 1) {
        // Wand
        distance = 10;
        symbol = '~';
    } else {
        // Arrow
        distance = 5;
        symbol = 'a';
    }

    int dx = 0, dy = 0;

    if (strcmp(direction, "u") == 0) dy = -1;
    else if (strcmp(direction, "d") == 0) dy = +1;
    else if (strcmp(direction, "l") == 0) dx = -1;
    else if (strcmp(direction, "r") == 0) dx = +1;
    else if (strcmp(direction, "ur") == 0) {
        dx = +1;
        dy = -1;
    } else if (strcmp(direction, "ul") == 0) {
        dx = -1;
        dy = -1;
    } else if (strcmp(direction, "dl") == 0) {
        dx = -1;
        dy = +1;
    } else if (strcmp(direction, "dr") == 0) {
        dx = +1;
        dy = +1;
    }

    bool weapon_used = false;

    for (int i = 1; i <= distance; i++) {
        int new_x = px + i * dx;
        int new_y = py + i * dy;

        if (new_x < 0 || new_x >= WIDTH || new_y < 0 || new_y >= HEIGHT) {
            drop_weapon(px + (i - 1) * dx, py + (i - 1) * dy, weapon_in_hand);
            return;
        }

        if (map[new_y][new_x] == '|' || map[new_y][new_x] == '-' || map[new_y][new_x] == '#') {
            drop_weapon(px + (i - 1) * dx, py + (i - 1) * dy, weapon_in_hand);
            return;
        }

        for (int j = 0; j < monster_count; j++) {
            if (monsters[j].x == new_x && monsters[j].y == new_y) {
                attack(monsters[j].x, monsters[j].y, symbol);
                weapon_used = true;
                return;
            }
        }
    }

    if (!weapon_used) {
        drop_weapon(px + distance * dx, py + distance * dy, weapon_in_hand);
    }

    strncpy(last_direction, direction, sizeof(last_direction) - 1);
    last_direction[sizeof(last_direction) - 1] = '\0';

    long_range_weapon = true;
}

struct monster monster_in_room(int px, int py) {
    struct monster monster;
    monster.x = -1;
    monster.y = -1;

    for (int i = 0; i < monster_count; i++) {
        if (monsters[i].state == 0 && monsters[i].level == level && (
                monsters[i].x == px || monsters[i].x == px + 1 || monsters[i].x == px - 1) && (
                monsters[i].y == py || monsters[i].y == py + 1 || monsters[i].y == py - 1)) {
            return monsters[i];
        }
    }
    return monster;
}

int pause_window(int px, int py) {
    int height = 9, width = 45;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

    WINDOW *pause_win = newwin(height, width, start_y, start_x);
    keypad(pause_win, TRUE);
    wclear(pause_win);
    box(pause_win, 0, 0);

    const char *options[] = {"Resume", "Save", "Exit"};
    int selected = 0;

    while (1) {
        int num_options = 3;
        wclear(pause_win);
        box(pause_win, 0, 0);
        mvwprintw(pause_win, 2, (width - strlen("** GAME HAS BEEN PAUSED **")) / 2 + 1, "** GAME HAS BEEN PAUSED **");
        wattron(pause_win, COLOR_PAIR(6));
        mvwprintw(pause_win, 2, (width - 32) / 2, " \\\\\\\\\\_____________________\\\"-._");
        mvwprintw(pause_win, 3, (width - 32) / 2, " /////~~~~~~~~~~~~~~~~~~~~~/.-'");
        wattron(pause_win, COLOR_PAIR(6));

        for (int i = 0, x = 4; i < num_options; i++, x += 16) {
            if (i == selected) {
                wattron(pause_win, COLOR_PAIR(6));
                wattron(pause_win, A_UNDERLINE);
                mvwprintw(pause_win, 6, x, "%s", options[i]);
                wattroff(pause_win, A_UNDERLINE);
                wattroff(pause_win, COLOR_PAIR(6));
            } else {
                wattron(pause_win, COLOR_PAIR(10));
                mvwprintw(pause_win, 6, x, "%s", options[i]);
                wattroff(pause_win, COLOR_PAIR(10));
            }
        }

        wrefresh(pause_win);
        int key = wgetch(pause_win);

        if (key == KEY_RIGHT) {
            selected = (selected + 1) % num_options;
        } else if (key == KEY_LEFT) {
            selected = (selected - 1 + num_options) % num_options;
        } else if (key == '\n') {
            break;
        } else if (key == 27) {
            wclear(pause_win);
            refresh();
            delwin(pause_win);
            refresh();
            return 0;
        }
    }

    wclear(pause_win);
    refresh();
    delwin(pause_win);
    refresh();
    switch (selected) {
        case 0: {

            return 0;
        }
        case 1: {
            clear();
            return 1;
            break;
        }
        case 2: {
            //exit
            return 1;
            break;
        }
        default:
            return 0;
    }
}

int lock_pass_input(int px, int py) {
    int which_door = 0;
    for (int c = 0; c < locked_door_count; c++) {
        if (locked[c].x == px && locked[c].y == py) {
            which_door = c;
        }
    }
    if (locked[which_door].state == 1) return which_door;


    int win_width = 50;
    int win_height = 8;

    int start_x = (COLS - win_width) / 2;
    int start_y = (LINES - win_height) / 2;

    char is_pass[5];
    WINDOW *password_win = newwin(win_height, win_width, start_y, start_x);
    wbkgd(password_win, COLOR_PAIR(2));
    box(password_win, 0, 0);

    echo();
    char msg1[] = "This door needs a passkey";
    int msg1_len = strlen(msg1);
    int start_col1 = (win_width - msg1_len) / 2;

    char msg2[] = "(If you don't know, submit the form blank.)";
    int msg2_len = strlen(msg2);
    int start_col2 = (win_width - msg2_len) / 2;
    mvwprintw(password_win, 3, start_col1, "%s", msg1);
    mvwprintw(password_win, 4, start_col2, "%s", msg2);
    mvwgetstr(password_win, 5, start_col2, is_pass);
    wrefresh(password_win);
    noecho();

    size_t len = strlen(is_pass);
    if (len > 0 && is_pass[len - 1] == '\n') {
        is_pass[len - 1] = '\0';
    }
    wclear(password_win);
    delwin(password_win);
    if (len == 0) {
        return which_door;
    }
    if (strcmp(password, is_pass) == 0) {
        locked[which_door].state = 1;
        alert("door opened", 0);
        attron(COLOR_PAIR(2));
        mvaddch(py, px, '@');
        map[py][px] = '@';
        attroff(COLOR_PAIR(2));
        refresh();
    } else {
        WINDOW *warning_1 = newwin(win_height, win_width, start_y, start_x);
        wbkgd(warning_1, COLOR_PAIR(11));
        box(warning_1, 0, 0);
        char msg4[] = "WARNING! Try again!";
        int msg4_len = strlen(msg4);
        int start_col4 = (win_width - msg4_len) / 2;

        mvwprintw(warning_1, 3, start_col4, "%s", msg4);
        echo();
        mvwgetstr(warning_1, 5, start_col4, is_pass);
        noecho();

        size_t len = strlen(is_pass);
        if (len > 0 && is_pass[len - 1] == '\n') {
            is_pass[len - 1] = '\0';
        }
        wrefresh(warning_1);
        wclear(warning_1);
        delwin(warning_1);
        if (len == 0) {
            return which_door;
        }
        if (strcmp(password, is_pass) == 0) {
            locked[which_door].state = 1;
            alert("door opened", 0);
        } else {
            WINDOW *warning_2 = newwin(win_height, win_width, start_y, start_x);
            wbkgd(warning_2, COLOR_PAIR(8));
            box(warning_2, 0, 0);
            char msg5[] = "WARNING! Last Try!";
            int msg5_len = strlen(msg5);
            int start_col5 = (win_width - msg5_len) / 2;

            mvwprintw(warning_2, 3, start_col5, "%s", msg5);
            echo();
            mvwgetstr(warning_2, 5, start_col5, is_pass);
            noecho();

            size_t length = strlen(is_pass);
            if (length > 0 && is_pass[length - 1] == '\n') {
                is_pass[length - 1] = '\0';
            }
            wrefresh(warning_2);
            wclear(warning_2);
            delwin(warning_2);
            if (length == 0) {
                return which_door;
            }
            if (strcmp(password, is_pass) == 0) {
                locked[which_door].state = 1;
                alert("door opened", 0);
            } else {
                WINDOW *warning_3 = newwin(win_height, win_width, start_y, start_x);
                wbkgd(warning_3, COLOR_PAIR(8));
                box(warning_3, 0, 0);
                char msg6[] = "WARNING! Security Lockdown!";
                int msg6_len = strlen(msg6);
                int start_col6 = (win_width - msg6_len) / 2;

                mvwprintw(warning_3, 3, start_col6, "%s", msg6);
                wrefresh(warning_3);
                getch();
                wclear(warning_3);
                delwin(warning_3);
            }
        }
    }
    return which_door;
}

void show_password_dialogue(int px, int py) {
    int passkey = 0;
    passkey = rand() % 10000;
    password[0] = '0' + (passkey % 10000) / 1000;
    password[1] = '0' + (passkey % 1000) / 100;
    password[2] = '0' + (passkey % 100) / 10;
    password[3] = '0' + (passkey % 10);
    password[4] = '\0';
    alert("password", passkey);
}

void pick_up(int y, int x) {
    if (map[y][x] == '*') {
        pocket[pocket_count].x = x;
        pocket[pocket_count].y = y;
        pocket[pocket_count].name = "master key";
        alert("picked up key", 0);
        pocket_count++;
    } else if (map[y][x] == '%') {
        pocket[pocket_count].x = x;
        pocket[pocket_count].y = y;
        pocket[pocket_count].name = "food";
        int food_index = 0;
        for (int i = 0; i < food_count; i++) {
            if (foods[i].x == x && foods[i].y == y) {
                food_index = i;
                foods[i].state = 0;
            }
        }
        alert("picked up food", food_index);
        pocket_count++;
    } else if (map[y][x] == '$') {
        pocket[pocket_count].x = x;
        pocket[pocket_count].y = y;
        pocket[pocket_count].name = "gold";
        int gold_type = 0;
        for (int i = 0; i < gold_count; i++) {
            if (golds[i].x == x && golds[i].y == y) {
                gold_type = golds[i].type;
                golds[i].state = 0;
            }
        }
        alert("picked up gold", gold_type);
        pocket_count++;
    } else if (map[y][x] == 'm' || map[y][x] == 'd' || map[y][x] == '~' || map[y][x] ==
               'a' || map[y][x] == '!') {
        pocket[pocket_count].x = x;
        pocket[pocket_count].y = y;
        pocket[pocket_count].name = "weapon";
        char symbol = 'm';
        int num = 1;
        int type = 1;
        for (int i = 0; i < weapon_count; i++) {
            if (weapons[i].x == x && weapons[i].y == y) {
                symbol = weapons[i].symbol;
                if (symbol == 'm') type = 1;
                else if (symbol == 'd') {
                    type = 2;
                    num = 10;
                } else if (symbol == '~') {
                    type = 3;
                    num = 8;
                } else if (symbol == 'a') {
                    type = 4;
                    num = 20;
                } else type = 5;
                if (num < weapons[i].num_collect) weapons[i].num_collect++;
                else weapons[i].num_collect += weapons[i].num_collect;
                weapons[i].state = 0;
            }
        }
        alert("picked up weapon", type);
        pocket_count++;
    } else if (map[y][x] == 'p') {
        pocket[pocket_count].x = x;
        pocket[pocket_count].y = y;
        pocket[pocket_count].name = "talisman";
        int type = 0;
        for (int i = 0; i < talisman_count; i++) {
            if (talismans[i].x == x && talismans[i].y == y) {
                type = talismans[i].type;
                talismans[i].state = 0;
            }
        }
        alert("picked up potion", type);
        pocket_count++;
    }
    map[y][x] = '.';
}

struct ROOM get_room_by_xy(int px, int py) {
    struct ROOM room;
    room.x = -1;
    room.y = -1;
    for (int i = 0; i < room_count[level]; i++) {
        if (px >= rooms[level][i].x && px <= rooms[level][i].x + rooms[level][i].width &&
            py >= rooms[level][i].y && py <= rooms[level][i].y + rooms[level][i].height) {
            room = rooms[level][i];
        }
    }
    return room;
}

void monster_attack(struct monster monster) {
    char type = monster.type;
    if (type == 'D') {
        alert("attack", 0);
        lose_health(5);
    } else if (type == 'F') {
        alert("attack", 1);
        lose_health(5);
    } else if (type == 'G') {
        alert("attack", 2);
        lose_health(5);
    } else if (type == 'S') {
        alert("attack", 3);
        lose_health(5);
    } else if (type == 'U') {
        alert("attack", 4);
        lose_health(5);
    }
}

void monster_move(int px, int py, struct monster *m) {
    if (m->type == 'G' || m->type == 'U') if (m->movement_num > 5) return;
    if (m->movement_state == 1) return;
    int my = m->y;
    int mx = m->x;

    int nx = mx;
    int ny = my;

    if (mx < px && mx + 1 < WIDTH && map[my][mx + 1] == '.') {
        nx++;
    } else if (mx > px && mx - 1 >= 0 && map[my][mx - 1] == '.') {
        nx--;
    } else if (my < py && my + 1 < HEIGHT && map[my + 1][mx] == '.') {
        ny++;
    } else if (my > py && my - 1 >= 0 && map[my - 1][mx] == '.') {
        ny--;
    }

    if (nx == px && ny == py) {
        monster_attack(*m);
        return;
    }

    if (nx != mx || ny != my) {
        map[my][mx] = '.';
        m->x = nx;
        m->y = ny;
        m->movement_num++;
        map[ny][nx] = m->type;
    }

    render_map();
}

int monster_check(int x, int y, struct monster monster) {
    if (monster.state == 0 && (monster.x == x || monster.x == x + 1 || monster.x == x - 1) && (
            monster.y == y || monster.y == y + 1 || monster.y == y - 1)) {
        return 1;
    } else return 0;
}

void door_fix(struct ROOM room) {
    for (int y = room.y; y < room.y + room.height; y++) {
        if (map[y][room.x] == '+') {
            if (map[y][room.x - 1] != '#') {
                map[y][room.x] = '|';
            }
        } else {
            if (map[y][room.x - 1] == '#') {
                map[y][room.x] = '+';
            }
        }
    }

    for (int y = room.y; y < room.y + room.height; y++) {
        if (map[y][room.x + room.width - 1] == '+') {
            if (map[y][room.x + room.width] != '#') {
                map[y][room.x + room.width - 1] = '|';
            }
        } else {
            if (map[y][room.x + room.width] == '#') {
                map[y][room.x + room.width - 1] = '+';
            }
        }
    }

    for (int x = room.x; x < room.x + room.width; x++) {
        if (map[room.y][x] == '+') {
            if (map[room.y - 1][x] != '#') {
                map[room.y][x] = '-';
            }
        } else {
            if (map[room.y - 1][x] == '#') {
                map[room.y][x] = '+';
            }
        }
    }

    for (int x = room.x; x < room.x + room.width; x++) {
        if (map[room.y + room.height - 1][x] == '+') {
            if (map[room.y + room.height][x] != '#') {
                map[room.y + room.height - 1][x] = '-';
            }
        } else {
            if (map[room.y + room.height][x] == '#') {
                map[room.y + room.height - 1][x] = '+';
            }
        }
    }
}

void fix_edges(struct ROOM room) {
    for (int y = room.y; y < room.y + room.height; y++) {
        if (room.x > 0 && map[y][room.x - 1] == '#') {
            map[y][room.x] = '+';
        }
    }

    for (int y = room.y; y < room.y + room.height; y++) {
        if (room.x + room.width < WIDTH && map[y][room.x + room.width] == '#') {
            map[y][room.x + room.width - 1] = '+';
        }
    }

    for (int x = room.x; x < room.x + room.width; x++) {
        if (room.y > 0 && map[room.y - 1][x] == '#') {
            map[room.y][x] = '+';
        }
    }

    for (int x = room.x; x < room.x + room.width; x++) {
        if (room.y + room.height < HEIGHT && map[room.y + room.height][x] == '#') {
            map[room.y + room.height - 1][x] = '+';
        }
    }
}


MenuState handle_new_game(WINDOW *win) {
    if (signed_in_user.username == NULL) {
        strcpy(signed_in_user.username, "Guest"); // Or handle differently
    }
    clear();
    curs_set(0);
    bool treasure_room_place = false;
    init_map();
    while (room_count[level] < ROOM_COUNT) {
        struct ROOM new_room;
        new_room.width = ROOM_MIN_SIZE + rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1);
        new_room.height = ROOM_MIN_SIZE + rand() % (ROOM_MAX_SIZE - ROOM_MIN_SIZE + 1);
        new_room.x = rand() % (WIDTH - new_room.width - 1);
        new_room.y = rand() % (HEIGHT - new_room.height - 1);

        bool overlap = false;

        for (int i = 0; i < room_count[level]; i++) {
            if (room_overlap(new_room, rooms[level][i])) {
                overlap = true;
                break;
            }
        }

        if (!overlap) {
            if (level < 4) {
                int prob = rand() % 6;
                if (prob == 0) new_room.type = 1;
                else new_room.type = 0;
            } else new_room.type = 0;
            add_room(new_room);
            add_pillar(new_room);
            add_trap(new_room);
            add_food(new_room);
            add_gold(new_room);
            add_weapon(new_room);
            add_talisman(new_room);

            // Room types:
            // 0: Regular
            // 1: Enchant
            // 2: Treasure
            if (new_room.type != 1) add_monster(new_room);

            if (room_count[level] > 0) {
                corridor(
                    rooms[level][room_count[level] - 1].x + rooms[level][room_count[level] - 1].width / 2,
                    rooms[level][room_count[level] - 1].y + rooms[level][room_count[level] - 1].height / 2,
                    new_room.x + (new_room.width - 2) / 2,
                    new_room.y + (new_room.height - 2) / 2
                );

                door_fix(new_room);
                fix_edges(new_room);
                if (rand() % 6 == 0) add_hidden_door(new_room);
            }
            rooms[level][room_count[level]++] = new_room;
        }
    }

    if (level == 4 && !treasure_room_place) {
        int room = rand() % 6;
        if (room == 0) room = 1;
        rooms[level][room].type = 2;
        treasure_room_place = true;
        add_treasure(rooms[level][room]);
    }


    int room_with_stairs = rand() % 6;
    int room_with_key = rand() % 6;

    if (level != 4) add_stairs(rooms[level][room_with_stairs]);
    add_master_key(rooms[level][room_with_key]);
    if (rand() % 4 == 0) locked_door(rooms[level][0]);
    int px = rooms[level][0].x + 1, py = rooms[level][0].y + 1;
    player_in_room(px, py, rooms[level], room_count[level]);

    int ch;


    while (1) {
        curs_set(0);
        refresh();
        cbreak();
        noecho();
        health_bar(health);
        hunger_bar(hunger);
        if (health <= 0 || hunger <= 0) {
            score += gold * 2;
            score -= 3;
            if (strcmp(signed_in_user.username, "Guest")) {
                set_user_stat(signed_in_user.username, "golds",
                              get_user_stat(signed_in_user.username, "golds") + gold);
                if (get_user_stat(signed_in_user.username, "highscore") < score) {
                    set_user_stat(signed_in_user.username, "highscore", score);
                }
            }

            FILE *file = fopen("../data/score.txt", "w");
            char score_c[10];
            sprintf(score_c, "%d", score);
            fwrite(score_c, sizeof(score_c), 1, file);
            fclose(file);

            return MENU_LOSE;
        }
        show_level();
        show_gold();
        render_map();
        init_colors();
        int color;
        FILE *filec = fopen("../data/color.txt", "r");
        char color_s[1000];
        fscanf(filec, "%s", color_s);
        color = color_s[0] - '0';
        fclose(filec);
        attron(COLOR_PAIR(color + 20));
        mvaddch(py, px, 'X');
        attroff(COLOR_PAIR(color + 20));

        refresh();

        if (level == 1 && first == 1) {
            first = 0;
            if (pause_window(px, py)) return MENU_MAIN;
            render_map();
        }
        ch = getch();
        if (ch == 'q') break;
        int nx = px, ny = py;
        if (talisman_time_track > 0) talisman_time_track--;
        if (food_time_out > 0) food_time_out--;
        if (food_time_out == 0) spoil_food();
        if (talisman_time_track <= 0 && (used_talisman || used_magic_food)) {
            num_of_blocks = 1;
            if (used_talisman) alert("talisman time over", 0);
            used_talisman = false;
        }
        if (ch == KEY_UP || ch == '8') ny -= num_of_blocks;
        else if (ch == KEY_DOWN || ch == '2') ny += num_of_blocks;
        else if (ch == KEY_LEFT || ch == '4') nx -= num_of_blocks;
        else if (ch == KEY_RIGHT || ch == '6') nx += num_of_blocks;
        else if (ch == '7') {
            nx -= num_of_blocks;
            ny -= num_of_blocks;
        } else if (ch == '9') {
            ny -= num_of_blocks;
            nx += num_of_blocks;
        } else if (ch == '1') {
            ny += num_of_blocks;
            nx -= num_of_blocks;
        } else if (ch == '3') {
            nx += num_of_blocks;
            ny += num_of_blocks;
        } else if (ch == 'M') {
            reveal_whole_map();
        } else if (ch == 's') {
            search_around(ny, nx);
        } else if (ch == 'e') {
            quick_eat();
        } else if (ch == 'i') {
            inventory_window();
        } else if (ch == 't') {
            quick_talisman_use();
        } else if (ch == 'w') {
            alert("weapon in bag", weapon_in_hand->symbol);
            weapon_in_backpack();
        } else if (ch == 'a') {
            //if (long_range_weapon) a_command(px, py);
            // else messages("no long range weapon", 0);
        } else if (ch == ' ') {
            if (weapon_in_hand) {
                if (is_ranged_weapon(weapon_in_hand->symbol)) {
                    long_range_weapon = true;
                    mvprintw(0, 0, "Choose a direction to throw the weapon!");
                    int direction = getch();
                    char dir[3] = {0};
                    int type = 0;
                    if (direction == KEY_DOWN || direction == '2') strcpy(dir, "d");
                    else if (direction == KEY_LEFT || direction == '4') strcpy(dir, "l");
                    else if (direction == KEY_RIGHT || direction == '6') strcpy(dir, "r");
                    else if (direction == KEY_UP || direction == '8') strcpy(dir, "u");
                    else if (direction == '1') strcpy(dir, "dl");
                    else if (direction == '3') strcpy(dir, "dr");
                    else if (direction == '7') strcpy(dir, "ul");
                    else if (direction == '9') strcpy(dir, "ur");

                    if (weapon_in_hand->symbol == 'd') type = 0;
                    else if (weapon_in_hand->symbol == '~') type = 1;
                    else if (weapon_in_hand->symbol == 'a') type = 2;
                    ranged_attack(px, py, dir, type);
                } else {
                    long_range_weapon = false;
                    struct monster mon = monster_in_room(px, py);
                    if (mon.x != -1 && mon.y != -1) {
                        attack(mon.x, mon.y, weapon_in_hand->symbol);
                    } else alert("no monster", 0);
                }
            } else alert("no weapon", 0);
        } else if (ch == 27) {
            if (pause_window(px, py)) return MENU_MAIN;
        } else if (ch == 'f') {
            int condition[2] = {0};
            int direction = getch();
            if (direction == KEY_UP || direction == '8') condition[0] = -1;
            else if (direction == KEY_DOWN || direction == '2') condition[0] = 1;
            else if (direction == KEY_LEFT || direction == '4') condition[1] = -1;
            else if (direction == KEY_RIGHT || direction == '6') condition[1] = 1;
            else if (direction == '7') {
                condition[0] = -1;
                condition[1] = -1;
            } else if (direction == '9') {
                condition[0] = -1;
                condition[1] = 1;
            } else if (direction == '1') {
                condition[0] = 1;
                condition[1] = -1;
            } else if (direction == '3') {
                condition[0] = 1;
                condition[1] = 1;
            }

            while (map[ny][nx] == '.') {
                nx += condition[1];
                ny += condition[0];
                if (map[ny][nx] == '.') {
                    px = nx;
                    py = ny;
                }
            }
        }

        if (map[ny][nx] == '#' || map[ny][nx] == '+' || map[ny][nx] == '^' || map[ny][nx] == '?') {
            px = nx;
            py = ny;
            player_in_room(px, py, rooms[level], room_count[level]);
        } else if (map[ny][nx] == '<') {
            char enter = getch();
            if (enter == '<') {
                level++;
                init_map();
                return handle_new_game(win);
            }
            px = nx;
            py = ny;
        } else if (map[ny][nx] == '@') {
            bool master = false;
            if (master_key[level] && master_keys_broken[level] == false) {
                px = nx;
                py = ny;
                master_key[level] = false;
                master = true;
            } else {
                if (master_keys_broken[level] == true) {
                    alert("key broke", 0);
                    for (int i = 0; i < level; i++) {
                        if (master_keys_broken[i]) {
                            alert("fix key", 0);
                            char accept = getch();
                            if (accept == 'y') {
                                master_keys_broken[level] = false;
                                alert("key fixed", 0);
                                master = true;
                            }
                        }
                    }
                }
            }
            if (master) {
                px = nx;
                py = ny;
            } else {
                int which_door = lock_pass_input(nx, ny);
                if (locked[which_door].state) {
                    px = nx;
                    py = ny;
                }
            }
        } else if (map[ny][nx] == '&') {
            // px = nx;
            // py = ny;
            show_password_dialogue(nx, ny);
        } else if (map[ny][nx] == '*') {
            int break_prob = rand() % 10;
            if (break_prob == 0) {
                master_keys_broken[level] = true;
            }
            px = nx;
            py = ny;
            pick_up(ny, nx);

            if (first_key[level]) {
                alert("master key found", 0);
            }
            if (first_key[level]) {
                master_key[level] = true;
                first_key[level] = false;
            }
        } else if (map[ny][nx] == '%') {
            px = nx;
            py = ny;
            pick_up(ny, nx);
        } else if (map[ny][nx] == 'T') {
            px = nx;
            py = ny;
            score += gold * 4;
            score += 1000;
            if (strcmp(signed_in_user.username, "Guest")) {
                set_user_stat(signed_in_user.username, "golds",
                              get_user_stat(signed_in_user.username, "golds") + gold);
                if (get_user_stat(signed_in_user.username, "highscore") < score) {
                    set_user_stat(signed_in_user.username, "highscore", score);
                }
            }
            FILE *file = fopen("../data/score.txt", "w");
            char score_c[10];
            sprintf(score_c, "%d", score);
            fwrite(score_c, sizeof(score_c), 1, file);
            fclose(file);
            return MENU_WIN;
        } else if (map[ny][nx] == '$') {
            px = nx;
            py = ny;
            pick_up(ny, nx);
        } else if (map[ny][nx] == 'm' || map[ny][nx] == 'd' || map[ny][nx] == '~' || map[ny][
                       nx] == 'a' || map[ny][nx]
                   == '!') {
            px = nx;
            py = ny;
            pick_up(ny, nx);
        } else if (map[ny][nx] == 'p') {
            px = nx;
            py = ny;
            pick_up(ny, nx);
        } else if (map[ny][nx] == '|' || map[ny][nx] == '-') {
            reveal_door(ny, nx);
        } else if (map[ny][nx] == '.') {
            for (int i = 0; i < traps_count; i++) {
                if (traps[i].x == nx && traps[i].y == ny) {
                    reveal_trap(ny, nx);
                }
            }
            px = nx;
            py = ny;

            struct ROOM room_p = get_room_by_xy(px, py);
            if (room_p.x != -1 && room_p.y != -1) {
                for (int i = 0; i < monster_count; i++) {
                    if (monsters[i].level == level && monsters[i].state == 0 && (
                            monsters[i].x >= room_p.x && monsters[i].x <= room_p.x + room_p.width) && (
                            monsters[i].y >= room_p.y && monsters[i].y <= room_p.y + room_p.height) && room_p.type !=
                        1) {
                        if (monsters[i].type == 'G' || monsters[i].type == 'S' || monsters[i].type ==
                            'U') {
                            monster_move(px, py, &monsters[i]);
                        }
                        if (monster_check(px, py, monsters[i])) monster_attack(monsters[i]);
                    }
                }
            }
        }
        health_update(0);
        hunger_update();
        refresh();
    }
    curs_set(1);
    return MENU_MAIN;
}
