#include "game.hpp"
#include "utils.hpp"
#include <iostream>
#include <chrono>
#include <thread>

Game::Game(int w, int h)
    : width(w), height(h),
      player1(2, h / 2 - 2, 4, h),  // left paddle
      player2(w - 3, h / 2 - 2, 4, h),  // right paddle
      ball(w / 2, h / 2, w, h) {
    running = true;
}

void Game::run() {
    while (running) {
        processInput();
        update();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 20 fps
    }
}

void Game::processInput() {
    if (_kbhit()) {
        char ch = _getch();
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
    ball.move();

    // Ball collision with paddles
    if (ball.getX() == player1.getX() + 1) {
        if (ball.getY() >= player1.getY() && ball.getY() <= player1.getY() + player1.getLength()) {
            ball.bounceHorizontal();
        }
    }

    if (ball.getX() == player2.getX() - 1) {
        if (ball.getY() >= player2.getY() && ball.getY() <= player2.getY() + player2.getLength()) {
            ball.bounceHorizontal();
        }
    }

    // Ball goes out of bounds → reset
    if (ball.getX() <= 0 || ball.getX() >= width - 1) {
        resetBall();
    }
}

void Game::render() {
    system("cls"); // Windows clear screen

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height - 1) {
                std::cout << "#"; // top/bottom walls
            } else if (x == 0 || x == width - 1) {
                std::cout << "#"; // left/right walls
            } else if (x == ball.getX() && y == ball.getY()) {
                std::cout << "O"; // ball
            } else if (x == player1.getX() && y >= player1.getY() && y < player1.getY() + player1.getLength()) {
                std::cout << "|"; // player 1 paddle
            } else if (x == player2.getX() && y >= player2.getY() && y < player2.getY() + player2.getLength()) {
                std::cout << "|"; // player 2 paddle
            } else {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

void Game::resetBall() {
    ball = Ball(width / 2, height / 2, width, height);
}
