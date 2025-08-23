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
#include "ultils.hpp"

class Game {
public:
    Game(int width, int height, int paddleSize, bool rightWall);

    void run();      // main game loop
    void processInput();
    void update();
    void render();

private:
    int _windowSizeX;
    int _windowSizeY;
    int _wallThickness;
    long _score;
    bool _running;
    bool _isRightWall;

    std::shared_ptr<Ball> ball;
    std::shared_ptr<Paddle> paddle;
};