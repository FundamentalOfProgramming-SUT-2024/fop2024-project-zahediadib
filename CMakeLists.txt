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
        src/profile_menu.c
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS} ${SDL2_MIXER_LIBRARY_DIRS})
add_definitions(${SDL2_CFLAGS_OTHER} ${SDL2_MIXER_CFLAGS_OTHER})

# Find the Curses package and include the directories
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Link the ncurses library
target_link_libraries(Rogue ${CURSES_LIBRARIES})
target_link_libraries(Rogue ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ncurses pthread)