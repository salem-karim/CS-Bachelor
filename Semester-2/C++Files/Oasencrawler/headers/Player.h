#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class World;

class Player {
public:
  int x, y, health, score;

  Player(int x, int y);
  bool move(World *world, char direction, std::string &error);
};

#endif // !PLAYER_H
