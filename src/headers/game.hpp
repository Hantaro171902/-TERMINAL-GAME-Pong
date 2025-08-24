/*
 * game.hpp
 * Main game controller
 */
#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "ball.hpp"
#include "paddle.hpp"
#include "cursor_input.hpp"
#include "utils.hpp"

class Game {
public:
    Game(int width, int height);
    ~Game();    // add a destructor to clean up terminal settings
    void run();

private:
    // Core game loop pieces
    void processInput();
    void update();
    void render();
    void resetBall();
    void drawBoundary() const;

    // Game objects
    Paddle player1;
    Paddle player2;
    Ball ball;

    // Settings
    const int width;
    const int height;
    bool running = true;

    // Score
    int score1 = 0;
    int score2 = 0;
};
