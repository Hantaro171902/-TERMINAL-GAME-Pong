#include "game.hpp"
#include "utils.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Game::Game(int w, int h)
    : width(w), height(h),
      player1(w, h, 4, 1, "█"),        // left paddle (length=4, width=1)
      player2(w, h, 4, 1, "█"),        // right paddle
      ball(w, h, 1, 1, "●")            // ball (1x1)
{
    player1.setPosition(2, h / 2 - 2);
    player2.setPosition(w - 3, h / 2 - 2);
    ball.setPosition(w / 2, h / 2);
    running = true;
}

void Game::run() {
    while (running) {
        processInput();
        update();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // ~20 fps
    }
}

void Game::processInput() {
    if (kbhit()) {                      // ✅ utils.hpp
        char ch = getch();              // ✅ utils.hpp
        switch (ch) {
            // Player 1: W/S
            case 'w': player1.moveUp(); break;
            case 's': player1.moveDown(); break;

            // Player 2: Up/Down arrows
            case 72: player2.moveUp(); break;    // up arrow
            case 80: player2.moveDown(); break;  // down arrow

            // Quit
            case 'q': running = false; break;
        }
    }
}

void Game::update() {
    ball.update(1.0f); // dt=1 for now

    XYPosition ballPos = ball.getPosition();
    XYPosition p1Pos = player1.getPosition();
    XYPosition p2Pos = player2.getPosition();

    // Ball collision with player 1
    if ((int)ballPos.x == (int)p1Pos.x + 1) {
        if ((int)ballPos.y >= (int)p1Pos.y &&
            (int)ballPos.y <= (int)p1Pos.y + player1.getLength()) {
            ball.bounceHorizontal();
        }
    }

    // Ball collision with player 2
    if ((int)ballPos.x == (int)p2Pos.x - 1) {
        if ((int)ballPos.y >= (int)p2Pos.y &&
            (int)ballPos.y <= (int)p2Pos.y + player2.getLength()) {
            ball.bounceHorizontal();
        }
    }

    // Ball goes out of bounds → reset
    if (ballPos.x <= 0 || ballPos.x >= width - 1) {
        resetBall();
    }
}

void Game::render() {
    system("clear"); // use "cls" on Windows, "clear" on Linux/mac

    XYPosition ballPos = ball.getPosition();
    XYPosition p1Pos = player1.getPosition();
    XYPosition p2Pos = player2.getPosition();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height - 1) {
                std::cout << "#"; // top/bottom walls
            } else if (x == 0 || x == width - 1) {
                std::cout << "#"; // left/right walls
            } else if (x == (int)ballPos.x && y == (int)ballPos.y) {
                std::cout << "O"; // ball
            } else if (x == (int)p1Pos.x &&
                       y >= (int)p1Pos.y && y < (int)p1Pos.y + player1.getLength()) {
                std::cout << "|"; // player 1 paddle
            } else if (x == (int)p2Pos.x &&
                       y >= (int)p2Pos.y && y < (int)p2Pos.y + player2.getLength()) {
                std::cout << "|"; // player 2 paddle
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

void Game::resetBall() {
    ball = Ball(width, height, 1, 1, "●");
    ball.setPosition(width / 2, height / 2);
}
