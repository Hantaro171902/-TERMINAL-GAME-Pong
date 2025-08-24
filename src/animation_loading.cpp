#include <iostream>
#include <thread>   // for sleep_for
#include <chrono>   // for milliseconds
#include "animation_loading.hpp"

using namespace std;

void animLoading() {
    int x = 10, y = 10; // Starting position for the loading animation
    const int width = 50;

    moveCursor(x, y);
    setTextColor(CYAN); // Cyan
    cout << SYMBOL_TOP_LEFT;
    for (int i = 0; i < width; i++) {
        cout << SYMBOL_HORIZONTAL;
    }
    cout << SYMBOL_TOP_RIGHT;

    moveCursor(x, y + 1);
    cout << SYMBOL_VERTICAL;
    setTextColor(GRAY); // Gray
    for (int i = 0; i < width; i++) {
        cout << BLOCK_HALF;
    }
    setTextColor(CYAN); // Cyan
    cout << SYMBOL_VERTICAL;

    moveCursor(x, y + 2);
    cout << SYMBOL_BOTTOM_LEFT;
    for (int i = 0; i < width; i++) {
        cout << SYMBOL_HORIZONTAL;
    }
    cout << SYMBOL_BOTTOM_RIGHT;

    moveCursor(x + 1, y + 3);
    cout << ". . . LOADING . . .";

    for (int i = 0; i <= width; i++) {
        moveCursor(x + 1 + i, y + 1);
        cout << BLOCK_FULL; // Print the loading bar
        moveCursor(x + width + 3, y + 1);
        cout << "Loading... " << (i * 100 / width) << "%"; // Show percentage
        cout.flush(); // Ensure the output is displayed immediately
        this_thread::sleep_for(chrono::milliseconds(40)); // Adjust speed as needed
    }

    moveCursor(x + 1, y + 3);
    setTextColor(GREEN); // Green
    cout << ". . . LOADING COMPLETE . . .";
    setTextColor(WHITE); // Reset to default color
    this_thread::sleep_for(chrono::milliseconds(1000)); // Pause before clearing
    clearScreen(); // Clear the screen after loading
}