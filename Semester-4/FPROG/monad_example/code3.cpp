#include <iostream>
#include <string>
#include <vector>

// Struktur, die das Ergebnis und Logs enthält
struct NumbersWithLogs {
    int result;
    std::vector<std::string> logs;
};

// Funktion zum Quadrieren mit Logging
NumbersWithLogs square(int x) {
    int squared = x * x;
    return {
        squared,
        { "Squared " + std::to_string(x) + " to get " + std::to_string(squared) + "." }
    };
}

// Funktion, die 1 hinzufügt mit Logging
NumbersWithLogs addOne(const NumbersWithLogs& x) {
    int newResult = x.result + 1;
    std::vector<std::string> updatedLogs = x.logs;
    updatedLogs.push_back("Added 1 to " + std::to_string(x.result) + " to get " + std::to_string(newResult) + ".");
    return { newResult, updatedLogs };
}

// Hauptprogramm
int main() {
    // Schritt 1: Quadrieren
    NumbersWithLogs squareResult = square(2);

    // Schritt 2: 1 hinzufügen
    NumbersWithLogs finalResult = addOne(squareResult);

    // Ergebnis und Logs ausgeben
    std::cout << "Result: " << finalResult.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : finalResult.logs) {
        std::cout << "  " << log << "\n";
    }

    return 0;
}
