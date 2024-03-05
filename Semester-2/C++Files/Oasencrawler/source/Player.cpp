#include "../headers/Player.h"
#include "../headers/World.h"

Player::Player(int x, int y) : x(x), y(y) {
  health = 5;
  score = 0;
}

bool Player::move(World *world, char direction, std::string &error) {
  int dx = 0, dy = 0;
  switch (direction) {
  case 'W':
  case 'w':
    dy = -1;
    break;
  case 'A':
  case 'a':
    dx = -1;
    break;
  case 'S':
  case 's':
    dy = 1;
    break;
  case 'D':
  case 'd':
    dx = 1;
    break;
  case 'x':
    break;
  default:
    error = "Invalid input!";
    return true;
  }

  if ((0 <= (this->x + dx) && (this->x + dx) < world->size) &&
      (0 <= (this->y + dy) && (this->y + dy) < world->size)) {
    this->x += dx;
    this->y += dy;
  } else {
    error = "You can't move there!";
    return true;
  }
  return false;
}
