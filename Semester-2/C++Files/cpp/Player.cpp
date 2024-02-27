//
// Created by karim on 22.02.24.
//
#include "../h/Player.h"
#include "iostream"

Player::Player() { std::cout << "Hello World" << std::endl; }
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

bool Player::validateCoordinates(int coordinate) const {
  return coordinate >= 0 && coordinate <= 9;
}

void Player::setX(int newX) {
  if (!validateCoordinates(newX))
    return;
  x = newX;
}

void Player::setY(int newY) {
  if (!validateCoordinates(newY))
    return;
  y = newY;
}

int Player::getX() const { return this->x; }
int Player::getY() const { return this->y; }
