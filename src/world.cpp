/*
 * world.cpp
 * Game world and physics implementation
 */

#include "headers/world.hpp"
#include <algorithm>

World::World(int width, int height) 
    : m_width(width), m_height(height), m_player1Score(0), m_player2Score(0) {
}

void World::update(double deltaTime) {
    if (m_ball) m_ball->update(deltaTime);
    if (m_paddle1) m_paddle1->update(deltaTime);
    if (m_paddle2) m_paddle2->update(deltaTime);
    
    checkBoundaries();
    checkCollisions();
}

void World::checkCollisions() {
    if (!m_ball) return;
    
    // Check ball-paddle collisions
    if (m_paddle1 && m_ball->isCollidingWith(*m_paddle1)) {
        handleBallPaddleCollision(*m_ball, *m_paddle1);
    }
    
    if (m_paddle2 && m_ball->isCollidingWith(*m_paddle2)) {
        handleBallPaddleCollision(*m_ball, *m_paddle2);
    }
}

void World::checkBoundaries() {
    if (m_ball) {
        handleBallWallCollision(*m_ball);
    }
    
    if (m_paddle1) {
        handlePaddleWallCollision(*m_paddle1);
    }
    
    if (m_paddle2) {
        handlePaddleWallCollision(*m_paddle2);
    }
}

void World::setBall(std::unique_ptr<Ball> ball) {
    m_ball = std::move(ball);
}

void World::setPaddle1(std::unique_ptr<Paddle> paddle) {
    m_paddle1 = std::move(paddle);
}

void World::setPaddle2(std::unique_ptr<Paddle> paddle) {
    m_paddle2 = std::move(paddle);
}

void World::handleBallPaddleCollision(Ball& ball, Paddle& paddle) {
    // Reverse ball's X direction
    ball.reverseX();
    
    // Add some randomness to the Y direction based on where the ball hit the paddle
    double paddleCenter = paddle.getPosition().y + paddle.getHeight() / 2.0;
    double ballCenter = ball.getPosition().y;
    double relativeIntersectY = (ballCenter - paddleCenter) / (paddle.getHeight() / 2.0);
    
    // Adjust Y velocity based on where the ball hit the paddle
    ball.setVelocity(Vector2D(ball.getVelocity().x, relativeIntersectY * 0.5));
}

void World::handleBallWallCollision(Ball& ball) {
    Vector2D pos = ball.getPosition();
    
    // Check top and bottom walls
    if (pos.y <= 0 || pos.y >= m_height - ball.getHeight()) {
        ball.reverseY();
    }
    
    // Check left and right walls (scoring)
    if (pos.x <= 0) {
        // Player 2 scores
        m_player2Score++;
        ball.reset();
    } else if (pos.x >= m_width - ball.getWidth()) {
        // Player 1 scores
        m_player1Score++;
        ball.reset();
    }
}

void World::handlePaddleWallCollision(Paddle& paddle) {
    Vector2D pos = paddle.getPosition();
    
    // Keep paddle within bounds
    if (pos.y < 0) {
        paddle.setPosition(Vector2D(pos.x, 0));
    } else if (pos.y > m_height - paddle.getHeight()) {
        paddle.setPosition(Vector2D(pos.x, m_height - paddle.getHeight()));
    }
}
