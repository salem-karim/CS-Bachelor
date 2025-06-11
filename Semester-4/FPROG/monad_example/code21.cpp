#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <future>
#include <mutex>
#include <algorithm>

// Typdefinition für einen Würfel
using Dice = std::vector<int>;
using ResultPair = std::pair<int, int>;

// Funktion zur Generierung einzigartiger Kombinationen von zwei Würfeln
void compareDice(const Dice& dice1, const Dice& dice2, const std::string& diceNames) {
    int wins1 = 0, wins2 = 0;
    std::set<ResultPair> uniqueResults;
    std::mutex mutex;

    auto compute = [&](int start, int end) {
        std::set<ResultPair> localResults;
        int localWins1 = 0, localWins2 = 0;

        for (int i = start; i < end; ++i) {
            for (int value1_2 : dice1) {
                for (int value2_1 : dice2) {
                    for (int value2_2 : dice2) {
                        int sum1 = dice1[i] + value1_2;
                        int sum2 = value2_1 + value2_2;

                        ResultPair result = {sum1, sum2};
                        if (localResults.find(result) == localResults.end()) {
                            localResults.insert(result);
                            if (sum1 > sum2) {
                                ++localWins1;
                            } else if (sum1 < sum2) {
                                ++localWins2;
                            }
                        }
                    }
                }
            }
        }

        std::lock_guard<std::mutex> lock(mutex);
        wins1 += localWins1;
        wins2 += localWins2;
        uniqueResults.insert(localResults.begin(), localResults.end());
    };

    size_t numThreads = std::thread::hardware_concurrency();
    size_t chunkSize = dice1.size() / numThreads;
    std::vector<std::future<void>> futures;

    for (size_t t = 0; t < numThreads; ++t) {
        size_t start = t * chunkSize;
        size_t end = (t == numThreads - 1) ? dice1.size() : (t + 1) * chunkSize;
        futures.push_back(std::async(std::launch::async, compute, start, end));
    }

    for (auto& future : futures) {
        future.get();
    }

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
