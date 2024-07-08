cmake_minimum_required(VERSION 3.16)

project(telegraph C)

# CMake includes
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

# Download SDL3
FetchContent_Declare(
  SDL
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG        main
  GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(SDL)

# Download SDL2 TTF extension
FetchContent_Declare(
  SDL_ttf
  GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
  GIT_TAG        main
  GIT_PROGRESS   TRUE
)
FetchContent_MakeAvailable(SDL_ttf)

# Find ncurses
find_package(Curses REQUIRED)

# Create morse tree lib
add_library(morse_tree STATIC morse_tree.c)

target_include_directories(morse_tree PUBLIC .)

# Create exe
add_executable(telegraph main.c)

target_link_libraries(telegraph
    PRIVATE
        m
        ${CURSES_LIBRARIES}
        morse_tree
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
)
