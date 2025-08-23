/*
 * paddle.hpp
 * Paddle entity class
 */

#pragma once

#include "ultils.hpp"

class Paddle {
public:
    int x, y;       // position (x = column, y = center row)
    int length;     // paddle height
    int speed;      // how many rows it moves per key press

    Paddle(int startX, int startY, int len = 4, int spd = 1);

    void moveUp();
    void moveDown(int screenHeight);
    void draw() const;
    void clear() const;
};

