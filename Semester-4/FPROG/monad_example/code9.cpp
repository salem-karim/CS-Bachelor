#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>

// Generische Struktur für WrapWithLogs
template <typename T>
struct WrapWithLogs {
    T result;
    std::vector<std::string> logs;

    // bind-Methode zur Verkettung von Transformationen
    template <typename U>
    WrapWithLogs<U> bind(const std::function<WrapWithLogs<U>(T)>& transform) const {
        WrapWithLogs<U> newNumberWithLogs = transform(result);
        std::vector<std::string> updatedLogs = logs;
        updatedLogs.insert(updatedLogs.end(), newNumberWithLogs.logs.begin(), newNumberWithLogs.logs.end());
        return { newNumberWithLogs.result, updatedLogs };
    }
};

// Funktion, die einen generischen Wert in WrapWithLogs "einhüllt" (unit)
template <typename T>
WrapWithLogs<T> wrapWithLogs(T x) {
    return { x, {} };
}

// Funktion zum Quadrieren (Transformation) - generisch
template <typename T>
WrapWithLogs<T> square(T x) {
    static_assert(std::is_arithmetic<T>::value, "square requires a numeric type");
    T squared = x * x;
    return {
        squared,
        { "Squared " + std::to_string(x) + " to get " + std::to_string(squared) + "." }
    };
}

// Funktion, die 1 hinzufügt (Transformation) - generisch
template <typename T>
WrapWithLogs<T> addOne(T x) {
    static_assert(std::is_arithmetic<T>::value, "addOne requires a numeric type");
    T incremented = x + 1;
    return {
        incremented,
        { "Added 1 to " + std::to_string(x) + " to get " + std::to_string(incremented) + "." }
    };
}

// Funktion, die die Zahl mit 3 multipliziert (Transformation) - generisch
template <typename T>
WrapWithLogs<T> multiplyByThree(T x) {
    static_assert(std::is_arithmetic<T>::value, "multiplyByThree requires a numeric type");
    T multiplied = x * 3;
    return {
        multiplied,
        { "Multiplied " + std::to_string(x) + " by 3 to get " + std::to_string(multiplied) + "." }
    };
}

// Funktion, die einen generischen Wert in einen String umwandelt (Transformation)
template <typename T>
WrapWithLogs<std::string> toString(T x) {
    std::ostringstream oss;
    oss << "Value: " << x;
    return {
        oss.str(),
        { "Converted " + std::to_string(x) + " to string: \"" + oss.str() + "\"." }
    };
}

// Hauptprogramm
int main() {
    // Beispiel 1: Doppelte Quadrierung mit bind
    auto result1 = wrapWithLogs(2)
                       .bind(std::function<WrapWithLogs<int>(int)>(square<int>))
                       .bind(std::function<WrapWithLogs<int>(int)>(square<int>));

    // Ergebnis und Logs ausgeben
    std::cout << "Example 1: square(square(wrapWithLogs(2)))\n";
    std::cout << "Result: " << result1.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : result1.logs) {
        std::cout << "  " << log << "\n";
    }
    std::cout << "\n";

    // Beispiel 2: Add 1 mit bind
    auto result2 = wrapWithLogs(5)
                       .bind(std::function<WrapWithLogs<int>(int)>(addOne<int>));

    // Ergebnis und Logs ausgeben
    std::cout << "Example 2: addOne(wrapWithLogs(5)) using bind\n";
    std::cout << "Result: " << result2.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : result2.logs) {
        std::cout << "  " << log << "\n";
    }
    std::cout << "\n";

    // Beispiel 3: Multiply by 3 und konvertiere zu String
    auto result3 = wrapWithLogs(4)
                       .bind(std::function<WrapWithLogs<int>(int)>(multiplyByThree<int>))
                       .bind(std::function<WrapWithLogs<std::string>(int)>(toString<int>));

    // Ergebnis und Logs ausgeben
    std::cout << "Example 3: multiplyByThree(wrapWithLogs(4)) and convert to string using bind\n";
    std::cout << "Result: " << result3.result << "\n";
    std::cout << "Logs:\n";
    for (const auto& log : result3.logs) {
        std::cout << "  " << log << "\n";
    }

    return 0;
}
