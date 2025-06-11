#include <iostream>
#include <vector>
#include <string>
#include <functional>

// Typdefinition für eine Liste (Vector)
using List = std::vector<std::string>;

// Funktion, die FlatMap (run) für Listen implementiert
List run(const List& input, const std::function<List(const std::string&)>& transform) {
    List result;
    for (const auto& item : input) {
        List transformed = transform(item);
        result.insert(result.end(), transformed.begin(), transformed.end());
    }
    return result;
}

// Hauptprogramm
int main() {
    // Türen
    List doors = { "red", "green", "blue" };

    // Transformation für Tür zu Kopf/Schwanz (Heads/Tails)
    List doorsAndCoinPossibilities = run(doors, [](const std::string& door) -> List {
        return { door + " heads", door + " tails" };
    });

    // Ausgabe der Ergebnisse
    std::cout << "Doors and Coin Possibilities:\n";
    for (const auto& possibility : doorsAndCoinPossibilities) {
        std::cout << possibility << "\n";
    }

    return 0;
}
