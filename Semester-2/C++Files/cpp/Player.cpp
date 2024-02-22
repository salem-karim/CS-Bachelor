//
// Created by karim on 22.02.24.
//
#include "iostream"
#include "../h/Player.h"

Player::Player() {
    std::cout << "Hello World" << std::endl;
}
Player::Player(int newX, int newY) {
    x = newX;
    y = newY;
}

void Player::move(char direction) {
    switch(direction) {
        case 'W':
        case 'w':
            y++;
            break;
        case 'A':
        case 'a':
            x--;
            break;
        case 'S':
        case 's':
            y--;
            break;
        case 'D':
        case 'd':
            x++;
            break;
        case 'x':
            break;
        default:
            std::cout << "Invalid Input!" << std::endl;
    }
}