cmake_minimum_required(VERSION 3.22)
project(Rogue C)

set(CMAKE_C_STANDARD 11)

# Include the directories
include_directories(/usr/include/)
include_directories(/usr/include/ncursesw)

# Add executable first
add_executable(Rogue main.c
        src/signup_menu.c
        src/menus.c
        headers/menus.h
        src/signin_menu.c
        src/utils.c
        headers/utils.h
        headers/user.h
        src/main_menu.c
        src/leaderboard_menu.c
        src/game.c
        headers/game.h
        src/win_menu.c
        src/lose_menu.c
        src/settings_menu.c
)

# Find the Curses package and include the directories
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Link the ncurses library
target_link_libraries(Rogue ${CURSES_LIBRARIES})
