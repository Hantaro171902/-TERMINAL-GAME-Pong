/*
 * main.cpp
 * Program entry point
 */

#include "game.hpp"
#include "ball.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>

using namespace std;

int main(int argc, char* argv[]) {
    // Handle command line arguments
    if (argc > 1) {
        string arg = argv[1];
        if (arg == "-h" || arg == "--help") {
            cout << "Pong Game - A simple terminal-based Pong implementation\n";
            cout << "Usage: " << argv[0] << " [option]\n\n";
            cout << "Options:\n";
            cout << "  -h, --help     Show this help message\n";
            cout << "  -v, --version  Show version information\n";
            cout << "\nControls:\n";
            cout << "  W/S - Move Player 1 paddle up/down\n";
            cout << "  ESC - Quit game\n";
            return 0;
        } else if (arg == "-v" || arg == "--version") {
            cout << "Pong Game v1.0.0\n";
            cout << "A clean, object-oriented implementation of the classic Pong game\n";
            return 0;
        } else {
            cout << "Unknown option: " << arg << "\n";
            cout << "Use -h or --help for usage information\n";
            return 1;
        }
    }
    
    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
    
    try {
        // Create and start the game
        Game game;
        game.start();
        
        cout << "\nThanks for playing Pong!\n";
        
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Unknown error occurred" << endl;
        return 1;
    }

    // Testing demo
    clearScreen();
    hideCursor();

    PongObject paddle(80, 24, 5, 1);
    paddle.setPosition(2, 10);

    Ball ball(80, 24, -20.0f, 8.0f);
    ball.setPosition(40, 12);

    float delta = 0.1f;

    while (true) {
        // ball.clear();
        ball.update(delta, paddle);
        // ball.draw();

        sleep_ms(50);

        if (ball.isOutLeft() || ball.isOutRight()) {
            break; // game over
        }
    }

    showCursor();
    
    return 0;
}
