#ifndef GAME_H
#define GAME_H

#include "../include/ncursesw/ncurses.h"
#include "../headers/menus.h"
#include <stdbool.h>

// Map and room constants
#define MAX_ROOMS 8
#define MIN_ROOMS 4
#define MAX_FLOORS 4
#define MIN_ROOM_SIZE 5
#define MAX_ROOM_SIZE 12
#define MAP_HEIGHT 24
#define MAP_WIDTH 80

// Game mechanics constants
#define PILLAR_CHANCE 15
#define FOG_RADIUS 3
#define MAX_ITEMS_PER_ROOM 6
#define TREASURE_ROOM_WIDTH 30
#define TREASURE_ROOM_HEIGHT 15
#define TREASURE_MIN_ENEMIES 10
#define TREASURE_MAX_ENEMIES 12
#define MAX_TREASURE_ENEMIES 12
#define ENCHANT_ROOM_MIN_ENEMIES 3
#define ENCHANT_ROOM_MAX_ENEMIES 4

// Room types
typedef enum {
    ROOM_REGULAR,
    ROOM_ENCHANT,
    ROOM_TREASURE,
} RoomType;

// Weapon types
typedef enum {
    WEAPON_MACE,
    WEAPON_DAGGER,   // 20%
    WEAPON_WAND,     // 15%
    WEAPON_ARROW,    // 40%
    WEAPON_SWORD     // 25%
} WeaponType;

// Enemy types
typedef enum {
    ENEMY_DEMON,     // 40%
    ENEMY_FIRE,      // 30%
    ENEMY_GIANT,     // 15%
    ENEMY_SNAKE,     // 10%
    ENEMY_UNDEAD     // 5%
} EnemyType;

// Basic structure for position
typedef struct {
    int x;
    int y;
} Pillar;

// Item structures
typedef struct {
    int x;
    int y;
    int value;
    char symbol;
} Gold;

typedef struct {
    int x;
    int y;
    char symbol;
} Food;

typedef struct {
    int x;
    int y;
    WeaponType type;
    char symbol;
} Weapon;

typedef struct {
    int x;
    int y;
    EnemyType type;
    char symbol;
    int health;
    int damage;
} Enemy;

// Room structure
typedef struct {
    int x;
    int y;
    int width;
    int height;
    bool connected;
    RoomType type;
    Pillar pillars[4];
    int num_pillars;
    Gold golds[2];
    int num_golds;
    Food foods[2];
    int num_foods;
    Weapon weapons[2];
    int num_weapons;
    Enemy enemies[MAX_TREASURE_ENEMIES];
    int num_enemies;
    bool is_treasure_portal;
    int portal_x;
    int portal_y;
} Room;

// Floor structure
typedef struct {
    Room rooms[MAX_ROOMS];
    int num_rooms;
    char layout[MAP_HEIGHT][MAP_WIDTH];
} Floor;

extern Floor floors[MAX_FLOORS];

// Core game functions
void init_map();
void reset_game();

MenuState handle_new_game(WINDOW *win);

#endif /* GAME_H */