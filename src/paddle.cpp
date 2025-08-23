#include "paddle.hpp"


Paddle::Paddle(int startX, int startY, int h, int bHeight)
    : x(startX), y(startY), height(h), boardHeight(bHeight) {}

void Paddle::draw() const {
    for (int i = 0; i < height; i++) {
        std::cout << "\033[" << (y + i) << ";" << x << "H" << "|";
    }
}

void Paddle::moveUp() {
    if (y > 1) y--;
}

void Paddle::moveDown() {
    if (y + height < boardHeight) y++;
}

int Paddle::getX() const { return x; }
int Paddle::getY() const { return y; }
int Paddle::getHeight() const { return height; }

// void Paddle::clear() const {
//     for (int i = -length/2; i <= length/2; i++) {
//         gotoxy(x, y + i);
//         std::cout << " ";
//     }
// }
