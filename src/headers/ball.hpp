/*
 * ball.hpp
 * Ball entity class
 */

#pragma once

#include "gameobject.hpp"

class Ball : public GameObject {
public:
    Ball(const Vector2D& position, double speed);
    ~Ball() override = default;
    
    void update(double deltaTime) override;
    void onCollision(GameObject& other) override;
    
    // Ball-specific methods
    void reset();
    void reverseX();
    void reverseY();
    void setRandomDirection();
    
private:
    double m_speed;
    Vector2D m_initialPosition;
};
