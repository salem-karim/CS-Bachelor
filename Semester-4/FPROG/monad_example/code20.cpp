#include <iostream>
#include <vector>
#include <string>
#include <tuple>

// Typdefinition für einen Würfel
using Dice = std::vector<int>;

// Funktion zur Generierung aller Kombinationen von zwei Würfeln
void compareDice(const Dice& dice1, const Dice& dice2, const std::string& diceNames) {
    int wins1 = 0, wins2 = 0;

    std::cout << "Comparisons for " << diceNames << ":\n";
    for (int value1_1 : dice1) {
        for (int value1_2 : dice1) {
            for (int value2_1 : dice2) {
                for (int value2_2 : dice2) {
                    int sum1 = value1_1 + value1_2;
                    int sum2 = value2_1 + value2_2;

                    if (sum1 > sum2) {
                        ++wins1;
                        std::cout << "(" << sum1 << ", " << sum2 << ") - " << diceNames.substr(0, diceNames.find(" vs ")) << " wins\n";
                    } else if (sum1 < sum2) {
                        ++wins2;
                        std::cout << "(" << sum1 << ", " << sum2 << ") - " << diceNames.substr(diceNames.find("vs ") + 3) << " wins\n";
                    } else {
                        std::cout << "(" << sum1 << ", " << sum2 << ") - Draw\n";
                    }
                }
            }
        }
    }

    std::cout << "\nTotal Wins:\n";
    std::cout << diceNames.substr(0, diceNames.find(" vs ")) << ": " << wins1 << "\n";
    std::cout << diceNames.substr(diceNames.find("vs ") + 3) << ": " << wins2 << "\n\n";
}

int main() {
    // Definition der Würfel
    Dice redDice = {4, 4, 4, 4, 4, 1};
    Dice blueDice = {6, 3, 3, 3, 3, 3};
    Dice greenDice = {5, 5, 5, 2, 2, 2};

    // Vergleiche durchführen
    compareDice(redDice, blueDice, "Red vs Blue");
    compareDice(redDice, greenDice, "Red vs Green");
    compareDice(blueDice, greenDice, "Blue vs Green");

    return 0;
}
