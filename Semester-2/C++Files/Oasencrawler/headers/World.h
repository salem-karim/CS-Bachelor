#ifndef WORLD_H
#define WORLD_H

#include "Player.h"

class World {
public:
  char grid[5][5];
  void initializeWorld(Player *player);
  bool checkRelics(World *world);
  void applyField(World *world, Player *player, std::string &message);
};

#endif // !WORLD_H
