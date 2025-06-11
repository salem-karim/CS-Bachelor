#include <iostream>
#include <list>
#include <string>
#include <vector>

// Typdefinition für eine Liste
using List = std::list<std::string>;

// Funktion, die `map` implementiert
template <typename T, typename Func>
auto map(const std::list<T>& input, Func transform) {
    std::list<decltype(transform(std::declval<T>()))> result;
    for (const auto& item : input) {
        result.push_back(transform(item));
    }
    return result;
}

// Funktion, die `flat` implementiert
template <typename T>
std::list<T> flat(const std::list<std::list<T>>& input) {
    std::list<T> result;
    for (const auto& sublist : input) {
        result.insert(result.end(), sublist.begin(), sublist.end());
    }
    return result;
}

int main() {
    // Türen
    List doors = { "red", "green", "blue" };

    // Map-ähnliche Logik
    auto unflattenedDoorsAndCoinPossibilities = map(doors, [](const std::string& door) {
        return List{ door + " heads", door + " tails" };
    });

    // Flache Liste erzeugen
    auto doorsAndCoinPossibilities = flat(unflattenedDoorsAndCoinPossibilities);

    // Ausgabe der Ergebnisse
    std::cout << "Doors and Coin Possibilities:\n";
    for (const auto& possibility : doorsAndCoinPossibilities) {
        std::cout << possibility << "\n";
    }

    return 0;
}
