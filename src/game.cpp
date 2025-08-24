#include "game.hpp"
#include "utils.hpp"
#include "color.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

Game::Game(int w, int h)
    : width(w), height(h),
      player1(2, h/2 - 2, 4, 1, BLOCK_FULL),        // left paddle (length=4, width=1)
      player2(w - 3, h/2 - 2, 4, 1, BLOCK_FULL),    // right paddle
      ball(w/2, h/2, 1, 1, BALL_SOLID),
      running(true)
{
    player1.setWindowLimits(width, height);
    player2.setWindowLimits(width, height);
    ball.setWindowLimits(width, height);

    player1.setColor(TextColor::BRIGHT_CYAN);
    player2.setColor(TextColor::BRIGHT_BLUE);
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
        this_thread::sleep_for(chrono::milliseconds(50)); // ~20 fps
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
    ball.update(player1, player2, width, height); // dt=1 for now

    XYPosition ballPos = ball.getPosition();
    // XYPosition p1Pos = player1.getPosition();
    // XYPosition p2Pos = player2.getPosition();

    if (ballPos.x <= 0) {
        score2++;
        resetBall();
    } else if (ballPos.x >= width - 1) {
        score1++;
        resetBall();
    }
}

void Game::render() {
    clearTerminal();

    setTextColor(TextColor::GRAY);

    for (int x = 0; x < width; x++) {
        moveCursor(x, 0);
        cout << SYMBOL_DOUBLE_HORIZONTAL; // top wall
        moveCursor(x, height - 1);
        cout << SYMBOL_DOUBLE_HORIZONTAL; // bottom wall
    }

    for (int y = 0; y < height; y++) {
        moveCursor(0, y);
        cout << SYMBOL_DOUBLE_VERTICAL; // left wall
        moveCursor(width - 1, y);
        cout << SYMBOL_DOUBLE_VERTICAL; // right wall
        if (y > 0 && y < height - 1) {
            moveCursor(width / 2, y);
            cout << SYMBOL_VERTICAL; // center line
        }
    }

    resetTextColor();

    // XYPosition ballPos = ball.getPosition();
    // XYPosition p1Pos = player1.getPosition();
    // XYPosition p2Pos = player2.getPosition();

    // for (int y = 0; y < height; y++) {
    //     for (int x = 0; x < width; x++) {
    //         if (y == 0 || y == height - 1) {
    //             cout << "#"; // top/bottom walls
    //         } else if (x == 0 || x == width - 1) {
    //             cout << "#"; // left/right walls
    //         } else if (x == (int)ballPos.x && y == (int)ballPos.y) {
    //             cout << "O"; // ball
    //         } else if (x == (int)p1Pos.x &&
    //                    y >= (int)p1Pos.y && y < (int)p1Pos.y + player1.getLength()) {
    //             cout << "|"; // player 1 paddle
    //         } else if (x == (int)p2Pos.x &&
    //                    y >= (int)p2Pos.y && y < (int)p2Pos.y + player2.getLength()) {
    //             cout << "|"; // player 2 paddle
    //         } else {
    //             cout << " ";
    //         }
    //     }
    //     cout << "\n";
    // }
}

void Game::resetBall() {
     ball.reset(width / 2, height / 2);
}
