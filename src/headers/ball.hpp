#pragma once
#include <iostream>
#include "pong_object.hpp"

class Ball : public PongObject {
public:
    Ball(int startX, int startY, int width, int height, const std::string& symbol);

    // This method now correctly overrides the base class method.
    // Note: The signature has been changed to match the base class.
    void update(float deltaTime) override;

    // A separate method for the game logic that doesn't override anything.
    void updateBall(const PongObject& paddle1, const PongObject& paddle2, int screenWidth, int screenHeight);

    void render() const;

    void reset(int startX, int startY);

private:
    float dx = 0.0f; // Ball velocity
    float dy = 0.0f;
    // const float deceleration = 0.01f;   
    std::string _symbol;
};