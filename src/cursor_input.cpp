#include "cursor_input.hpp"

InputKey getInputKey() {
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode & echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Non-blocking
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    InputKey key = InputKey::NONE;
    char ch;

    if (read(STDIN_FILENO, &ch, 1) == 1) {
        if (ch == '\033') { // Escape sequence → arrow keys
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 1 &&
                read(STDIN_FILENO, &seq[1], 1) == 1) {
                switch (seq[1]) {
                    case 'A': key = InputKey::P2_UP; break;    // ↑
                    case 'B': key = InputKey::P2_DOWN; break;  // ↓
                    case 'C': key = InputKey::P2_RIGHT; break; // →
                    case 'D': key = InputKey::P2_LEFT; break;  // ←
                }
            }
        } else {
            switch (ch) {
                // Player 1 (WASD)
                case 'w': case 'W': key = InputKey::P1_UP; break;
                case 's': case 'S': key = InputKey::P1_DOWN; break;
                case 'a': case 'A': key = InputKey::P1_LEFT; break;
                case 'd': case 'D': key = InputKey::P1_RIGHT; break;

                // General controls
                case '\n': key = InputKey::ENTER; break;
                case 27:   key = InputKey::ESC; break; // Escape
                case 'q': case 'Q': key = InputKey::Q; break;
                case 'r': case 'R': key = InputKey::R; break;
                case '[': key = InputKey::LEFT_BRACKET; break;
                case ']': key = InputKey::RIGHT_BRACKET; break;
                default: key = InputKey::NONE; break;
            }
        }
    }

    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return key;
}
