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
    , player1(4, h / 2 - 2, 4, 1, BLOCK_FULL)
    , player2(w - 3, h / 2 - 2, 4, 1, BLOCK_FULL)
    , ball(w / 2, h / 2, 1, 1, BALL_SOLID)
{
    player1.setWindowLimits(width, height);
    player2.setWindowLimits(width, height);
    ball.setWindowLimits(width, height);

    // Set horizontal limits for each paddle
    player1.setXLimits(1, width / 2 - 2);
    player2.setXLimits(width / 2 + 1, width - 2);
    
    player1.setColor(TextColor::BRIGHT_BLUE);
    player2.setColor(TextColor::BRIGHT_CYAN);
    ball.setColor(TextColor::BRIGHT_YELLOW);

    clearScreen();
    hideCursor();
}

Game::~Game() {
    showCursor();
    resetTextColor();
    clearScreen();
}

void Game::run() {
     // Time tracking for smoother movement
    auto prevTime = chrono::high_resolution_clock::now();
    drawBoundary();

    while (running) {
        auto currentTime = chrono::high_resolution_clock::now();
        float deltaTime = chrono::duration<float>(currentTime - prevTime).count();
        prevTime = currentTime;

        processInput();
        update(deltaTime); // Pass deltaTime to update
        render();

        this_thread::sleep_for(chrono::milliseconds(20)); // Adjust for desired frame rate
    }
}

void Game::isWinner() {
    if (score1 >= 10) {
        moveCursor(width / 2 - 5, height / 2);
        setTextColor(TextColor::BRIGHT_GREEN);
        cout << "Player 1 Wins!";
        resetTextColor();
        cout.flush();
        this_thread::sleep_for(chrono::seconds(3));
        running = false;
    } else if (score2 >= 10) {
        moveCursor(width / 2 - 5, height / 2);
        setTextColor(TextColor::BRIGHT_GREEN);
        cout << "Player 2 Wins!";
        resetTextColor();
        cout.flush();
        this_thread::sleep_for(chrono::seconds(3));
        running = false;
    }
}

void Game::processInput() {
    InputKey key = getInputKey();

    // Reset velocities
    player1.setVelocityY(0.0f);
    player1.setVelocityX(0.0f);
    player2.setVelocityY(0.0f);
    player2.setVelocityX(0.0f);

    switch (key) {
        case InputKey::P1_UP:
            player1.moveUp();
            break;
        case InputKey::P1_DOWN:
            player1.moveDown();
            break;
        case InputKey::P1_LEFT:
            player1.moveLeft();
            break;
        case InputKey::P1_RIGHT:
            player1.moveRight();
            break;
        case InputKey::P2_UP:
            player2.moveUp();
            break;
        case InputKey::P2_DOWN:
            player2.moveDown();
            break;
        case InputKey::P2_LEFT:
            player2.moveLeft();
            break;
        case InputKey::P2_RIGHT:
            player2.moveRight();
            break;
        case InputKey::Q:
        case InputKey::ESC:
            running = false;
            break;
        default:
            break;
    }
}

void Game::update(float deltaTime) {
    player1.update(deltaTime);
    player2.update(deltaTime);
    ball.updateBall(player1, player2, width, height);

    XYPosition ballPos = ball.getPosition();

    if (ballPos.x <= 0) {
        score2++;
        resetBall();
    } else if (ballPos.x >= width - 1) {
        score1++;
        resetBall();
    }

    // Check winner
    isWinner();
}

void Game::render() {
    clearTerminal();

    drawBoundary();
    // clearScreen();
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
    setTextColor(TextColor::BRIGHT_WHITE);

    // Top border
    moveCursor(-1, 0);
    cout << SYMBOL_DOUBLE_TOP_LEFT;
    for (int x = 1; x < width - 1; ++x) {
        cout << SYMBOL_DOUBLE_HORIZONTAL;
    }
    cout << SYMBOL_DOUBLE_TOP_RIGHT;

    // Bottom border
    moveCursor(0, height - 1);
    cout << SYMBOL_DOUBLE_BOTTOM_LEFT;
    for (int x = 1; x < width - 1; ++x) {
        cout << SYMBOL_DOUBLE_HORIZONTAL;
    }
    cout << SYMBOL_DOUBLE_BOTTOM_RIGHT;

    // Side border and center line
    for (int y = 0; y < height - 1; ++y) {
        // Left side
        moveCursor(0, y);
        cout << SYMBOL_DOUBLE_VERTICAL;

        // Right side
        moveCursor(width, y);
        cout << SYMBOL_DOUBLE_VERTICAL;

        // Center line
        moveCursor(width / 2, y);
        cout << SYMBOL_VERTICAL;
    }
    resetTextColor();
}

void Game::resetBall() {
    ball.reset(width / 2, height / 2);
}