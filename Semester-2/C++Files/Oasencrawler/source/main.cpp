#include "../headers/Player.h"
#include "../headers/World.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

void printWorld(World *world, Player *player);
void checkField(World *world, Player *player);

int main() {
  srand(time(0)); // Seed the random number generator
  Player *myPlayer = new Player(0, 0);
  World *myWorld = new World();
  do {
    myWorld->initializeWorld(myPlayer);
  } while (!(myWorld->checkRelics(myWorld)));
  string message = " ", error = " ";
  char input = ' ';
  while (true) {
    system("clear");
    cout << "press x to end" << endl;
    printWorld(myWorld, myPlayer);
    cout << "Health: " << myPlayer->health << " Score: " << myPlayer->score
         << endl;
    if (!error.empty() && !(message.empty())) {
      cout << message << endl;
      cout << error << endl;
      message = " ";
      error = " ";
    }
    cin >> input;
    if (myPlayer->move(input, error)) {
      continue;
    }
    myWorld->applyField(myWorld, myPlayer, message);
    if (input == 'x' || myPlayer->health == 0) {
      cout << "Game Over!"
           << " | Your Score was: " << myPlayer->score << endl;
      break;
    } else if (!(myWorld->checkRelics(myWorld))) {
      do {
        myWorld->initializeWorld(myPlayer);
      } while (!(myWorld->checkRelics(myWorld)));
    }
  }
  delete myWorld;
  delete myPlayer;
  return 0;
}

void printWorld(World *world, Player *player) {
  for (int y = 0; y < 5; ++y) {
    for (int x = 0; x < 5; ++x) {
      cout << ' ';
      if (player->x == x && player->y == y)
        cout << ' ' << 'P' << ' ';
      else
        cout << ' ' << world->grid[x][y] << ' ';
    }
    cout << endl;
  }
}
