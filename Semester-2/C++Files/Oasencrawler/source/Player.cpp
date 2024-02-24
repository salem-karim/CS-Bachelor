#include "../headers/Player.h"
#include <iostream>

Player::Player(int newX, int newY) {
  x = newX;
  y = newY;
}

void Player::move(char direction) {
  switch (direction) {
  case 'W':
  case 'w':
    y--;
    break;
  case 'A':
  case 'a':
    x--;
    break;
  case 'S':
  case 's':
    y++;
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
