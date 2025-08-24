#pragma once
#include <iostream>
#include "pong_object.hpp"

class Ball : public PongObject {
public:
    Ball(int startX, int startY, int width, int height, const std::string& symbol);

    void update(const PongObject& paddle1, const PongObject& paddle2, int screenWidth, int screenHeight);
    void render() const;

    void reset(int startX, int startY);

private:
    int dx, dy; // Ball velocity
    std::string _symbol;
};
