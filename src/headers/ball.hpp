#pragma once
#include "pong_object.hpp"
#include <string>

class Ball : public PongObject {
private:
    int dx, dy;
    std::string symbol;

public:
    Ball(int startX, int startY, int bWidth, int bHeight, const std::string& symbol = "o");

    void draw() const override;
    void update(float deltaTime) override;

    void bounceVertical();
    void bounceHorizontal();
};
