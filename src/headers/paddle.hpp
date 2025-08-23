#pragma once
#include "pong_object.hpp"

class Paddle : public PongObject {
public:
    Paddle(int windowX, int windowY, int length, int thickness, std::string symbol = "█")
        : PongObject(windowX, windowY, length, thickness, symbol), _speed(1.0f) {}

    void moveUp() {
        if (_position.y > 1) _position.y -= _speed;
    }

    void moveDown() {
        if (_position.y + _length < _windowLimitY - 1)
            _position.y += _speed;
    }

    void setSpeed(float s) { _speed = s; }
    float getSpeed() const { return _speed; }

private:
    float _speed;
};
