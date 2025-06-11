#include <iostream>
#include <string>
#include <vector>
#include <functional>

// Struktur für WrapWithLogs
struct WrapWithLogs {
    int result;
    std::vector<std::string> logs;

    // bind-Methode zur Verkettung von Transformationen
    WrapWithLogs bind(const std::function<WrapWithLogs(int)>& transform) const {
        WrapWithLogs newNumberWithLogs = transform(result);
        std::vector<std::string> updatedLogs = logs;
        updatedLogs.insert(updatedLogs.end(), newNumberWithLogs.logs.begin(), newNumberWithLogs.logs.end());
        return { newNumberWithLogs.result, updatedLogs };
    }
};

// Funktion, die eine Zahl in WrapWithLogs "einhüllt" (unit)
WrapWithLogs wrapWithLogs(int x) {
    return { x, {} };
}

// Funktion zum Quadrieren (Transformation)
WrapWithLogs square(int x) {
    return {
        x * x,
        { "Squared " + std::to_string(x) + " to get " + std::to_string(x * x) + "." }
    };
}

// Funktion, die 1 hinzufügt (Transformation)
WrapWithLogs addOne(int x) {
    return {
        x + 1,
        { "Added 1 to " + std::to_string(x) + " to get " + std::to_string(x + 1) + "." }
    };
}

// Funktion, die die Zahl mit 3 multipliziert (Transformation)
WrapWithLogs multiplyByThree(int x) {
    return {
        x * 3,
        { "Multiplied " + std::to_string(x) + " by 3 to get " + std::to_string(x * 3) + "." }
    };
}

// Hauptprogramm
int main() {
    // Beispiel 1: Doppelte Quadrierung mit bind
    WrapWithLogs result1 = wrapWithLogs(2)
                               .bind(square)
                               .bind(square);

    // Ergebnis und Logs ausgeben
    std::cout << "Example 1: square(square(wrapWithLogs(2)))\n";
    std::cout << "Result: " << result1.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : result1.logs) {
        std::cout << "  " << log << "\n";
    }
    std::cout << "\n";

    // Beispiel 2: Add 1 mit bind
    WrapWithLogs result2 = wrapWithLogs(5)
                               .bind(addOne);

    // Ergebnis und Logs ausgeben
    std::cout << "Example 2: addOne(wrapWithLogs(5)) using bind\n";
    std::cout << "Result: " << result2.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : result2.logs) {
        std::cout << "  " << log << "\n";
    }
    std::cout << "\n";

    // Beispiel 3: Multiply by 3 mit bind
    WrapWithLogs result3 = wrapWithLogs(4)
                               .bind(multiplyByThree);

    // Ergebnis und Logs ausgeben
    std::cout << "Example 3: multiplyByThree(wrapWithLogs(4)) using bind\n";
    std::cout << "Result: " << result3.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : result3.logs) {
        std::cout << "  " << log << "\n";
    }

    return 0;
}
