#include <iostream>
#include <vector>
#include <execution>
#include <string>

int main() {
    std::vector<std::string> doors = { "red", "green", "blue" };
    std::vector<std::string> possibilities;

    // Parallelisierte Transformation
    std::for_each(std::execution::par, doors.begin(), doors.end(), [&](const std::string& door) {
        possibilities.push_back(door + " heads");
        possibilities.push_back(door + " tails");
    });

    // Ausgabe
    std::cout << "Doors and Coin Possibilities:\n";
    for (const auto& possibility : possibilities) {
        std::cout << possibility << "\n";
    }

    return 0;
}
