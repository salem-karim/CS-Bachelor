#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy {
public:
  int x, y;
  void placeEnemy(Player *player);
  void followPlayer(Player *player);
  bool isClose(Player *player);
};

#endif // !ENEMY_H
