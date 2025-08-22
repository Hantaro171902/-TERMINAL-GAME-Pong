/*
 * game.hpp
 * Main game controller
 */

#pragma once

#include <memory>
#include <chrono>
#include <string>

// Forward declarations
class World;
class Screen;
class InputHandler;
class Ball;
class Paddle;

class Game {
public:
    Game();
    ~Game();
    
    void start();
    void stop();
    bool isRunning() const;
    
private:
    void gameLoop();
    void update(double deltaTime);
    void render();
    void processInput();
    void handleCollisions();
    void updateScore();
    void setupInputBindings();
    
    // Game state
    bool m_isRunning;
    int m_player1Score;
    int m_player2Score;
    std::chrono::steady_clock::time_point m_lastFrameTime;
    
    // Game objects
    std::unique_ptr<World> m_world;
    std::unique_ptr<Screen> m_screen;
    std::unique_ptr<InputHandler> m_inputHandler;
    std::unique_ptr<Ball> m_ball;
    std::unique_ptr<Paddle> m_player1Paddle;
    std::unique_ptr<Paddle> m_player2Paddle;
    
    // Game constants
    static constexpr int SCREEN_WIDTH = 80;
    static constexpr int SCREEN_HEIGHT = 30;
    static constexpr int PADDLE_HEIGHT = 3;
    static constexpr int PADDLE_WIDTH = 1;
    static constexpr double BALL_SPEED = 1.0;
    static constexpr double PADDLE_SPEED = 1.0;
    static constexpr std::chrono::milliseconds FRAME_DURATION{50};
};
