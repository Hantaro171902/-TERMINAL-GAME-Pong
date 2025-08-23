#pragma once
#include <string>
#include "color.hpp"   // make sure you have this, or remove setColor if unused

struct XYPosition {
    float x;
    float y;
};

class PongObject {
public:
    PongObject(int windowX, int windowY, int length, int thickness, std::string symbol = "█")
        : _windowLimitX(windowX),
          _windowLimitY(windowY),
          _length(length),
          _thickness(thickness),
          _symbol(symbol) {
        _position = { windowX / 2.0f, windowY / 2.0f };
    }

    virtual ~PongObject() {}

    XYPosition getPosition() const { return _position; }
    void setPosition(float x, float y) { _position = {x, y}; }

    int getLength() const { return _length; }
    int getThickness() const { return _thickness; }
    std::string getSymbol() const { return _symbol; }

    // void setColor(Color color); // enable only if you have Color defined

protected:
    int _windowLimitX, _windowLimitY;
    XYPosition _position;
    int _length, _thickness;
    std::string _symbol;
};
