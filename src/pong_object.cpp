/*
 * gameobject.cpp
 * Base class implementation for all game entities
 */

#include "pong_object.hpp"
#include <iostream>

using namespace std;

void PongObject::setPosition(int x, int y) {
    _position.x = x;
    _position.y = y;
}

XYPosition PongObject::getPosition() const { 
    return _position; 
}

void PongObject::setWindowLimits(int maxX, int maxY) {
    _windowLimitX = maxX;
    _windowLimitY = maxY;
}

void PongObject::setColor(Color color) {
    _color = color;
}

void PongObject::switchColor() {
    static vector<TextColor> palette = {
        RED, GREEN, BLUE,
        YELLOW, CYAN, MAGENTA, WHITE
    };
    int idx = random_range(0, (int)palette.size() - 1);
    _color = palette[idx];
}

void PongObject::draw() const {
    setTextColor(_color); // from color.hpp
    for (int i = 0; i < _length; i++) {
        move_cursor(_position.y + i, _position.x); // from cursor_input.hpp
        for (int j = 0; j < _thickness; j++) {
            cout << _symbol;
        }
    }
    resetTextColor();
    cout.flush();
}

void PongObject::clear() const {
    for (int i = 0; i < _length; i++) {
        move_cursor(_position.y + i, _position.x);
        for (int j = 0; j < _thickness; j++) {
            cout << " ";
        }
    }
}

int PongObject::getLength() const { return _length; }
int PongObject::getThickness() const { return _thickness; }
