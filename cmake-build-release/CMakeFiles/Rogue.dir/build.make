# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/Rogue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/Rogue/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/Rogue.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Rogue.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Rogue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Rogue.dir/flags.make

CMakeFiles/Rogue.dir/main.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/main.c.o: ../main.c
CMakeFiles/Rogue.dir/main.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Rogue.dir/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/main.c.o -MF CMakeFiles/Rogue.dir/main.c.o.d -o CMakeFiles/Rogue.dir/main.c.o -c /root/Rogue/main.c

CMakeFiles/Rogue.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/main.c > CMakeFiles/Rogue.dir/main.c.i

CMakeFiles/Rogue.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/main.c -o CMakeFiles/Rogue.dir/main.c.s

CMakeFiles/Rogue.dir/src/signup_menu.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/signup_menu.c.o: ../src/signup_menu.c
CMakeFiles/Rogue.dir/src/signup_menu.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Rogue.dir/src/signup_menu.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/signup_menu.c.o -MF CMakeFiles/Rogue.dir/src/signup_menu.c.o.d -o CMakeFiles/Rogue.dir/src/signup_menu.c.o -c /root/Rogue/src/signup_menu.c

CMakeFiles/Rogue.dir/src/signup_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/signup_menu.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/signup_menu.c > CMakeFiles/Rogue.dir/src/signup_menu.c.i

CMakeFiles/Rogue.dir/src/signup_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/signup_menu.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/signup_menu.c -o CMakeFiles/Rogue.dir/src/signup_menu.c.s

CMakeFiles/Rogue.dir/src/menus.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/menus.c.o: ../src/menus.c
CMakeFiles/Rogue.dir/src/menus.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Rogue.dir/src/menus.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/menus.c.o -MF CMakeFiles/Rogue.dir/src/menus.c.o.d -o CMakeFiles/Rogue.dir/src/menus.c.o -c /root/Rogue/src/menus.c

CMakeFiles/Rogue.dir/src/menus.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/menus.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/menus.c > CMakeFiles/Rogue.dir/src/menus.c.i

CMakeFiles/Rogue.dir/src/menus.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/menus.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/menus.c -o CMakeFiles/Rogue.dir/src/menus.c.s

CMakeFiles/Rogue.dir/src/signin_menu.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/signin_menu.c.o: ../src/signin_menu.c
CMakeFiles/Rogue.dir/src/signin_menu.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/Rogue.dir/src/signin_menu.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/signin_menu.c.o -MF CMakeFiles/Rogue.dir/src/signin_menu.c.o.d -o CMakeFiles/Rogue.dir/src/signin_menu.c.o -c /root/Rogue/src/signin_menu.c

CMakeFiles/Rogue.dir/src/signin_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/signin_menu.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/signin_menu.c > CMakeFiles/Rogue.dir/src/signin_menu.c.i

CMakeFiles/Rogue.dir/src/signin_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/signin_menu.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/signin_menu.c -o CMakeFiles/Rogue.dir/src/signin_menu.c.s

CMakeFiles/Rogue.dir/src/utils.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/utils.c.o: ../src/utils.c
CMakeFiles/Rogue.dir/src/utils.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/Rogue.dir/src/utils.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/utils.c.o -MF CMakeFiles/Rogue.dir/src/utils.c.o.d -o CMakeFiles/Rogue.dir/src/utils.c.o -c /root/Rogue/src/utils.c

CMakeFiles/Rogue.dir/src/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/utils.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/utils.c > CMakeFiles/Rogue.dir/src/utils.c.i

CMakeFiles/Rogue.dir/src/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/utils.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/utils.c -o CMakeFiles/Rogue.dir/src/utils.c.s

CMakeFiles/Rogue.dir/src/main_menu.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/main_menu.c.o: ../src/main_menu.c
CMakeFiles/Rogue.dir/src/main_menu.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/Rogue.dir/src/main_menu.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/main_menu.c.o -MF CMakeFiles/Rogue.dir/src/main_menu.c.o.d -o CMakeFiles/Rogue.dir/src/main_menu.c.o -c /root/Rogue/src/main_menu.c

CMakeFiles/Rogue.dir/src/main_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/main_menu.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/main_menu.c > CMakeFiles/Rogue.dir/src/main_menu.c.i

CMakeFiles/Rogue.dir/src/main_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/main_menu.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/main_menu.c -o CMakeFiles/Rogue.dir/src/main_menu.c.s

CMakeFiles/Rogue.dir/src/leaderboard_menu.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/leaderboard_menu.c.o: ../src/leaderboard_menu.c
CMakeFiles/Rogue.dir/src/leaderboard_menu.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/Rogue.dir/src/leaderboard_menu.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/leaderboard_menu.c.o -MF CMakeFiles/Rogue.dir/src/leaderboard_menu.c.o.d -o CMakeFiles/Rogue.dir/src/leaderboard_menu.c.o -c /root/Rogue/src/leaderboard_menu.c

CMakeFiles/Rogue.dir/src/leaderboard_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/leaderboard_menu.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/leaderboard_menu.c > CMakeFiles/Rogue.dir/src/leaderboard_menu.c.i

CMakeFiles/Rogue.dir/src/leaderboard_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/leaderboard_menu.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/leaderboard_menu.c -o CMakeFiles/Rogue.dir/src/leaderboard_menu.c.s

CMakeFiles/Rogue.dir/src/game.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/game.c.o: ../src/game.c
CMakeFiles/Rogue.dir/src/game.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/Rogue.dir/src/game.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/game.c.o -MF CMakeFiles/Rogue.dir/src/game.c.o.d -o CMakeFiles/Rogue.dir/src/game.c.o -c /root/Rogue/src/game.c

CMakeFiles/Rogue.dir/src/game.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/game.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/game.c > CMakeFiles/Rogue.dir/src/game.c.i

CMakeFiles/Rogue.dir/src/game.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/game.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/game.c -o CMakeFiles/Rogue.dir/src/game.c.s

CMakeFiles/Rogue.dir/src/win_menu.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/win_menu.c.o: ../src/win_menu.c
CMakeFiles/Rogue.dir/src/win_menu.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/Rogue.dir/src/win_menu.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/win_menu.c.o -MF CMakeFiles/Rogue.dir/src/win_menu.c.o.d -o CMakeFiles/Rogue.dir/src/win_menu.c.o -c /root/Rogue/src/win_menu.c

CMakeFiles/Rogue.dir/src/win_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/win_menu.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/win_menu.c > CMakeFiles/Rogue.dir/src/win_menu.c.i

CMakeFiles/Rogue.dir/src/win_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/win_menu.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/win_menu.c -o CMakeFiles/Rogue.dir/src/win_menu.c.s

CMakeFiles/Rogue.dir/src/lose_menu.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/lose_menu.c.o: ../src/lose_menu.c
CMakeFiles/Rogue.dir/src/lose_menu.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/Rogue.dir/src/lose_menu.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/lose_menu.c.o -MF CMakeFiles/Rogue.dir/src/lose_menu.c.o.d -o CMakeFiles/Rogue.dir/src/lose_menu.c.o -c /root/Rogue/src/lose_menu.c

CMakeFiles/Rogue.dir/src/lose_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/lose_menu.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/lose_menu.c > CMakeFiles/Rogue.dir/src/lose_menu.c.i

CMakeFiles/Rogue.dir/src/lose_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/lose_menu.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/lose_menu.c -o CMakeFiles/Rogue.dir/src/lose_menu.c.s

CMakeFiles/Rogue.dir/src/settings_menu.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/settings_menu.c.o: ../src/settings_menu.c
CMakeFiles/Rogue.dir/src/settings_menu.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/Rogue.dir/src/settings_menu.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/settings_menu.c.o -MF CMakeFiles/Rogue.dir/src/settings_menu.c.o.d -o CMakeFiles/Rogue.dir/src/settings_menu.c.o -c /root/Rogue/src/settings_menu.c

CMakeFiles/Rogue.dir/src/settings_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/settings_menu.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/settings_menu.c > CMakeFiles/Rogue.dir/src/settings_menu.c.i

CMakeFiles/Rogue.dir/src/settings_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/settings_menu.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/settings_menu.c -o CMakeFiles/Rogue.dir/src/settings_menu.c.s

CMakeFiles/Rogue.dir/src/profile_menu.c.o: CMakeFiles/Rogue.dir/flags.make
CMakeFiles/Rogue.dir/src/profile_menu.c.o: ../src/profile_menu.c
CMakeFiles/Rogue.dir/src/profile_menu.c.o: CMakeFiles/Rogue.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/Rogue.dir/src/profile_menu.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Rogue.dir/src/profile_menu.c.o -MF CMakeFiles/Rogue.dir/src/profile_menu.c.o.d -o CMakeFiles/Rogue.dir/src/profile_menu.c.o -c /root/Rogue/src/profile_menu.c

CMakeFiles/Rogue.dir/src/profile_menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Rogue.dir/src/profile_menu.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/Rogue/src/profile_menu.c > CMakeFiles/Rogue.dir/src/profile_menu.c.i

CMakeFiles/Rogue.dir/src/profile_menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Rogue.dir/src/profile_menu.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/Rogue/src/profile_menu.c -o CMakeFiles/Rogue.dir/src/profile_menu.c.s

# Object files for target Rogue
Rogue_OBJECTS = \
"CMakeFiles/Rogue.dir/main.c.o" \
"CMakeFiles/Rogue.dir/src/signup_menu.c.o" \
"CMakeFiles/Rogue.dir/src/menus.c.o" \
"CMakeFiles/Rogue.dir/src/signin_menu.c.o" \
"CMakeFiles/Rogue.dir/src/utils.c.o" \
"CMakeFiles/Rogue.dir/src/main_menu.c.o" \
"CMakeFiles/Rogue.dir/src/leaderboard_menu.c.o" \
"CMakeFiles/Rogue.dir/src/game.c.o" \
"CMakeFiles/Rogue.dir/src/win_menu.c.o" \
"CMakeFiles/Rogue.dir/src/lose_menu.c.o" \
"CMakeFiles/Rogue.dir/src/settings_menu.c.o" \
"CMakeFiles/Rogue.dir/src/profile_menu.c.o"

# External object files for target Rogue
Rogue_EXTERNAL_OBJECTS =

Rogue: CMakeFiles/Rogue.dir/main.c.o
Rogue: CMakeFiles/Rogue.dir/src/signup_menu.c.o
Rogue: CMakeFiles/Rogue.dir/src/menus.c.o
Rogue: CMakeFiles/Rogue.dir/src/signin_menu.c.o
Rogue: CMakeFiles/Rogue.dir/src/utils.c.o
Rogue: CMakeFiles/Rogue.dir/src/main_menu.c.o
Rogue: CMakeFiles/Rogue.dir/src/leaderboard_menu.c.o
Rogue: CMakeFiles/Rogue.dir/src/game.c.o
Rogue: CMakeFiles/Rogue.dir/src/win_menu.c.o
Rogue: CMakeFiles/Rogue.dir/src/lose_menu.c.o
Rogue: CMakeFiles/Rogue.dir/src/settings_menu.c.o
Rogue: CMakeFiles/Rogue.dir/src/profile_menu.c.o
Rogue: CMakeFiles/Rogue.dir/build.make
Rogue: /usr/lib/x86_64-linux-gnu/libcurses.so
Rogue: /usr/lib/x86_64-linux-gnu/libform.so
Rogue: CMakeFiles/Rogue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/Rogue/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking C executable Rogue"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Rogue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Rogue.dir/build: Rogue
.PHONY : CMakeFiles/Rogue.dir/build

CMakeFiles/Rogue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Rogue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Rogue.dir/clean

CMakeFiles/Rogue.dir/depend:
	cd /root/Rogue/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/Rogue /root/Rogue /root/Rogue/cmake-build-release /root/Rogue/cmake-build-release /root/Rogue/cmake-build-release/CMakeFiles/Rogue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Rogue.dir/depend

