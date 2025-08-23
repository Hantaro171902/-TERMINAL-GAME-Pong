#include "pong_object.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

PongObject::PongObject(int windowX, int windowY, int length, int thickness, const std::string& symbol)
    : _windowLimitX(windowX)
    , _windowLimitY(windowY)
    , _position{ windowX / 2.0f, windowY / 2.0f }
    , _length(length)
    , _thickness(thickness)
    , _symbol(symbol)
{
}

XYPosition PongObject::getPosition() const { return _position; }

void PongObject::setPosition(float x, float y) {
    _position.x = x;
    _position.y = y;
}

void PongObject::setWindowLimits(int maxX, int maxY) {
    _windowLimitX = maxX;
    _windowLimitY = maxY;
}

int PongObject::getLength()    const { return _length; }
int PongObject::getThickness() const { return _thickness; }
std::string PongObject::getSymbol() const { return _symbol; }
void PongObject::setSymbol(const std::string& s) { _symbol = s; }

void PongObject::setColor(TextColor c) { _color = c; }
TextColor PongObject::getColor() const { return _color; }

void PongObject::switchColor() {
    static const vector<TextColor> palette = {
        RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, BRIGHT_RED, BRIGHT_GREEN,
        BRIGHT_YELLOW, BRIGHT_BLUE, BRIGHT_MAGENTA, BRIGHT_CYAN, BRIGHT_WHITE
    };
    int idx = random_range(0, static_cast<int>(palette.size()) - 1);
    _color = palette[idx];
}

void PongObject::draw() const {
    setTextColor(_color);

    // draw as a rectangle of (_length rows) × (_thickness columns)
    for (int i = 0; i < _length; ++i) {
        // NOTE: move_cursor expects (x=column, y=row)
        move_cursor(static_cast<int>(_position.x), static_cast<int>(_position.y) + i);
        for (int j = 0; j < _thickness; ++j) {
            cout << _symbol;
        }
    }

    resetTextColor();
    cout.flush();
}

void PongObject::clear() const {
    for (int i = 0; i < _length; ++i) {
        move_cursor(static_cast<int>(_position.x), static_cast<int>(_position.y) + i);
        for (int j = 0; j < _thickness; ++j) {
            cout << ' ';
        }
    }
    cout.flush();
}

void PongObject::clampToBounds() {
    // leave a 1-char margin (top/bottom/left/right) so walls can be drawn at 0 and limit-1
    int minX = 1;
    int minY = 1;
    int maxX = std::max(1, _windowLimitX - _thickness - 1);
    int maxY = std::max(1, _windowLimitY - _length    - 1);

    _position.x = std::clamp(_position.x, static_cast<float>(minX), static_cast<float>(maxX));
    _position.y = std::clamp(_position.y, static_cast<float>(minY), static_cast<float>(maxY));
}
