#include <iostream>
#include <string>
#include <vector>
#include <functional>

// Struktur für WrapWithLogs
struct WrapWithLogs {
    int result;
    std::vector<std::string> logs;
};

// Funktion, die eine Zahl in WrapWithLogs "einhüllt"
WrapWithLogs wrapWithLogs(int x) {
    return { x, {} };
}

// Funktion zur zentralen Verarbeitung von Logs
WrapWithLogs runWithLogs(const WrapWithLogs& input, const std::function<WrapWithLogs(int)>& transform) {
    WrapWithLogs newNumberWithLogs = transform(input.result);
    std::vector<std::string> updatedLogs = input.logs;
    updatedLogs.insert(updatedLogs.end(), newNumberWithLogs.logs.begin(), newNumberWithLogs.logs.end());
    return { newNumberWithLogs.result, updatedLogs };
}

// Funktion zum Quadrieren (nur Transformation)
WrapWithLogs square(int x) {
    return {
        x * x,
        { "Squared " + std::to_string(x) + " to get " + std::to_string(x * x) + "." }
    };
}

// Funktion, die 1 hinzufügt (nur Transformation)
WrapWithLogs addOne(int x) {
    return {
        x + 1,
        { "Added 1 to " + std::to_string(x) + " to get " + std::to_string(x + 1) + "." }
    };
}

// Hauptprogramm
int main() {
    // Beispiel 1: Doppelte Quadrierung
    WrapWithLogs result1 = runWithLogs(
        runWithLogs(wrapWithLogs(2), square), square);

    // Ergebnis und Logs ausgeben
    std::cout << "Example 1: square(square(wrapWithLogs(2)))\n";
    std::cout << "Result: " << result1.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : result1.logs) {
        std::cout << "  " << log << "\n";
    }
    std::cout << "\n";

    // Beispiel 2: Add 1 mit Logs
    WrapWithLogs result2 = runWithLogs(wrapWithLogs(5), addOne);

    // Ergebnis und Logs ausgeben
    std::cout << "Example 2: runWithLogs(wrapWithLogs(5), addOne)\n";
    std::cout << "Result: " << result2.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : result2.logs) {
        std::cout << "  " << log << "\n";
    }

    return 0;
}
