#include "../headers/Player.h"
#include "../headers/World.h"
#include <iostream>

using namespace std;

void printWorld(World *world, Player *player);
void checkField(World *world, Player *player);

int main() {
  Player *myPlayer = new Player(0, 0);
  World *myWorld = new World();
  do {
    myWorld->initializeWorld();
  } while (!(myWorld->checkRelics(myWorld)));
  string message = " ", error = " ";
  char input = ' ';
  while (true) {
    system("clear");
    cout << "press x to end" << endl;
    printWorld(myWorld, myPlayer);
    cout << "Health: " << myPlayer->health << " Score: " << myPlayer->score
         << endl;
    if (!error.empty()) {
      cout << error << endl;
    }
    if (!message.empty()) {
      cout << message << endl;
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
      printWorld(myWorld, myPlayer);
      cout << "You win!"
           << " | Your Score was: " << myPlayer->score << endl;
      break;
    }
    error = " ";
    message = " ";
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
        cout << ' ' << 'X' << ' ';
      else
        cout << ' ' << world->grid[x][y] << ' ';
    }
    cout << endl;
  }
}
