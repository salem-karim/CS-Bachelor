#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <numeric>
#include <execution>
#include <ranges>
#include <functional>
#include <iterator>
#include <utility>
#include <optional>

// Typdefinition für einen Würfel
using Dice = std::vector<int>;
using ResultPair = std::pair<int, int>;

struct ComparisonResults {
    int wins1;
    int wins2;
    std::set<ResultPair> uniqueResults;
};

// Maybe-Monade zur Handhabung von optionalen Ergebnissen
class MaybeResult {
public:
    explicit MaybeResult(std::optional<std::string> result) : result(std::move(result)) {}

    template <typename Func>
    MaybeResult bind(Func func) const {
        if (result.has_value()) {
            return func(result.value());
        }
        return MaybeResult(std::nullopt);
    }

    const std::optional<std::string>& get() const { return result; }

private:
    std::optional<std::string> result;
};

// Monade für Summenberechnungen
class SumMonad {
public:
    explicit SumMonad(std::vector<int> values) : values(std::move(values)) {}

    template <typename Func>
    SumMonad bind(Func func) const {
        std::vector<int> newValues;
        for (int value : values) {
            auto transformed = func(value);
            newValues.insert(newValues.end(), transformed.begin(), transformed.end());
        }
        return SumMonad(std::move(newValues));
    }

    const std::vector<int>& get() const { return values; }

private:
    std::vector<int> values;
};

// Funktion zur Generierung aller möglichen Summen von Würfeln für eine gegebene Anzahl von Würfeln
SumMonad generateSums(const Dice& dice, int numDice) {
    std::vector<int> sums;

    // Rekursive Generierung aller möglichen Summen basierend auf numDice
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
    return SumMonad(std::move(sums));
}

// Funktion zur Berechnung der Ergebnisse mit Maybe-Monade
ComparisonResults calculateDiceComparison(const SumMonad& sums1Monad, const SumMonad& sums2Monad) {
    const auto& sums1 = sums1Monad.get();
    const auto& sums2 = sums2Monad.get();

    std::set<ResultPair> uniqueResults;

    auto computeResults = [&](int sum1, int sum2) -> MaybeResult {
        uniqueResults.emplace(sum1, sum2);
        if (sum1 > sum2) {
            return MaybeResult("wins1");
        } else if (sum1 < sum2) {
            return MaybeResult("wins2");
        } else {
            return MaybeResult("draw");
        }
    };

    int totalWins1 = 0;
    int totalWins2 = 0;

    for (int sum1 : sums1) {
        for (int sum2 : sums2) {
            MaybeResult result = computeResults(sum1, sum2);
            result.bind([&](const std::string& res) {
                if (res == "wins1") {
                    ++totalWins1;
                } else if (res == "wins2") {
                    ++totalWins2;
                }
                return MaybeResult(std::nullopt);
            });
        }
    }

    return {totalWins1, totalWins2, uniqueResults};
}

// Funktion zur Ausgabe der Ergebnisse
void printResults(const ComparisonResults& results, const std::string& diceNames) {
    auto splitNames = [](const std::string& names) {
        size_t vsPos = names.find(" vs ");
        size_t throwsPos = names.find("(");
        std::string player1 = names.substr(0, vsPos);
        std::string player2 = names.substr(vsPos + 4, throwsPos - vsPos - 5);
        std::string throwsInfo = names.substr(throwsPos);
        return std::make_tuple(player1, player2, throwsInfo);
    };

    auto [player1, player2, throwsInfo] = splitNames(diceNames);

    std::cout << "==============================\n";
    std::cout << "Unique Comparisons for " << diceNames << ":\n";
    for (const auto& [sum1, sum2] : results.uniqueResults) {
        if (sum1 > sum2) {
            std::cout << "(" << sum1 << ", " << sum2 << ") - " << player1 << " " << throwsInfo << " wins\n";
        } else if (sum1 < sum2) {
            std::cout << "(" << sum1 << ", " << sum2 << ") - " << player2 << " " << throwsInfo << " wins\n";
        } else {
            std::cout << "(" << sum1 << ", " << sum2 << ") - Draw\n";
        }
    }

    std::cout << "\nTotal Wins:\n";
    std::cout << player1 << " " << throwsInfo << ": " << results.wins1 << "\n";
    std::cout << player2 << " " << throwsInfo << ": " << results.wins2 << "\n";
    std::cout << "==============================\n\n";
}

int main() {
    // Definition der Würfel
    Dice redDice = {4, 4, 4, 4, 4, 1};
    Dice blueDice = {6, 3, 3, 3, 3, 3};
    Dice greenDice = {5, 5, 5, 2, 2, 2};

    // Ein Wurf pro Spieler
    auto singleThrowRed = generateSums(redDice, 1);
    auto singleThrowBlue = generateSums(blueDice, 1);
    auto singleThrowGreen = generateSums(greenDice, 1);

    auto resultsSingleRB = calculateDiceComparison(singleThrowRed, singleThrowBlue);
    printResults(resultsSingleRB, "Red vs Blue (1 throw each)");

    auto resultsSingleRG = calculateDiceComparison(singleThrowRed, singleThrowGreen);
    printResults(resultsSingleRG, "Red vs Green (1 throw each)");

    auto resultsSingleBG = calculateDiceComparison(singleThrowBlue, singleThrowGreen);
    printResults(resultsSingleBG, "Blue vs Green (1 throw each)");

    // Zwei Würfe pro Spieler
    auto doubleThrowRed = generateSums(redDice, 2);
    auto doubleThrowBlue = generateSums(blueDice, 2);
    auto doubleThrowGreen = generateSums(greenDice, 2);

    auto resultsDoubleRB = calculateDiceComparison(doubleThrowRed, doubleThrowBlue);
    printResults(resultsDoubleRB, "Red vs Blue (2 throws each)");

    auto resultsDoubleRG = calculateDiceComparison(doubleThrowRed, doubleThrowGreen);
    printResults(resultsDoubleRG, "Red vs Green (2 throws each)");

    auto resultsDoubleBG = calculateDiceComparison(doubleThrowBlue, doubleThrowGreen);
    printResults(resultsDoubleBG, "Blue vs Green (2 throws each)");

    // Drei Würfe pro Spieler
    auto tripleThrowRed = generateSums(redDice, 3);
    auto tripleThrowBlue = generateSums(blueDice, 3);
    auto tripleThrowGreen = generateSums(greenDice, 3);

    auto resultsTripleRB = calculateDiceComparison(tripleThrowRed, tripleThrowBlue);
    printResults(resultsTripleRB, "Red vs Blue (3 throws each)");

    auto resultsTripleRG = calculateDiceComparison(tripleThrowRed, tripleThrowGreen);
    printResults(resultsTripleRG, "Red vs Green (3 throws each)");

    auto resultsTripleBG = calculateDiceComparison(tripleThrowBlue, tripleThrowGreen);
    printResults(resultsTripleBG, "Blue vs Green (3 throws each)");

    return 0;
}
