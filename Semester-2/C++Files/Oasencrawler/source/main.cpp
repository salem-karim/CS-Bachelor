#include "../headers/Enemy.h"
#include "../headers/Player.h"
#include "../headers/World.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

void printWorld(World *world, Player *player, Enemy *enemy);

int main() {
  srand(time(0)); // Seed the random number generator
  Player *myPlayer = new Player(0, 0);
  World *myWorld = new World();
  Enemy *myEnemy = new Enemy();
  myEnemy->placeEnemy(myPlayer);
  do {
    myWorld->initializeWorld(myPlayer);
  } while (!(myWorld->checkRelics(myWorld)));
  string message = " ", error = " ", damage = " ";
  char input = ' ';
  while (true) {
    system("clear");
    cout << "press x to end" << endl;
    printWorld(myWorld, myPlayer, myEnemy);
    cout << "Health: " << myPlayer->health << " Score: " << myPlayer->score
         << endl;
    if (!error.empty() || !(message.empty())) {
      cout << damage << ' ' << message << endl;
      cout << error << endl;
      message = " ";
      error = " ";
      damage = " ";
    }
    cin >> input;
    if (myPlayer->move(myWorld, input, error)) {
      continue;
    }
    damage = myEnemy->followPlayer(myWorld, myPlayer);
    myWorld->applyField(myWorld, myPlayer, message);
    if (input == 'x' || myPlayer->health == 0) {
      cout << "Game Over!"
           << " | Your Score was: " << myPlayer->score << endl;
      break;
    } else if (!(myWorld->checkRelics(myWorld))) {
      myWorld->size++;
      do {
        myWorld->initializeWorld(myPlayer);
      } while (!(myWorld->checkRelics(myWorld)));
      myEnemy->placeEnemy(myPlayer);
    }
  }
  delete myEnemy;
  delete myWorld;
  delete myPlayer;
  return 0;
}

void printWorld(World *world, Player *player, Enemy *enemy) {
  for (int y = 0; y < world->size; ++y) {
    for (int x = 0; x < world->size; ++x) {
      cout << ' ';
      if (player->x == x && player->y == y && enemy->x == x && enemy->y == y)
        cout << ' ' << 'E' << 'P';
      else if (player->x == x && player->y == y)
        cout << ' ' << 'P' << ' ';
      else if (enemy->x == x && enemy->y == y)
        if (world->grid[x][y] != '-')
          cout << ' ' << 'E' << world->grid[x][y];
        else
          cout << ' ' << 'E' << ' ';
      else
        cout << ' ' << world->grid[x][y] << ' ';
    }
    cout << endl;
  }
}
