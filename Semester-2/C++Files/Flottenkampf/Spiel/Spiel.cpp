#include "Spiel.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

void Spiel::spielStart() { flotteErstellen(); }
void Spiel::spielLoop() {}
void Spiel::spielRunde() {}
void Spiel::spielEnde() {}

void Spiel::flotteErstellen() {
  int length = 0;
  int type = 0;

  for (int i = 1; i <= 2; i++) {
    do {
      cout << "Größe der Flotte(1-9) von Spieler " << i << ": ";
      try {
        cin >> length;
        if (cin.fail()) { // Check if the input is not an integer
          cin.clear();    // Clear the error flag
          cin.ignore(numeric_limits<streamsize>::max(),
                     '\n'); // Discard invalid input
          throw invalid_argument("Eingabe muss eine ganze Zahl sein.");
        }
        if (length < 1 || length > 9) {
          cout << "Bitte eine Zahl zwischen 1 und 9 eingeben" << endl;
        }
      } catch (const invalid_argument &e) {
        cout << e.what() << endl;
      }
    } while (length < 1 || length > 9);

    Flotten[i].resize(length);
    for (int j = 0; j < length; j++) {
      do {
        cout << "Schiff " << j + 1 << " von " << length << endl;
        cout << "(1)Jäger, (2)Zerstörer, (3)Kreuzer : ";
        try {
          cin >> type;
          if (cin.fail()) { // Check if the input is not an integer
            cin.clear();    // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n'); // Discard invalid input
            throw invalid_argument("Eingabe muss eine ganze Zahl sein.");
          }
          if (type < 1 || type > 3) {
            cout << "Bitte eine Zahl zwischen 1 und 3 eingeben" << endl;
          }
        } catch (const invalid_argument &e) {
          cout << e.what() << endl;
        }
      } while (type < 1 || type > 3);
      // Set the ship type
    }
  }
}
