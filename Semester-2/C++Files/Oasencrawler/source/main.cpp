#include "../headers/Player.h"
#include <iostream>

using namespace std;

int main() {
  Player *myPlayer = new Player(0, 0);

  char world[5][5];

  for (int x = 0; x < 5; ++x) {
    for (int y = 0; y < 5; ++y) {
      world[x][y] = '-';
    }
  }
  cout << "press x to end" << endl;
  char input = ' ';

  while (true) {
    cin >> input;
    myPlayer->move(input);

    for (int y = 0; y < 5; ++y) {
      for (int x = 0; x < 5; ++x) {
        cout << ' ';
        if (myPlayer->x == x && myPlayer->y == y)
          cout << ' ' << 'X' << ' ';
        else
          cout << ' ' << world[x][y] << ' ';
      }
      cout << endl;
    }

    if (input == 'x')
      break;
  }

  delete myPlayer;
  return 0;
}
