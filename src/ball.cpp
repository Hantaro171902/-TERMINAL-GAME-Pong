#include "ball.hpp"
#include <iostream>

Ball::Ball(int startX, int startY, int bWidth, int bHeight)
    : x(startX), y(startY), dx(1), dy(1), boardWidth(bWidth), boardHeight(bHeight) {}

void Ball::draw() const {
    std::cout << "\033[" << y << ";" << x << "H" << "o";
}

void Ball::update() {
    x += dx;
    y += dy;

    if (y <= 1 || y >= boardHeight) {
        dy = -dy;
    }
}

void Ball::bounceVertical() {
    dx = -dx;
}

void Ball::bounceHorizontal() {
    dy = -dy;
}

int Ball::getX() const { return x; }
int Ball::getY() const { return y; }
