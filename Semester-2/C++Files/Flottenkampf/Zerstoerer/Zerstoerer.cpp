#include "Zerstoerer.hpp"
#include <iostream>
#include <random>

void Zerstoerer::attack(ISchiff *Gegner) {
  if (Gegner->getIsSunk()) {
    std::cout << "The enemy ship is already destroyed" << std::endl;
    return;
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 10);
  int random = dis(gen);
  if (random >= (Gegner->getGroesse() - 2)) {
    Gegner->setHuelle((Gegner->getHuelle() - getSchaden()));
    if (Gegner->getHuelle() <= 0) {
      Gegner->setIsSunk(true);
      std::cout << "Destroyed" << std::endl;
      return;
    }
  } else {
    std::cout << "Missed" << std::endl;
  }
}
