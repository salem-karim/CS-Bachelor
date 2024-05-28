#include "Kreuzer.hpp"
#include <iostream>
#include <random>

void Kreuzer::attack(ISchiff *Gegner) {
  int xd = std::abs(getX() - Gegner->getX());
  int yd = std::abs(getY() - Gegner->getY());
  // numbers from 0 to 17
  int distance = (xd + yd) - 1;
  double modifier = 1.0 / 17.0;
  // Modify the damage based on the distance
  double damageModifier = 1.0 / (1.0 + (distance * modifier));
  int modifiedDamage =
      static_cast<int>(std::round(damageModifier * getSchaden()));

  while (!Gegner->getIsSunk()) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    int random = dis(gen);

    if (random >= Gegner->getGroesse()) {
      Gegner->setHuelle(Gegner->getHuelle() - modifiedDamage);

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
