/*
 * paddle.hpp
 * Paddle entity class
 */

#pragma once

#include "gameobject.hpp"

class Paddle : public GameObject {
public:
    Paddle(const Vector2D& position, double speed, bool isPlayer1);
    ~Paddle() override = default;
    
    void update(double deltaTime) override;
    void onCollision(GameObject& other) override;
    
    // Paddle-specific methods
    void moveUp();
    void moveDown();
    void stop();
    void setAI(bool isAI) { m_isAI = isAI; }
    bool isAI() const { return m_isAI; }
    bool isPlayer1() const { return m_isPlayer1; }
    
    // AI methods
    void updateAI(const Vector2D& ballPosition, double deltaTime);
    
private:
    double m_speed;
    bool m_isPlayer1;
    bool m_isAI;
    Vector2D m_moveDirection;
};
