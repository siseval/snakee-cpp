cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
project(snake)
add_subdirectory(curspp)

add_executable(snake
    main.cpp
    snakee.cpp
    board.cpp
    movement.cpp
    draw.cpp
)

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(snake ${CURSES_LIBRARY})
target_link_libraries(snake curspp)
