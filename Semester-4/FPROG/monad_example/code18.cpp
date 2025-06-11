#include <iostream>
#include <vector>
#include <string>
#include <tuple>

// Typdefinition für einen Würfel
using Dice = std::vector<int>;

// Funktion zur Generierung aller Kombinationen von zwei Würfeln
std::vector<std::tuple<int, int>> generateCombinations(const Dice& dice1, const Dice& dice2) {
    std::vector<std::tuple<int, int>> combinations;
    for (int value1 : dice1) {
        for (int value2 : dice2) {
            combinations.emplace_back(value1, value2);
        }
    }
    return combinations;
}

// Funktion zur Ausgabe der Kombinationen
void printCombinations(const std::vector<std::tuple<int, int>>& combinations, const std::string& diceNames) {
    std::cout << "Combinations for " << diceNames << ":\n";
    for (const auto& [value1, value2] : combinations) {
        std::cout << "(" << value1 << ", " << value2 << ")\n";
    }
    std::cout << "\n";
}

int main() {
    // Definition der Würfel
    Dice redDice = {4, 4, 4, 4, 4, 1};
    Dice blueDice = {6, 3, 3, 3, 3, 3};
    Dice greenDice = {5, 5, 5, 2, 2, 2};

    // Kombinationen generieren
    auto redBlueCombinations = generateCombinations(redDice, blueDice);
    auto redGreenCombinations = generateCombinations(redDice, greenDice);
    auto blueGreenCombinations = generateCombinations(blueDice, greenDice);

    // Kombinationen ausgeben
    printCombinations(redBlueCombinations, "Red vs Blue");
    printCombinations(redGreenCombinations, "Red vs Green");
    printCombinations(blueGreenCombinations, "Blue vs Green");

    return 0;
}
