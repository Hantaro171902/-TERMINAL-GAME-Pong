#pragma once
#include "pong_object.hpp"
#include "ultils.hpp" // for BALL symbol

class Ball : public PongObject {
public:
    Ball(int windowX, int windowY, float speedX, float speedY)
        : PongObject(windowX, windowY, 1, 1, BALL_SOLID),
          _velocityX(speedX),
          _velocityY(speedY),
          _startVelocityX(speedX),
          _startVelocityY(speedY),
          _acceleration(0.05),
          _hasBounced(false) {}

    void update(float deltaTime, const PongObject& paddle);
    bool hasBounced() const { return _hasBounced; }
    bool isOutLeft() const { return _position.x <= 0; }
    bool isOutRight() const { return _position.x >= _windowLimitX; }
    void resetVelocity();

private:
    float _velocityX, _velocityY;
    float _startVelocityX, _startVelocityY;
    float _acceleration;
    bool _hasBounced;
};
