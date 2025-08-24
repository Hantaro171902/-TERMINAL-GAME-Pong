#include "ball.hpp"
#include "utils.hpp"
#include "color.hpp"
#include <iostream>

Ball::Ball(int startX, int startY, int width, int height, const std::string& symbol)
    : PongObject(startX, startY, width, height, symbol), dx(1), dy(1), _symbol(symbol) {}

// A separate method for the game logic.
void Ball::updateBall(const PongObject& paddle1, const PongObject& paddle2, int screenWidth, int screenHeight) {
     // Apply deceleration to both horizontal and vertical velocities
    // if (abs(dx) > 0.01f) {
    //     dx -= signum(dx) * deceleration;
    // } else {
    //     dx = 0;
    // }

    // if (abs(dy) > 0.01f) {
    //     dy -= signum(dy) * deceleration;
    // } else {
    //     dy = 0;
    // }

    // dx = -30.0f;
    // dy = 30.0f;

    _position.x += dx;
    _position.y += dy;
    
    // Check for collision with top or bottom walls
    if (_position.y <= 1 || _position.y + getLength() >= screenHeight - 1) {
        dy = -dy;
    }
    
    // Left paddle collision
    if (_position.x <= paddle1.getX() + paddle1.getThickness() &&
        _position.x >= paddle1.getX() &&
        _position.y >= paddle1.getY() &&
        _position.y < paddle1.getY() + paddle1.getLength()) {

        dx = -dx;
        _position.x = paddle1.getX() + paddle1.getThickness();

         // Add bounce physics
        // float relativeIntersectY = (paddle1.getY() + (paddle1.getLength() / 2)) - _position.y;
        // float normalizedRelativeIntersectionY = relativeIntersectY / (paddle1.getLength() / 2);
        // dy = normalizedRelativeIntersectionY * 5.0f; // Adjust bounce speed as needed
    }

    // Right paddle collision
    if (_position.x + getThickness() >= paddle2.getX() &&
        _position.x + getThickness() <= paddle2.getX() + paddle2.getThickness() &&
        _position.y >= paddle2.getY() &&
        _position.y < paddle2.getY() + paddle2.getLength()) {

        dx = -dx;
        _position.x = paddle2.getX() - getThickness();

         // Add bounce physics
        // float relativeIntersectY = (paddle2.getY() + (paddle2.getLength() / 2)) - _position.y;
        // float normalizedRelativeIntersectionY = relativeIntersectY / (paddle2.getLength() / 2);
        // dy = normalizedRelativeIntersectionY * 5.0f; // Adjust bounce speed as needed
         // Add bounce physics
        // float relativeIntersectY = (paddle2.getY() + (paddle2.getLength() / 2)) - _position.y;
        // float normalizedRelativeIntersectionY = relativeIntersectY / (paddle2.getLength() / 2);
        // dy = normalizedRelativeIntersectionY * 5.0f; // Adjust bounce speed as needed
    }
}

// Overridden update method.
void Ball::update(float deltaTime) {
    // This method is now empty because all the logic is in updateBall.
    // The compiler will no longer complain about the virtual function being hidden.
}

void Ball::render() const {
    setTextColor(_color);
    moveCursor(static_cast<int>(_position.x), static_cast<int>(_position.y));
    std::cout << _symbol;
    resetTextColor();
}

void Ball::reset(int startX, int startY) {
    _position.x = static_cast<float>(startX);
    _position.y = static_cast<float>(startY);
    dx = 1;
    dy = 1;
}