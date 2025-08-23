#include "ball.hpp"
#include <iostream>

using namespace std;

Ball::Ball(int startX, int startY, int bWidth, int bHeight, const std::string& symbol)
    : PongObject(startX, startY, bWidth, bHeight), dx(1), dy(1), symbol(symbol) {}

void Ball::draw() const {
    auto pos = getPosition();
    cout << "\033[" << static_cast<int>(pos.y) << ";" << static_cast<int>(pos.x) << "H" << getSymbol();
}

void Ball::update(float deltaTime) {
    auto pos = getPosition();
    setPosition(pos.x + dx, pos.y + dy);

    pos = getPosition();
    // bounce off top/bottom edges
    if (pos.y <= 1 || pos.y >= _windowLimitY - 1) {  
        dy = -dy;
    }

    // bounce off left/right edges (optional, for testing)
    if (pos.x <= 1 || pos.x >= _windowLimitX - 1) {
        dx = -dx;
    }
}

void Ball::bounceVertical() {
    dx = -dx;
}

void Ball::bounceHorizontal() {
    dy = -dy;
}
