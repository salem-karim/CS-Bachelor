#include "Spiel.hpp"
#include "../Jaeger/Jaeger.hpp"
#include "../Kreuzer/Kreuzer.hpp"
#include "../Zerstoerer/Zerstoerer.hpp"
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <stdexcept>

using namespace std;

void Spiel::spielStart() {
  flotteErstellen();
  spielLoop();
}

void Spiel::spielLoop() {
  bool gameOver = false;
  char input;
  do {
    // Check if any player's fleet is completely sunk
    for (int i = 0; i < 2; i++) {
      gameOver = true;
      for (const auto &schiff : Flotten.at(i)) {
        if (!schiff->getIsSunk()) {
          gameOver = false;
          break;
        }
      }
      if (gameOver)
        break;
    }
    if (gameOver)
      break;
    spielFeld->printWelt(Flotten);
    cout << "Runde Spielen? (y/n)" << endl;
    try {
      cin >> input;
      if (cin.fail()) { // Check if the input is not a character
        cin.clear();    // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw invalid_argument("Eingabe muss ein Buchstabe sein.");
      }
      if (input != 'y' && input != 'n') {
        cout << "Bitte 'y' oder 'n' eingeben" << endl;
      }
      if (input == 'y') {
        spielRunde();
      } else if (input == 'n') {
        break; // Exit the loop if player chooses 'n'
      }
    } catch (const invalid_argument &e) {
      cout << e.what() << endl;
    }
  } while (input != 'n');
}
void Spiel::spielRunde() {
  // Change which Player Shoots and which ship to attack by random device
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(0, 1);
  int player = dis(gen);

  uniform_int_distribution<> dis2(0, Flotten.at(player).size() - 1);
  int ship = dis2(gen);

  int target;
  bool targetFound = false;

  // Keep generating new targets until a non-sunk ship is found
  while (!targetFound) {
    uniform_int_distribution<> dis3(0, Flotten.at(1 - player).size() - 1);
    target = dis3(gen);

    // Check if the target ship is not sunk
    if (!Flotten.at(1 - player).at(target)->getIsSunk()) {
      targetFound = true;
    }
  }

  // Attack the non-sunk target ship
  Flotten.at(player).at(ship)->attack(Flotten.at(1 - player).at(target).get());

  // cout which player attacks with which ship for both players
  cout << "Spieler " << player + 1 << " greift mit Schiff " << ship
       << " Spieler " << 1 - player + 1 << " GegnerSchiff " << target << endl;
}

void Spiel::spielEnde() {
  int sunkenShips[2] = {0, 0};
  for (int i = 0; i < 2; i++) {
    for (const auto &schiff : Flotten.at(i)) {
      if (schiff->getIsSunk()) {
        sunkenShips[i]++;
      }
    }
  }
  cout << "Spieler 1 hat " << sunkenShips[1] << " Schiffe versenkt." << endl;
  cout << "Spieler 2 hat " << sunkenShips[0] << " Schiffe versenkt." << endl;
  if (sunkenShips[1] > sunkenShips[0]) {
    cout << "Spieler 1 hat gewonnen!" << endl;
  } else if (sunkenShips[1] < sunkenShips[0]) {
    cout << "Spieler 2 hat gewonnen!" << endl;
  } else {
    cout << "Unentschieden!" << endl;
  }
}

void Spiel::flotteErstellen() {
  int length = 0;
  int type = 0;

  for (int i = 0; i < 2; i++) {
    do {
      cout << "Größe der Flotte(1-9) von Spieler " << i + 1 << ": ";
      try {
        cin >> length;
        if (cin.fail()) { // Check if the input is not an integer
          cin.clear();    // Clear the error flag
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          throw invalid_argument("Eingabe muss eine ganze Zahl sein.");
        }
        if (length < 1 || length > 9) {
          cout << "Bitte eine Zahl zwischen 1 und 9 eingeben" << endl;
        }
      } catch (const invalid_argument &e) {
        cout << e.what() << endl;
      }
    } while (length < 1 || length > 9);

    try {
      Flotten.at(i).resize(length);
    } catch (const out_of_range &) {
      throw runtime_error("Error: Out of range access to Flotten array.");
    }

    for (int j = 0; j < length; j++) {
      do {
        cout << "Schiff " << j + 1 << " von " << length << endl;
        cout << "(1)Jäger, (2)Zerstörer, 3)Kreuzer: ";
        try {
          cin >> type;
          if (cin.fail()) { // Check if the input is not an integer
            cin.clear();    // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw invalid_argument("Eingabe muss eine ganze Zahl sein.");
          }
          if (type < 1 || type > 3) {
            cout << "Bitte eine Zahl zwischen 1 und 3 eingeben" << endl;
          }
        } catch (const invalid_argument &e) {
          cout << e.what() << endl;
        }
      } while (type < 1 || type > 3);

      try {
        switch (type) {
        case 1:
          Flotten.at(i).at(j) = make_unique<Jaeger>();
          break;
        case 2:
          Flotten.at(i).at(j) = make_unique<Zerstoerer>();
          break;
        case 3:
          Flotten.at(i).at(j) = make_unique<Kreuzer>();
          break;
        default:
          break;
        }
      } catch (const out_of_range &) {
        throw runtime_error("Error: Out of range access to Flotten array.");
      }
    }
  }
  flottenInitialisieren();
}

void Spiel::flottenInitialisieren() {
  random_device rd;
  mt19937 gen(rd());

  // Use an array of size 2, where each element is a vector<int>
  array<vector<int>, 2> placedShips;

  for (int player = 0; player < 2; ++player) {
    for (auto &schiff : Flotten.at(player)) {
      bool isPlaced = false;

      while (!isPlaced) {
        int x, y;

        // Choose a random position
        int gridSize = spielFeld->getGrid().size();
        uniform_int_distribution<> disX(0, gridSize - 1);
        uniform_int_distribution<> disY(0, gridSize - 1);
        x = disX(gen);
        y = disY(gen);

        // Check if the chosen position overlaps with any previously placed ship
        bool overlaps = false;
        for (const auto &placedShipPos : placedShips[1 - player]) {
          if (placedShipPos / gridSize == x && placedShipPos % gridSize == y) {
            overlaps = true;
            break;
          }
        }

        if (!overlaps) {
          schiff->setX(x);
          schiff->setY(y);
          placedShips[player].push_back(
              x * gridSize + y); // Add the ship's position to the list
          isPlaced = true;
        }
      }
    }
  }
}

Spiel::Spiel() { spielFeld = make_shared<Welt>(); }
