#include "Welt.hpp"
#include <array>
#include <vector>

typedef std::array<std::vector<std::shared_ptr<Schiff>>, 2> Flotten;

std::vector<std::vector<char>> Welt::getGrid() const { return grid; }
void Welt::setField(char Field, int x, int y) { grid.at(x).at(y) = Field; }
void Welt::printWelt(Flotten) {}
