#pragma once
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

enum class InputKey {
    NONE,

    // Player 1 (WASD)
    P1_UP,
    P1_DOWN,
    P1_LEFT,
    P1_RIGHT,

    // Player 2 (Arrow Keys)
    P2_UP,
    P2_DOWN,
    P2_LEFT,
    P2_RIGHT,

    // General controls
    ENTER,
    ESC,
    Q, // Quit
    R, // Restart
    LEFT_BRACKET,
    RIGHT_BRACKET
};

InputKey getInputKey();