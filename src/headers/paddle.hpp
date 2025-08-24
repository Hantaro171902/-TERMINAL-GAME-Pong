#pragma once
#include "pong_object.hpp"

class Paddle : public PongObject {
public:
    Paddle(int startX, int startY, int length, int thickness, const std::string& symbol);
    
    void moveUp();
    void moveDown();

    void draw() const override;
    void update(float deltaTime) override;
};
