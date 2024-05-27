#pragma once
#ifndef _SPIEL_HPP_
#define _SPIEL_HPP_

#include "../Schiff/Schiff.hpp"
// #nclude "../Welt/Welt.hpp"
#include <array>
#include <vector>

class Spiel {
public:
  void spielStart();
  void spielLoop();
  void spielRunde();
  void spielEnde();
  void flotteErstellen();

  void setSchiff(Schiff schiff, int index, int player);
  Schiff getSchiff(int index, int player);
  // void setWelt(Welt welt);
  // Welt getWelt();

private:
  std::array<std::vector<Schiff>, 2> Flotten;
  // Welt spielFeld;
};

#endif
