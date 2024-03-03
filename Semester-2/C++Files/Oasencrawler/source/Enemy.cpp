#include "../headers/Enemy.h"
#include <cstdlib>

void Enemy::followPlayer(Player *player) {
  // Simple chasing behavior: Move towards the player on each axis
  if (x < player->x) {
    x++;
  } else if (x > player->x) {
    x--;
  }

  if (y < player->y) {
    y++;
  } else if (y > player->y) {
    y--;
  }
}

// check if Enemy is in sorunding of player

bool Enemy::isClose(Player *player) {
  // Get the distance of the player to the enemy
  int dx = std::abs(x - player->x);
  int dy = std::abs(y - player->y);
  return (dx <= 1 && dy <= 1);
}

void Enemy::placeEnemy(Player *player) {
  do {
    x = rand() % 5;
    y = rand() % 5;
  } while (isClose(player));
}
