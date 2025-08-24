// ultils.hpp
#pragma once

#include <iostream>
#include <string>
#include "color.hpp"

// template <typename T> int signum(T val) {
//     return (T(0) < val) - (val < T(0));
// }

// Terminal manipulation functions
void clearScreen();
void clearTerminal(); // Full terminal reset

// void setTextColor(int color);

// Cursor visibility
void hideCursor();
void showCursor();
void moveCursor(int x, int y);


void sleep_ms(int ms);
int random_range(int min, int max);
std::string formatTime(int totalSeconds);

// void play_sound(const std::string& path);


// Box drawing characters (UTF-8)
extern const char SYMBOL_HORIZONTAL[];
extern const char SYMBOL_VERTICAL[];
extern const char SYMBOL_TOP_LEFT[];
extern const char SYMBOL_TOP_RIGHT[];
extern const char SYMBOL_BOTTOM_LEFT[];
extern const char SYMBOL_BOTTOM_RIGHT[];
extern const char SYMBOL_T_LEFT[];
extern const char SYMBOL_T_RIGHT[];
extern const char SYMBOL_T_TOP[];
extern const char SYMBOL_T_BOTTOM[];
extern const char SYMBOL_INTERSECT[];

// Double line box drawing characters (UTF-8)
extern const char SYMBOL_DOUBLE_HORIZONTAL[];
extern const char SYMBOL_DOUBLE_VERTICAL[];
extern const char SYMBOL_DOUBLE_TOP_LEFT[];         
extern const char SYMBOL_DOUBLE_TOP_RIGHT[];
extern const char SYMBOL_DOUBLE_BOTTOM_LEFT[];
extern const char SYMBOL_DOUBLE_BOTTOM_RIGHT[];
extern const char SYMBOL_DOUBLE_T_LEFT[];
extern const char SYMBOL_DOUBLE_T_RIGHT[];
extern const char SYMBOL_DOUBLE_T_TOP[];
extern const char SYMBOL_DOUBLE_T_BOTTOM[];
extern const char SYMBOL_DOUBLE_INTERSECT[];

extern const char BLOCK_FULL[];
extern const char BLOCK_HALF[];

// Ball
extern const char* BALL_SOLID;   // ●
extern const char* BALL_HOLLOW;  // ○
extern const char* BALL_BULLSEYE; // ◎ (optional, looks cool)