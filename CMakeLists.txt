cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
project(snake)
add_executable(snake
  main.cpp
  curspp.cpp
  snake.cpp
  )

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(snake ${CURSES_LIBRARY})
