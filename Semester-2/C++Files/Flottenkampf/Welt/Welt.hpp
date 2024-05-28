#pragma once
#ifndef _WELT_HPP_
#define _WELT_HPP_

#include "../Schiff/Schiff.hpp"
#include <memory>
#include <vector>

typedef std::array<std::vector<std::shared_ptr<Schiff>>, 2> Flotten;

class Welt {
public:
  void printWelt(Flotten);
  std::vector<std::vector<char>> getGrid() const;
  void setField(char Field, int x, int y);

private:
  std::vector<std::vector<char>> grid;
};

#endif
