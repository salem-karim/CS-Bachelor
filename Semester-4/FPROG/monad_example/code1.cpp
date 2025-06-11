#include <iostream>
#include <functional>

// Funktion zum Quadrieren einer Zahl
int square(int x) {
    return x * x;
}

// Funktion, die 1 zu einer Zahl hinzufügt
int addOne(int x) {
    return x + 1;
}

// Hauptprogramm
int main() {
    // Verkettung der Funktionen
    int result = addOne(square(2));

    // Ergebnis ausgeben
    std::cout << "Result: " << result << std::endl;

    return 0;
}
