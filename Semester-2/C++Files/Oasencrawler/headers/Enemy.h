#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class World;

class Enemy {
public:
  int x, y;
  void placeEnemy(Player *player);
  std::string followPlayer(World *world, Player *player);
  bool isClose(Player *player);
};

#endif // !ENEMY_H
