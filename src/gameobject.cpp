/*
 * gameobject.cpp
 * Base class implementation for all game entities
 */

#include "headers/gameobject.hpp"
#include <algorithm>

GameObject::GameObject(const Vector2D& position, const Vector2D& velocity, 
                       int width, int height, const std::string& symbol)
    : m_position(position), m_velocity(velocity), m_width(width), m_height(height), m_symbol(symbol) {
}

void GameObject::update(double deltaTime) {
    m_position += m_velocity * deltaTime;
}

void GameObject::render() const {
    // Base implementation - can be overridden by derived classes
}

bool GameObject::isCollidingWith(const GameObject& other) const {
    // AABB collision detection
    bool xOverlap = (m_position.x < other.m_position.x + other.m_width) &&
                    (m_position.x + m_width > other.m_position.x);
    
    bool yOverlap = (m_position.y < other.m_position.y + other.m_height) &&
                    (m_position.y + m_height > other.m_position.y);
    
    return xOverlap && yOverlap;
}

void GameObject::onCollision(GameObject& other) {
    // Base implementation - can be overridden by derived classes
}
