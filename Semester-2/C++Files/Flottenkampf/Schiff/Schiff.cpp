#include "Schiff.hpp"

int Schiff::getHuelle() const { return Huelle; }
int Schiff::getSchaden() const { return Schaden; }
int Schiff::getGroesse() const { return Groesse; }
bool Schiff::getIsSunk() const { return isSunk; }
void Schiff::setx(int value) { x = value; }
void Schiff::sety(int value) { x = value; }
void Schiff::setHuelle(int value) { Huelle = value; }
void Schiff::setSchaden(int value) { Schaden = value; }
void Schiff::setGroesse(int value) { Groesse = value; }
int Schiff::getx() const { return x; }
int Schiff::gety() const { return y; }
void Schiff::setIsSunk(bool value) { isSunk = value; }
Schiff::Schiff(int shell, int size, int damage) {
  Huelle = shell;
  Groesse = size;
  Schaden = damage;
}
