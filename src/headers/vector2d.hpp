/*
 * vector2d.hpp
 * 2D vector mathematics for positions and velocities
 */

#pragma once

#include <cmath>

class Vector2D {
public:
    double x, y;
    
    Vector2D() : x(0.0), y(0.0) {}
    Vector2D(double x, double y) : x(x), y(y) {}
    
    // Vector operations
    Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    Vector2D& operator+=(const Vector2D& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    // Utility functions
    double magnitude() const {
        return std::sqrt(x * x + y * y);
    }
    
    Vector2D normalized() const {
        double mag = magnitude();
        if (mag > 0) {
            return Vector2D(x / mag, y / mag);
        }
        return Vector2D(0, 0);
    }
    
    void normalize() {
        double mag = magnitude();
        if (mag > 0) {
            x /= mag;
            y /= mag;
        }
    }
};
