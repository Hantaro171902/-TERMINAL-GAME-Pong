#include "game.hpp"
#include <iostream>

using namespace std;

Game::Game(int width, int height, int paddleSize, bool rightWall)
    : _windowSizeX(width),
      _windowSizeY(height),
      _wallThickness(1),   // much smaller than SDL version
      _score(0),
      _running(true),
      _isRightWall(rightWall) 
{
    ball = std::make_shared<Ball>(width/2, height/2, 1, 1); // starting in center
    paddle = std::make_shared<Paddle>(2, height/2, paddleSize, 1); // left paddle
}

void Game::run() {
    while (_running) {
        processInput();
        update();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // ~20 fps
    }
}

void Game::processInput() {
    // Non-blocking key press check
    if (kbhit()) {
        char ch = getchar();
        if (ch == 'q') _running = false; // quit
        if (ch == 'w') paddle->moveUp();
        if (ch == 's') paddle->moveDown(_windowSizeY);
    }
}

void Game::update() {
    ball->update(_windowSizeX, _windowSizeY, *paddle);

    if (ball->outOfBounds(_windowSizeX, _windowSizeY)) {
        _score -= 10;
        ball->reset(_windowSizeX/2, _windowSizeY/2);
    }
    if (ball->bounced()) {
        _score += 1;
    }
}

void Game::render() {
    clearScreen();

    // Draw walls
    for (int x = 0; x < _windowSizeX; x++) {
        gotoxy(x, 0); std::cout << "-";
        gotoxy(x, _windowSizeY-1); std::cout << "-";
    }
    if (_isRightWall) {
        for (int y = 0; y < _windowSizeY; y++) {
            gotoxy(_windowSizeX-1, y); std::cout << "|";
        }
    }

    // Draw paddle and ball
    paddle->draw();
    ball->draw();

    // Score
    gotoxy(0, _windowSizeY);
    std::cout << "Score: " << _score << std::flush;
}
