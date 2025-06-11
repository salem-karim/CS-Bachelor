#include <iostream>
#include <functional>
#include <memory>

// Generische Option-Struktur
template <typename T>
class Option {
public:
    // Konstruktor für "Some"
    static Option<T> some(T value) {
        return Option<T>(std::make_shared<T>(value));
    }

    // Konstruktor für "None"
    static Option<T> none() {
        return Option<T>(nullptr);
    }

    // Überprüfen, ob ein Wert vorhanden ist
    bool is_some() const {
        return value_ != nullptr;
    }

    // Zugriff auf den Wert
    T value() const {
        if (!is_some()) {
            throw std::runtime_error("Attempted to access value of None");
        }
        return *value_;
    }

private:
    explicit Option(std::shared_ptr<T> value) : value_(value) {}

    std::shared_ptr<T> value_;
};

// Run-Funktion zur Transformation
template <typename T>
Option<T> run(const Option<T>& input, const std::function<Option<T>(T)>& transform) {
    if (!input.is_some()) {
        return Option<T>::none();
    }
    return transform(input.value());
}

// Beispiel-Transformation: Add 1
Option<int> addOne(int x) {
    return Option<int>::some(x + 1);
}

// Hauptprogramm
int main() {
    // Beispiel 1: Eingabe mit Wert
    Option<int> input1 = Option<int>::some(5);
    Option<int> result1 = run(input1, std::function<Option<int>(int)>([](int x) { return addOne(x); }));

    if (result1.is_some()) {
        std::cout << "Result 1: " << result1.value() << "\n";
    } else {
        std::cout << "Result 1: None\n";
    }

    // Beispiel 2: Eingabe ohne Wert
    Option<int> input2 = Option<int>::none();
    Option<int> result2 = run(input2, std::function<Option<int>(int)>([](int x) { return addOne(x); }));

    if (result2.is_some()) {
        std::cout << "Result 2: " << result2.value() << "\n";
    } else {
        std::cout << "Result 2: None\n";
    }

    return 0;
}
