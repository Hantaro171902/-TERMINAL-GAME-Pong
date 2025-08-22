/*
 * screen.hpp
 * Screen management using ncurses
 */

#pragma once

#include "ncurses.hpp"
#include <string>
#include <vector>

class Screen {
public:
    Screen();
    ~Screen();
    
    // Screen management
    void initialize();
    void cleanup();
    void clear();
    void refresh();
    
    // Drawing methods
    void drawChar(int x, int y, char ch);
    void drawString(int x, int y, const std::string& str);
    void drawBorder();
    void drawScore(int player1Score, int player2Score);
    void drawGameOver(int winner);
    
    // Screen info
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    
    // Cursor control
    void setCursorPosition(int x, int y);
    void hideCursor();
    void showCursor();
    
private:
    int m_width;
    int m_height;
    std::vector<std::string> m_buffer;
    bool m_initialized;
    
    void setupTerminal();
    void restoreTerminal();
};
