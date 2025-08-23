#pragma once

class Ball {
private:
    int x, y;
    int dx, dy;  // direction
    int boardWidth, boardHeight;

public:
    Ball(int startX, int startY, int bWidth, int bHeight);

    void draw() const;
    void update();
    void bounceVertical();
    void bounceHorizontal();
    int getX() const;
    int getY() const;
};
