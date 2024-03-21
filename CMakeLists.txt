cmake_minimum_required(VERSION 3.16)

project(telegraph)

# Download SDL3 (!!)
include(FetchContent)

FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG        main
  GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(SDL3)

# Find ncurses
find_package(Curses REQUIRED)

# Create morse tree lib
add_library(morse_tree STATIC morse_tree.c)

target_include_directories(morse_tree PUBLIC .)

# Create exe
add_executable(telegraph telegraph.c)

target_link_libraries(telegraph
    PRIVATE
        ${CURSES_LIBRARIES}
        morse_tree
        SDL3::SDL3
)
