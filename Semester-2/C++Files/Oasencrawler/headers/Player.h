#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
  int x, y, health, score;

  Player(int newX, int newY);
  bool move(char direction, std::string &error);
};

#endif // !PLAYER_H
