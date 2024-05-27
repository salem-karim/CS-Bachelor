#include "Schiff.hpp"

int Schiff::getHuelle() const { return Huelle; }
int Schiff::getSchaden() const { return Schaden; }
int Schiff::getGroesse() const { return Groesse; }
void Schiff::setHuelle(int value) { Huelle = value; }
void Schiff::setSchaden(int value) { Schaden = value; }
void Schiff::setGroesse(int value) { Groesse = value; }
Schiff::Schiff(int shell, int size, int damage) {
  Huelle = shell;
  Groesse = size;
  Schaden = damage;
}
void Schiff::shoot() {}
