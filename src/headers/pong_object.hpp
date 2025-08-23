/*
 * pong_object.hpp
 * Base class for all game entities
 */

#pragma once

#include "color.hpp"
#include "ultils.hpp"
#include "cursor_input.hpp"
#include <vector>
#include <string>

struct XYPosition {
    int x;
    int y;
}

class PongObject {
private:
    int _windowLimitX, _windowLimitY;
    XYPosition _position;
    int _length, _thickness;
    char _symbol;
    TextColor _color;

public:
    PongObject(int windowX, int windowY, int length, int thickness, char symbol = BLOCK_FULL)
        : _windowLimitX(windowX),
          _windowLimitY(windowY),
          _length(length),
          _thickness(thickness),
          _symbol(symbol),
          _color(WHITE) {
        _position = { windowX / 2, windowY / 2 };
    }

    void setPosition(int x, int y);
    XYPosition getPosition() const;

    void setWindowLimits(int maxX, int maxY);

    void setColor(Color color);
    void switchColor();

    void draw() const;
    void clear() const;

    int getLength() const;
    int getThickness() const;

};
