#include "paddle.hpp"
#include <algorithm>
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
    _position.y += vy * deltaTime;
    clampToBounds();

}

void Paddle::moveUp() {
    // auto pos = getPosition();
    // setPosition(pos.x, pos.y - 1);
    // clampToBounds();
    setVelocityY(-60.0f);
}

void Paddle::moveDown() {
    // auto pos = getPosition();
    // setPosition(pos.x, pos.y + 1);
    // clampToBounds();
    setVelocityY(60.0f);
}

void Paddle::moveLeft() {
    setVelocityX(-60.0f);
}

void Paddle::moveRight() {
    setVelocityX(60.0f);
}

void Paddle::setVelocityY(float y) {
    vy = y;
}

void Paddle::setVelocityX(float x) {
    vx = x;
}

// int Paddle::getHeight() const { return height; }
void Paddle::clampToBounds() {
    // Clamp vertical movement using the base class's logic
    int minY = 1;
    int maxY = max(1, _windowLimitY - _length - 1);
    _position.y = clamp(_position.y, static_cast<float>(minY), static_cast<float>(maxY));

    // Clamp horizontal movement using the new paddle-specific limits
    _position.x = clamp(_position.x, _xMin, _xMax);
}

void Paddle::setXLimits(float xMin, float xMax) {
    _xMin = xMin;
    _xMax = xMax;
}