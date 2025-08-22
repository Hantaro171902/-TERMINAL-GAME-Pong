/*
 * screen.cpp
 * Screen management implementation using ncurses
 */

#include "headers/screen.hpp"
#include <iostream>
#include <algorithm>

Screen::Screen() : m_width(80), m_height(30), m_initialized(false) {
    m_buffer.resize(m_height, std::string(m_width, ' '));
}

Screen::~Screen() {
    cleanup();
}

void Screen::initialize() {
    if (m_initialized) return;
    
    setupTerminal();
    hideCursor();
    m_initialized = true;
}

void Screen::cleanup() {
    if (!m_initialized) return;
    
    showCursor();
    restoreTerminal();
    m_initialized = false;
}

void Screen::clear() {
    // Clear the buffer
    for (auto& row : m_buffer) {
        std::fill(row.begin(), row.end(), ' ');
    }
    
    // Clear the terminal using ncurses
    ncurses::clear();
}

void Screen::refresh() {
    // Use ncurses refresh
    ncurses::refresh();
}

void Screen::drawChar(int x, int y, char ch) {
    if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
        m_buffer[y][x] = ch;
        // Draw using ncurses
        ncurses::draw(y, x, std::string(1, ch));
    }
}

void Screen::drawString(int x, int y, const std::string& str) {
    for (size_t i = 0; i < str.length() && x + i < m_width; ++i) {
        drawChar(x + i, y, str[i]);
    }
}

void Screen::drawBorder() {
    // Draw border using ncurses
    ncurses::drawBox();
}

void Screen::drawScore(int player1Score, int player2Score) {
    std::string scoreText = "Player 1: " + std::to_string(player1Score) + 
                           " | Player 2: " + std::to_string(player2Score);
    int x = (m_width - scoreText.length()) / 2;
    drawString(x, 1, scoreText);
}

void Screen::drawGameOver(int winner) {
    std::string gameOverText = "GAME OVER - Player " + std::to_string(winner) + " Wins!";
    int x = (m_width - gameOverText.length()) / 2;
    int y = m_height / 2;
    drawString(x, y, gameOverText);
    
    std::string pressKeyText = "Press any key to exit...";
    x = (m_width - pressKeyText.length()) / 2;
    drawString(x, y + 1, pressKeyText);
}

void Screen::setCursorPosition(int x, int y) {
    // Cursor positioning is handled by ncurses
}

void Screen::hideCursor() {
    ncurses::curs_set(0);
}

void Screen::showCursor() {
    ncurses::curs_set(1);
}

void Screen::setupTerminal() {
    // Initialize ncurses
    ncurses::setlocale();
    ncurses::init();
    ncurses::cbreak();
    ncurses::noecho();
    ncurses::keypad();
    ncurses::meta();
    ncurses::nodelay();
    ncurses::typeahead();
    
    // Get terminal size
    uint32_t height, width;
    ncurses::setScreenDimensions(height, width);
    m_width = width;
    m_height = height;
    
    // Resize buffer
    m_buffer.resize(m_height, std::string(m_width, ' '));
}

void Screen::restoreTerminal() {
    // Terminate ncurses
    ncurses::terminate();
}
