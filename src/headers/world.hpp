/*
 * world.hpp
 * Game world and physics management
 */

#pragma once

#include "ball.hpp"
#include "paddle.hpp"
#include <memory>

class World {
public:
    World(int width, int height);
    ~World() = default;
    
    // World management
    void update(double deltaTime);
    void checkCollisions();
    void checkBoundaries();
    
    // Entity management
    void setBall(std::unique_ptr<Ball> ball);
    void setPaddle1(std::unique_ptr<Paddle> paddle);
    void setPaddle2(std::unique_ptr<Paddle> paddle);
    
    Ball* getBall() const { return m_ball.get(); }
    Paddle* getPaddle1() const { return m_paddle1.get(); }
    Paddle* getPaddle2() const { return m_paddle2.get(); }
    
    // World properties
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    
    // Scoring
    int getPlayer1Score() const { return m_player1Score; }
    int getPlayer2Score() const { return m_player2Score; }
    void addPlayer1Score() { m_player1Score++; }
    void addPlayer2Score() { m_player2Score++; }
    
private:
    int m_width;
    int m_height;
    int m_player1Score;
    int m_player2Score;
    
    std::unique_ptr<Ball> m_ball;
    std::unique_ptr<Paddle> m_paddle1;
    std::unique_ptr<Paddle> m_paddle2;
    
    void handleBallPaddleCollision(Ball& ball, Paddle& paddle);
    void handleBallWallCollision(Ball& ball);
    void handlePaddleWallCollision(Paddle& paddle);
};
