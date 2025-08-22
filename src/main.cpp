/*
 * main.cpp
 * Program entry point
 */

#include "headers/game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    // Handle command line arguments
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "-h" || arg == "--help") {
            std::cout << "Pong Game - A simple terminal-based Pong implementation\n";
            std::cout << "Usage: " << argv[0] << " [option]\n\n";
            std::cout << "Options:\n";
            std::cout << "  -h, --help     Show this help message\n";
            std::cout << "  -v, --version  Show version information\n";
            std::cout << "\nControls:\n";
            std::cout << "  W/S - Move Player 1 paddle up/down\n";
            std::cout << "  ESC - Quit game\n";
            return 0;
        } else if (arg == "-v" || arg == "--version") {
            std::cout << "Pong Game v1.0.0\n";
            std::cout << "A clean, object-oriented implementation of the classic Pong game\n";
            return 0;
        } else {
            std::cout << "Unknown option: " << arg << "\n";
            std::cout << "Use -h or --help for usage information\n";
            return 1;
        }
    }
    
    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    try {
        // Create and start the game
        Game game;
        game.start();
        
        std::cout << "\nThanks for playing Pong!\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
    
    return 0;
}
