/*
 * ball.cpp
 * Ball entity implementation
 */

#include "headers/ball.hpp"
#include <cstdlib>
#include <ctime>

Ball::Ball(const Vector2D& position, double speed)
    : GameObject(position, Vector2D(0, 0), 1, 1, "●"), m_speed(speed), m_initialPosition(position) {
    setRandomDirection();
}

void Ball::update(double deltaTime) {
    GameObject::update(deltaTime);
}

void Ball::onCollision(GameObject& other) {
    // Ball collision logic will be handled in World class
}

void Ball::reset() {
    m_position = m_initialPosition;
    setRandomDirection();
}

void Ball::reverseX() {
    m_velocity.x = -m_velocity.x;
}

void Ball::reverseY() {
    m_velocity.y = -m_velocity.y;
}

void Ball::setRandomDirection() {
    // Set random direction with constant speed
    double angle = (rand() % 360) * 3.14159 / 180.0;
    m_velocity.x = m_speed * cos(angle);
    m_velocity.y = m_speed * sin(angle);
    
    // Ensure minimum horizontal movement
    if (abs(m_velocity.x) < 0.3) {
        m_velocity.x = (m_velocity.x >= 0) ? 0.3 : -0.3;
    }
}
