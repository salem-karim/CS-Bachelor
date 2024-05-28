#pragma once
#ifndef _WELT_HPP_
#define _WELT_HPP_

#include "../Schiff/Schiff.hpp"
#include <array>

class Welt {
public:
  Welt();
  void printWelt(Flotten Flotten);
  std::array<std::array<char, 10>, 10> getGrid() const;
  void setField(char Field, int x, int y);

private:
  std::array<std::array<char, 10>, 10> grid;
};

#endif
