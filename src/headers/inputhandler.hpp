/*
 * inputhandler.hpp
 * Input handling using ncurses
 */

#pragma once

#include <functional>
#include <map>

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ESCAPE,
    SPACE,
    W,
    S,
    UNKNOWN
};

class InputHandler {
public:
    InputHandler();
    ~InputHandler();
    
    // Input management
    void initialize();
    void cleanup();
    Key getKey();
    bool isKeyPressed(Key key);
    
    // Key binding
    void bindKey(Key key, std::function<void()> action);
    void unbindKey(Key key);
    
    // Input processing
    void processInput();
    
private:
    std::map<Key, std::function<void()>> m_keyBindings;
    bool m_initialized;
    
    Key translateKey(int rawKey);
    void setupTerminal();
    void restoreTerminal();
};
