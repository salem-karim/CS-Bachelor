#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <future>
#include <algorithm>
#include <numeric>
#include <execution>
#include <queue>

// Typdefinition für einen Würfel
using Dice = std::vector<int>;
using ResultPair = std::pair<int, int>;

// Funktion zur Generierung einzigartiger Kombinationen von zwei Würfeln
void compareDice(const Dice& dice1, const Dice& dice2, const std::string& diceNames) {
    int wins1 = 0, wins2 = 0;
    std::set<ResultPair> uniqueResults;
    std::mutex mutex;
    std::condition_variable cv;
    std::queue<std::pair<int, int>> resultsQueue;

    // Funktion, um alle möglichen Summenkombinationen in einem Set zu speichern
    auto generateSums = [](const Dice& dice) {
        std::set<int> sums;
        std::for_each(std::execution::par, dice.begin(), dice.end(), [&](int value1) {
            std::for_each(dice.begin(), dice.end(), [&](int value2) {
                sums.insert(value1 + value2);
            });
        });
        return sums;
    };

    // Erstelle die Summensets parallel
    std::set<int> sums1, sums2;
    std::thread thread1([&] { sums1 = generateSums(dice1); });
    std::thread thread2([&] { sums2 = generateSums(dice2); });
    thread1.join();
    thread2.join();

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

    std::cout << "Unique Comparisons for " << diceNames << ":\n";
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

    // Vergleiche durchführen
    compareDice(redDice, blueDice, "Red vs Blue");
    compareDice(redDice, greenDice, "Red vs Green");
    compareDice(blueDice, greenDice, "Blue vs Green");

    return 0;
}
