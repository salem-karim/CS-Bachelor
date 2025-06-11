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
    // Schritt 1: Zahl mit Logs einhüllen
    WrapWithLogs wrappedNumber = wrapWithLogs(2);

    // Schritt 2: Quadrieren
    WrapWithLogs squareResult = square(wrappedNumber);

    // Schritt 3: 1 hinzufügen
    WrapWithLogs finalResult = addOne(squareResult);

    // Ergebnis und Logs ausgeben
    std::cout << "Result: " << finalResult.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : finalResult.logs) {
        std::cout << "  " << log << "\n";
    }

    return 0;
}
