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
    void run();

private:
    // Core game loop pieces
    void processInput();
    void update();
    void render();
    void resetBall();

    // Game objects
    Paddle player1;
    Paddle player2;
    Ball ball;

    // Settings
    int width, height;
    bool running;
};
