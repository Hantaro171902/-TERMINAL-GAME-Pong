#include "game.hpp"
#include "utils.hpp"
#include "color.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

Game::Game(int w, int h)
    : width(w)
    , height(h)
    , player1(2, h / 2 - 2, 4, 1, BLOCK_FULL)
    , player2(w - 3, h / 2 - 2, 4, 1, BLOCK_FULL)
    , ball(w / 2, h / 2, 1, 1, BALL_SOLID)
{
    player1.setWindowLimits(width, height);
    player2.setWindowLimits(width, height);
    ball.setWindowLimits(width, height);
    
    player1.setColor(TextColor::BRIGHT_BLUE);
    player2.setColor(TextColor::BRIGHT_CYAN);
    ball.setColor(TextColor::BRIGHT_YELLOW);

    clearScreen();
    hideCursor();
}

Game::~Game() {
    showCursor();
    resetTextColor();
    clearTerminal();
}

void Game::run() {
    drawBoundary();
    while (running) {
        processInput();
        update();
        render();
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void Game::processInput() {
    InputKey key = getInputKey();
    switch (key) {
        case InputKey::P1_UP:
            player1.moveUp();
            break;
        case InputKey::P1_DOWN:
            player1.moveDown();
            break;
        case InputKey::P2_UP:
            player2.moveUp();
            break;
        case InputKey::P2_DOWN:
            player2.moveDown();
            break;
        case InputKey::Q:
        case InputKey::ESC:
            running = false;
            break;
        default:
            break;
    }
}

void Game::update() {
    ball.updateBall(player1, player2, width, height);

    XYPosition ballPos = ball.getPosition();

    if (ballPos.x <= 0) {
        score2++;
        resetBall();
    } else if (ballPos.x >= width - 1) {
        score1++;
        resetBall();
    }
}

void Game::render() {

    clearScreen();
    player1.clear();
    player2.clear();
    ball.clear();

    player1.draw();
    player2.draw();
    ball.draw();

    moveCursor(width / 2 - 2, 1);
    setTextColor(TextColor::BRIGHT_WHITE);
    cout << score1 << " : " << score2;
    resetTextColor();
    cout.flush();
}

void Game::drawBoundary() const {
    setTextColor(TextColor::GRAY);
    for (int x = 0; x < width; ++x) {
        moveCursor(x, 0);
        cout << SYMBOL_DOUBLE_HORIZONTAL;
        moveCursor(x, height - 1);
        cout << SYMBOL_DOUBLE_HORIZONTAL;
    }
    for (int y = 0; y < height; ++y) {
        moveCursor(0, y);
        cout << SYMBOL_DOUBLE_VERTICAL;
        moveCursor(width - 1, y);
        cout << SYMBOL_DOUBLE_VERTICAL;
        if (y > 0 && y < height - 1) {
            moveCursor(width / 2, y);
            cout << SYMBOL_VERTICAL;
        }
    }
    resetTextColor();
}

void Game::resetBall() {
    ball.reset(width / 2, height / 2);
}