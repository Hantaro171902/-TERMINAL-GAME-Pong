/*
 * gameobject.hpp
 * Base class for all game entities
 */

#pragma once

#include "vector2d.hpp"
#include <string>

class GameObject {
public:
    GameObject(const Vector2D& position, const Vector2D& velocity, 
               int width, int height, const std::string& symbol);
    virtual ~GameObject() = default;
    
    // Getters
    Vector2D getPosition() const { return m_position; }
    Vector2D getVelocity() const { return m_velocity; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    std::string getSymbol() const { return m_symbol; }
    
    // Setters
    void setPosition(const Vector2D& position) { m_position = position; }
    void setVelocity(const Vector2D& velocity) { m_velocity = velocity; }
    
    // Game logic
    virtual void update(double deltaTime);
    virtual void render() const;
    
    // Collision detection
    bool isCollidingWith(const GameObject& other) const;
    virtual void onCollision(GameObject& other);
    
protected:
    Vector2D m_position;
    Vector2D m_velocity;
    int m_width;
    int m_height;
    std::string m_symbol;
};
