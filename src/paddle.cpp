#include "paddle.hpp"
#include <iostream>

using namespace std;

Paddle::Paddle(int startX, int startY, int h, int bHeight, const std::string& symbol)
    : PongObject(startX, startY, h, bHeight, symbol), height(h) {}

void Paddle::draw() const {
    auto pos = getPosition();
    for (int i = 0; i < height; i++) {
        cout << "\033[" << static_cast<int>(pos.y + i) << ";" << static_cast<int>(pos.x) << "H" << getSymbol();
    }
}

void Paddle::update(float deltaTime) {
    // Paddles don’t automatically update — player input or AI controls them
    // If you want to move with velocity, add vy as a member and use setPosition
}

void Paddle::moveUp() {
    auto pos = getPosition();
    if (pos.y > 1) setPosition(pos.x, pos.y - 1);
}

void Paddle::moveDown() {
    auto pos = getPosition();
    // Use _windowLimitY from PongObject, or add a getter if needed
    if (pos.y + height < _windowLimitY) setPosition(pos.x, pos.y + 1);
}

int Paddle::getHeight() const { return height; }
