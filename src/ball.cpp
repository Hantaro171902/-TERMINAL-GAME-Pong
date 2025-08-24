#include "ball.hpp"
#include "utils.hpp" // for console positioning
#include "color.hpp"    // add for resetTextColor()
#include <iostream>

using namespace std;

Ball::Ball(int startX, int startY, int width, int height, const string& symbol)
    : PongObject(startX, startY, width, height), dx(1), dy(1), _symbol(symbol) {}

// Move the ball, check collisions with paddles and screen edges
void Ball::update(const PongObject& paddle1, const PongObject& paddle2, int screenWidth, int screenHeight) {
    // Move
    pos.x += dx;
    pos.y += dy;

    // Top/bottom wall collision
    if (pos.y <= 0 || pos.y + getLength() >= screenHeight - 1) {
        dy = -dy;
    }

    // Left paddle collision
    if (pos.x <= paddle1.getX() + paddle1.getThickness() &&
        pos.x >= paddle1.getX() &&
        pos.y >= paddle1.getY() &&
        pos.y < paddle1.getY() + paddle1.getLength()) {
        dx = -dx;
        pos.x = paddle1.getX() + paddle1.getThickness(); // push out
    }

    // Right paddle collision
    if (pos.x + getThickness() >= paddle2.getX() &&
        pos.x + getThickness() <= paddle2.getX() + paddle2.getThickness() &&
        pos.y >= paddle2.getY() &&
        pos.y < paddle2.getY() + paddle2.getLength()) {
        dx = -dx;
        pos.x = paddle2.getX() - getThickness(); // push out
    }

    // TODO: handle scoring if ball goes past left/right edges
}

void Ball::render() const {
    setTextColor(_color);
    moveCursor(pos.x, pos.y);
    cout << _symbol;
    resetTextColor();
}

void Ball::reset(int startX, int startY) {
    pos.x = startX;
    pos.y = startY;
    dx = 1;
    dy = 1;
}
