cmake_minimum_required(VERSION 3.10)
project(PongGame VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# Find required packages
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSES REQUIRED ncurses)

# Source files
set(SOURCES
    src/main.cpp
    src/game.cpp
    src/ball.cpp
    src/paddle.cpp
    src/pong_object.cpp
    # src/pong.cpp
)

set(HEADERS
    src/headers/game.hpp
    src/headers/ball.hpp
    src/headers/paddle.hpp
    src/headers/pong_object.hpp
    # src/headers/pong.hpp
)

# Exe
add_executable(Pong ${SOURCES} ${HEADERS})

target_include_directories(Pong PRIVATE src/headers)

# Optional: copy asset folder into build dir
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
