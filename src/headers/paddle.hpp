#pragma once
#include "pong_object.hpp"

class Paddle : public PongObject {
private:
    int height;

public:
    Paddle(int startX, int startY, int h, int bHeight, const std::string& symbol);
    void moveUp();
    void moveDown();

private:
    std::string symbol;

    void draw() const override;
    void update(float deltaTime) override;  // For now, paddles don’t auto-move unless AI
 

    int getHeight() const;
};
