#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <numeric>
#include <execution>
#include <mutex>

// Typdefinition für einen Würfel
using Dice = std::vector<int>;
using ResultPair = std::pair<int, int>;

// Funktion zur Generierung aller möglichen Kombinationen von Würfeln
void compareDice(const Dice& dice1, const Dice& dice2, const std::string& diceNames, int numDice) {
    int wins1 = 0, wins2 = 0;
    std::set<ResultPair> uniqueResults;
    std::mutex mutex;

    // Funktion, um alle möglichen Summen von Würfeln für eine gegebene Anzahl von Würfeln zu generieren
    auto generateSums = [&](const Dice& dice, int numDice) {
        std::vector<int> sums;
        std::function<void(int, int, int)> generate = [&](int currentSum, int depth, int startIndex) {
            if (depth == numDice) {
                sums.push_back(currentSum);
                return;
            }

            for (size_t i = startIndex; i < dice.size(); ++i) {
                generate(currentSum + dice[i], depth + 1, i);
            }
        };

        generate(0, 0, 0);
        return sums;
    };

    // Generiere Summen für beide Würfelsets
    auto sums1 = generateSums(dice1, numDice);
    auto sums2 = generateSums(dice2, numDice);

    // Parallelisierte Verarbeitung der Ergebnisse
    auto computeResults = [&](int sum1, int sum2) {
        std::lock_guard<std::mutex> lock(mutex);
        uniqueResults.emplace(sum1, sum2);
        if (sum1 > sum2) {
            ++wins1;
        } else if (sum1 < sum2) {
            ++wins2;
        }
    };

    std::for_each(std::execution::par, sums1.begin(), sums1.end(), [&](int sum1) {
        std::for_each(std::execution::par, sums2.begin(), sums2.end(), [&](int sum2) {
            computeResults(sum1, sum2);
        });
    });

    // Ergebnisse ausgeben
    std::cout << "Unique Comparisons for " << diceNames << " (" << numDice << " vs " << numDice << " dice):\n";
    for (const auto& [sum1, sum2] : uniqueResults) {
        if (sum1 > sum2) {
            std::cout << "(" << sum1 << ", " << sum2 << ") - " << diceNames.substr(0, diceNames.find(" vs ")) << " wins\n";
        } else if (sum1 < sum2) {
            std::cout << "(" << sum1 << ", " << sum2 << ") - " << diceNames.substr(diceNames.find("vs ") + 3) << " wins\n";
        } else {
            std::cout << "(" << sum1 << ", " << sum2 << ") - Draw\n";
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

    // Vergleiche für unterschiedliche Anzahl von Würfeln durchführen
    for (int numDice = 1; numDice <= 3; ++numDice) {
        compareDice(redDice, blueDice, "Red vs Blue", numDice);
        compareDice(redDice, greenDice, "Red vs Green", numDice);
        compareDice(blueDice, greenDice, "Blue vs Green", numDice);
    }

    return 0;
}
