#include "../h/Player.h"
#include <iostream>

using namespace std;

int main() {
  Player *myPlayer = new Player(0, 0);
  char input;

  char world[10][10];

  for (int x = 0; x < 10; ++x) {
    for (int y = 0; y < 10; ++y) {
      world[x][y] = '-';
    }
  }

  while (true) {
    cout << "press x to end" << endl;
    cin >> input;

    myPlayer->move(input);

    for (int y = 0; y < 10; ++y) {
      for (int x = 0; x < 10; ++x) {
        cout << ' ';
        if (myPlayer->getX() == x && myPlayer->getY() == y)
          cout << 'X';
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
