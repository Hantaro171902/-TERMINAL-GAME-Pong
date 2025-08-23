/*
 * main.cpp
 * Program entry point
 */

#include "game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void show_info(const string& arg, const string& programName) {
    if (arg == "-h" || arg == "--help") {
        cout << "Pong Game - A simple terminal-based Pong implementation\n";
        cout << "Usage: " << programName << " [option]\n\n";
        cout << "Options:\n";
        cout << "  -h, --help     Show this help message\n";
        cout << "  -v, --version  Show version information\n";
        cout << "\nControls:\n";
        cout << "  W/S - Move Player 1 paddle up/down\n";
        cout << "  ↑/↓ - Move Player 2 paddle up/down\n";
        cout << "  ESC - Quit game\n";
    } else if (arg == "-v" || arg == "--version") {
        cout << "Pong Game v1.0.0\n";
        cout << "A clean, object-oriented implementation of the classic Pong game\n";
    } else {
        cout << "Unknown option: " << arg << "\n";
        cout << "Use -h or --help for usage information\n";
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
        string arg = argv[1];
        show_info(arg, argv[0]);
        return 0; // exit after showing info
    }

    int width = 80;
    int height = 25;

    Game game(width, height);
    game.run();

    return 0;
}
