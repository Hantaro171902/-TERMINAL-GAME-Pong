/*
 * inputhandler.cpp
 * Input handling implementation using ncurses
 */

#include "headers/inputhandler.hpp"
#include "ncurses.hpp"
#include <iostream>

InputHandler::InputHandler() : m_initialized(false) {
}

InputHandler::~InputHandler() {
    cleanup();
}

void InputHandler::initialize() {
    if (m_initialized) return;
    
    setupTerminal();
    m_initialized = true;
}

void InputHandler::cleanup() {
    if (!m_initialized) return;
    
    restoreTerminal();
    m_initialized = false;
}

Key InputHandler::getKey() {
    if (!m_initialized) return Key::UNKNOWN;
    
    int ch = getch();
    if (ch != ERR) {
        return translateKey(ch);
    }
    return Key::UNKNOWN;
}

bool InputHandler::isKeyPressed(Key key) {
    // For non-blocking input, we'd need to implement a more complex system
    // This is a simplified version
    return false;
}

void InputHandler::bindKey(Key key, std::function<void()> action) {
    m_keyBindings[key] = action;
}

void InputHandler::unbindKey(Key key) {
    m_keyBindings.erase(key);
}

void InputHandler::processInput() {
    Key key = getKey();
    auto it = m_keyBindings.find(key);
    if (it != m_keyBindings.end()) {
        it->second();
    }
}

Key InputHandler::translateKey(int rawKey) {
    switch (rawKey) {
        case 'w':
        case 'W':
            return Key::W;
        case 's':
        case 'S':
            return Key::S;
        case 'a':
        case 'A':
            return Key::LEFT;
        case 'd':
        case 'D':
            return Key::RIGHT;
        case ' ':
            return Key::SPACE;
        case 27: // ESC
            return Key::ESCAPE;
        case KEY_UP:
            return Key::UP;
        case KEY_DOWN:
            return Key::DOWN;
        case KEY_LEFT:
            return Key::LEFT;
        case KEY_RIGHT:
            return Key::RIGHT;
        default:
            return Key::UNKNOWN;
    }
}

void InputHandler::setupTerminal() {
    // Terminal setup is handled by Screen class
}

void InputHandler::restoreTerminal() {
    // Terminal restoration is handled by Screen class
}
