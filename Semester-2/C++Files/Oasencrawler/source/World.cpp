#include "../headers/World.h"
#include <cstdlib>
#include <ctime>

void World::initializeWorld() {

  srand(time(0)); // Seed the random number generator

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
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
}

bool World::checkRelics(World *world) {
  bool win = false;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (world->grid[i][j] == '*') {
        win = true;
      }
    }
  }
  return win;
}

void World::applyField(World *world, Player *player, std::string &message) {
  // srand(time(0));
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
        "You found a Relic! your score is: " + std::to_string(player->score);
  }
}
