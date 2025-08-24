#include "paddle.hpp"
#include <iostream>

using namespace std;

Paddle::Paddle(int startX, int startY, int length, int thickness, const std::string& symbol)
    : PongObject(startX, startY, length, thickness, symbol) {}

void Paddle::draw() const {
    PongObject::draw();
}

void Paddle::update(float deltaTime) {
    // Paddles don’t automatically update — player input or AI controls them
    // If you want to move with velocity, add vy as a member and use setPosition
}

void Paddle::moveUp() {
    auto pos = getPosition();
    setPosition(pos.x, pos.y - 1);
    clampToBounds();
}

void Paddle::moveDown() {
    auto pos = getPosition();
    setPosition(pos.x, pos.y + 1);
    clampToBounds();
}

// int Paddle::getHeight() const { return height; }
