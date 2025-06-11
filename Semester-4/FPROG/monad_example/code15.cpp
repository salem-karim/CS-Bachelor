#include <iostream>
#include <list>
#include <string>

// Typdefinition für eine Liste
using List = std::list<std::string>;

// Funktion, die `flat_map` implementiert
template <typename T, typename Func>
auto flat_map(const std::list<T>& input, Func transform) {
    using ResultType = decltype(transform(std::declval<T>()));
    using ElementType = typename ResultType::value_type;

    std::list<ElementType> result;
    for (const auto& item : input) {
        auto transformed = transform(item);
        result.insert(result.end(), transformed.begin(), transformed.end());
    }
    return result;
}

int main() {
    // Türen
    List doors = { "red", "green", "blue" };

    // Beispiel 1: FlatMap-ähnliche Logik
    auto doorsAndCoinPossibilities = flat_map(doors, [](const std::string& door) {
        return List{ door + " heads", door + " tails" };
    });

    std::cout << "Doors and Coin Possibilities (flat_map):\n";
    for (const auto& possibility : doorsAndCoinPossibilities) {
        std::cout << possibility << "\n";
    }

    return 0;
}
