#include "../h/Character.h"
#include "iostream"

Character::Character() { std::cout << "Hello World" << std::endl; }
Character::Character(int newX, int newY) {
  x = newX;
  y = newY;
}

void Character::move(char direction) {
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

bool Character::validateCoordinates(int coordinate) const {
  return coordinate >= 0 && coordinate <= 9;
}

void Character::setX(int newX) {
  if (!validateCoordinates(newX))
    return;
  x = newX;
}

void Character::setY(int newY) {
  if (!validateCoordinates(newY))
    return;
  y = newY;
}

int Character::getX() const { return this->x; }
int Character::getY() const { return this->y; }
