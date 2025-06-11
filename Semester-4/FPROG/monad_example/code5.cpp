#include <iostream>
#include <string>
#include <vector>

// Struktur für WrapWithLogs
struct WrapWithLogs {
    int result;
    std::vector<std::string> logs;
};

// Funktion, die eine Zahl in WrapWithLogs "einhüllt"
WrapWithLogs wrapWithLogs(int x) {
    return { x, {} };
}

// Funktion zum Quadrieren mit Logging
WrapWithLogs square(const WrapWithLogs& x) {
    int squared = x.result * x.result;
    std::vector<std::string> updatedLogs = x.logs;
    updatedLogs.push_back("Squared " + std::to_string(x.result) + " to get " + std::to_string(squared) + ".");
    return { squared, updatedLogs };
}

// Funktion, die 1 hinzufügt mit Logging
WrapWithLogs addOne(const WrapWithLogs& x) {
    int newResult = x.result + 1;
    std::vector<std::string> updatedLogs = x.logs;
    updatedLogs.push_back("Added 1 to " + std::to_string(x.result) + " to get " + std::to_string(newResult) + ".");
    return { newResult, updatedLogs };
}

// Hauptprogramm
int main() {
    // Beispiel 1: Doppelte Quadrierung
    WrapWithLogs squaredTwice = square(square(wrapWithLogs(2)));

    // Ergebnis und Logs ausgeben
    std::cout << "Example 1: square(square(wrapWithLogs(2)))\n";
    std::cout << "Result: " << squaredTwice.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : squaredTwice.logs) {
        std::cout << "  " << log << "\n";
    }
    std::cout << "\n";

    // Beispiel 2: addOne(wrapWithLogs(5))
    WrapWithLogs addOneResult = addOne(wrapWithLogs(5));

    // Ergebnis und Logs ausgeben
    std::cout << "Example 2: addOne(wrapWithLogs(5))\n";
    std::cout << "Result: " << addOneResult.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : addOneResult.logs) {
        std::cout << "  " << log << "\n";
    }

    return 0;
}
