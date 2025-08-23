/*
 * ball.cpp
 * Ball entity implementation
 */

#include "ball.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;


void Ball::update(float deltaTime, const PongObject& paddle) {
    _position.x += _velocityX * deltaTime;
    _position.y += _velocityY * deltaTime;

    _hasBounced = false;

    // bounce off top
    if (_position.y <= 1 && _velocityY < 0) {
        _velocityY *= -(1 + _acceleration);
        _hasBounced = true;
    }
    // bounce off bottom
    if (_position.y >= _windowLimitY - 2 && _velocityY > 0) {
        _velocityY *= -(1 + _acceleration);
        _hasBounced = true;
    }

    // paddle collision (assume left paddle)
    XYPosition paddlePos = paddle.getPosition();
    int paddleTop = paddlePos.y;
    int paddleBottom = paddlePos.y + paddle.getLength();

    if ((int)std::round(_position.x) <= paddlePos.x + paddle.getThickness() &&
        _velocityX < 0 &&
        (int)std::round(_position.y) >= paddleTop &&
        (int)std::round(_position.y) <= paddleBottom) {

        _velocityX *= -(1 + _acceleration);
        _hasBounced = true;
    }
}

bool Ball::hasBounced() const {
    return _hasBounced;
}

bool Ball::isOutLeft() const {
    return _position.x < 0;
}

bool Ball::isOutRight() const {
    return _position.x > _windowLimitX;
}

void Ball::resetVelocity() {
    _velocityX = _startVelocityX;
    _velocityY = _startVelocityY;
    // _acceleration = 0;
    // _hasBounced = false;
}