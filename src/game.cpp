/*
 * game.cpp
 * Main game controller implementation
 */

#include "headers/game.hpp"
#include "headers/world.hpp"
#include "headers/screen.hpp"
#include "headers/inputhandler.hpp"
#include "headers/ball.hpp"
#include "headers/paddle.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Game::Game() : m_isRunning(false), m_player1Score(0), m_player2Score(0) {
    // Initialize game objects
    m_screen = std::make_unique<Screen>();
    m_inputHandler = std::make_unique<InputHandler>();
    m_world = std::make_unique<World>(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    // Create ball and paddles
    Vector2D ballPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    m_ball = std::make_unique<Ball>(ballPos, BALL_SPEED);
    
    Vector2D paddle1Pos(2, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    m_player1Paddle = std::make_unique<Paddle>(paddle1Pos, PADDLE_SPEED, true);
    
    Vector2D paddle2Pos(SCREEN_WIDTH - 3, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2);
    m_player2Paddle = std::make_unique<Paddle>(paddle2Pos, PADDLE_SPEED, false);
    
    // Set AI for player 2
    m_player2Paddle->setAI(true);
    
    // Add objects to world
    m_world->setBall(std::move(m_ball));
    m_world->setPaddle1(std::move(m_player1Paddle));
    m_world->setPaddle2(std::move(m_player2Paddle));
    
    // Setup input bindings
    setupInputBindings();
}

Game::~Game() {
    stop();
}

void Game::start() {
    if (m_isRunning) return;
    
    // Initialize systems
    m_screen->initialize();
    m_inputHandler->initialize();
    
    m_isRunning = true;
    m_lastFrameTime = std::chrono::steady_clock::now();
    
    std::cout << "Pong Game Started!" << std::endl;
    std::cout << "Controls: W/S for Player 1, ESC to quit" << std::endl;
    std::cout << "Press any key to start..." << std::endl;
    
    // Wait for user input to start
    while (m_inputHandler->getKey() == Key::UNKNOWN) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    
    gameLoop();
}

void Game::stop() {
    m_isRunning = false;
    
    if (m_screen) m_screen->cleanup();
    if (m_inputHandler) m_inputHandler->cleanup();
}

bool Game::isRunning() const {
    return m_isRunning;
}

void Game::gameLoop() {
    while (m_isRunning) {
        auto currentTime = std::chrono::steady_clock::now();
        auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            currentTime - m_lastFrameTime).count() / 1000.0;
        
        if (deltaTime >= FRAME_DURATION.count() / 1000.0) {
            processInput();
            update(deltaTime);
            render();
            
            m_lastFrameTime = currentTime;
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Game::update(double deltaTime) {
    if (!m_world) return;
    
    m_world->update(deltaTime);
    
    // Update AI
    if (m_world->getPaddle2() && m_world->getBall()) {
        m_world->getPaddle2()->updateAI(m_world->getBall()->getPosition(), deltaTime);
    }
    
    // Update scores
    m_player1Score = m_world->getPlayer1Score();
    m_player2Score = m_world->getPlayer2Score();
    
    // Check for game over
    if (m_player1Score >= 10 || m_player2Score >= 10) {
        m_isRunning = false;
    }
}

void Game::render() {
    if (!m_screen) return;
    
    m_screen->clear();
    m_screen->drawBorder();
    m_screen->drawScore(m_player1Score, m_player2Score);
    
    // Draw game objects
    if (m_world->getBall()) {
        Vector2D ballPos = m_world->getBall()->getPosition();
    m_screen->drawChar(static_cast<int>(ballPos.x), static_cast<int>(ballPos.y), "●");
    }
    
    if (m_world->getPaddle1()) {
        Vector2D paddlePos = m_world->getPaddle1()->getPosition();
        for (int i = 0; i < m_world->getPaddle1()->getHeight(); ++i) {
            m_screen->drawChar(static_cast<int>(paddlePos.x), 
                              static_cast<int>(paddlePos.y) + i, "█");
        }
    }
    
    if (m_world->getPaddle2()) {
        Vector2D paddlePos = m_world->getPaddle2()->getPosition();
        for (int i = 0; i < m_world->getPaddle2()->getHeight(); ++i) {
            m_screen->drawChar(static_cast<int>(paddlePos.x), 
                              static_cast<int>(paddlePos.y) + i, "█");
        }
    }
    
    // Draw game over screen
    if (!m_isRunning) {
        int winner = (m_player1Score >= 10) ? 1 : 2;
        m_screen->drawGameOver(winner);
    }
    
    m_screen->refresh();
}

void Game::processInput() {
    if (!m_inputHandler) return;
    
    m_inputHandler->processInput();
}

void Game::handleCollisions() {
    // Collision handling is done in the World class
}

void Game::updateScore() {
    // Score updating is done in the update method
}

void Game::setupInputBindings() {
    if (!m_inputHandler) return;
    
    // Player 1 controls (W/S keys)
    m_inputHandler->bindKey(Key::W, [this]() {
        if (m_world && m_world->getPaddle1()) {
            m_world->getPaddle1()->moveUp();
        }
    });
    
    m_inputHandler->bindKey(Key::S, [this]() {
        if (m_world && m_world->getPaddle1()) {
            m_world->getPaddle1()->moveDown();
        }
    });
    
    // Quit game
    m_inputHandler->bindKey(Key::ESCAPE, [this]() {
        m_isRunning = false;
    });
}
