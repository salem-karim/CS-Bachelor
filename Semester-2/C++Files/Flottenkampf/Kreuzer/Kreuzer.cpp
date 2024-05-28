#include "Kreuzer.hpp"
#include <iostream>
#include <random>

void Kreuzer::attack(ISchiff *Gegner) {
  while (!Gegner->getIsSunk()) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    int random = dis(gen);

    if (random >= Gegner->getGroesse()) {
      Gegner->setHuelle(Gegner->getHuelle() - getSchaden());

      if (Gegner->getHuelle() <= 0) {
        Gegner->setIsSunk(true);
        std::cout << "Destroyed" << std::endl;
      } else {
        // If the attack was successful but the enemy is not yet sunk, continue
        // attacking
        continue;
      }
    } else {
      std::cout << "Missed" << std::endl;
      break;
    }
  }
}
