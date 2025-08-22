/*
 * paddle.cpp
 * Paddle entity implementation
 */

#include "headers/paddle.hpp"
#include <algorithm>

Paddle::Paddle(const Vector2D& position, double speed, bool isPlayer1)
    : GameObject(position, Vector2D(0, 0), 1, 3, "█"), 
      m_speed(speed), m_isPlayer1(isPlayer1), m_isAI(false), m_moveDirection(0, 0) {
}

void Paddle::update(double deltaTime) {
    m_velocity = m_moveDirection * m_speed;
    GameObject::update(deltaTime);
}

void Paddle::onCollision(GameObject& other) {
    // Paddle collision logic will be handled in World class
}

void Paddle::moveUp() {
    m_moveDirection.y = -1;
}

void Paddle::moveDown() {
    m_moveDirection.y = 1;
}

void Paddle::stop() {
    m_moveDirection.y = 0;
}

void Paddle::updateAI(const Vector2D& ballPosition, double deltaTime) {
    if (!m_isAI) return;
    
    // Simple AI: follow the ball
    double paddleCenter = m_position.y + m_height / 2.0;
    double ballCenter = ballPosition.y;
    
    if (ballCenter < paddleCenter - 0.5) {
        moveUp();
    } else if (ballCenter > paddleCenter + 0.5) {
        moveDown();
    } else {
        stop();
    }
}
