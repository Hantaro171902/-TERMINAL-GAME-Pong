#include "paddle.hpp"

Paddle::Paddle(int startX, int startY, int len, int spd) {
    x = startX;
    y = startY;
    length = len;
    speed = spd;
}

void Paddle::moveUp() {
    if (y - length/2 > 0) {
        y -= speed;
    }
}

void Paddle::moveDown(int screenHeight) {
    if (y + length/2 < screenHeight - 1) {
        y += speed;
    }
}

void Paddle::draw() const {
    for (int i = -length/2; i <= length/2; i++) {
        gotoxy(x, y + i);
        std::cout << "|";
    }
}

void Paddle::clear() const {
    for (int i = -length/2; i <= length/2; i++) {
        gotoxy(x, y + i);
        std::cout << " ";
    }
}
