#include "../headers/World.h"
#include <cstdlib>

void World::initializeWorld(Player *player) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int randomnum = rand() % 10;
      if (randomnum < 4) {
        grid[i][j] = '-';
      } else if (randomnum < 8) {
        grid[i][j] = 'x';
        int damagestep = rand() % 6;
        if (damagestep == 0) {
        }
      } else if (randomnum == 8) {
        grid[i][j] = '+';
      } else if (randomnum == 9) {
        grid[i][j] = '*';
      }
    }
  }
  grid[player->x][player->y] = '-';
}

bool World::checkRelics(World *world) {
  bool Relics = false;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (world->grid[i][j] == '*') {
        Relics = true;
      }
    }
  }
  return Relics;
}

void World::applyField(World *world, Player *player, std::string &message) {
  int randomnum = rand() % 6;

  if (world->grid[player->x][player->y] == 'x') {
    world->grid[player->x][player->y] = '-';
    if (randomnum == 0) {
      player->health -= 1;
      message = "You have been damaged!";
    }
  } else if (world->grid[player->x][player->y] == '+') {
    world->grid[player->x][player->y] = '-';
    player->health += 1;
    message = "You got 1 Healthpoint back!";
  } else if (world->grid[player->x][player->y] == '*') {
    world->grid[player->x][player->y] = '-';
    player->score += 1;
    message =
        "You found a Relic!\nyour score is: " + std::to_string(player->score);
  }
}
