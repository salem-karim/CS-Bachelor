#pragma once
#include <memory>
#ifndef _SPIEL_HPP_
#define _SPIEL_HPP_

#include "../Schiff/Schiff.hpp"
#include "../Welt/Welt.hpp"
#include <array>
#include <vector>

class Spiel {
public:
  void spielStart();
  void spielLoop();
  void spielRunde();
  void spielEnde();
  void flotteErstellen();

  void printShips();

  void setSchiff(Schiff schiff, int index, int player);
  Schiff getSchiff(int index, int player) const;
  // void setWelt(std::shared_ptr<Welt> welt);
  Welt getWelt() const;

private:
  std::array<std::vector<std::shared_ptr<Schiff>>, 2> Flotten;
  std::shared_ptr<Welt> spielFeld;
};

#endif
