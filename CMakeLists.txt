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
    src/world.cpp
    src/screen.cpp
    src/inputhandler.cpp
    src/ball.cpp
    src/paddle.cpp
    src/gameobject.cpp
    src/ncurses.cpp
)

# Include directories
include_directories(src/headers)
include_directories(${NCURSES_INCLUDE_DIRS})

# Create executable
add_executable(pong ${SOURCES})

# Link libraries
target_link_libraries(pong Threads::Threads ${NCURSES_LIBRARIES})

# Install target
install(TARGETS pong DESTINATION bin)

# Set properties
set_target_properties(pong PROPERTIES
    OUTPUT_NAME "pong"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Print configuration info
message(STATUS "Pong Game Configuration:")
message(STATUS "  C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Install Prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  NCurses Found: ${NCURSES_FOUND}")
