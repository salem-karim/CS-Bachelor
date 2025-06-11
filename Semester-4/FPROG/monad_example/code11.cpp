#include <iostream>
#include <string>
#include <memory>

// Platzhaltertypen
struct User {
    std::string name;
};

struct Pet {
    std::string nickname;
};

// Option-Struktur (ersetzt std::optional)
template <typename T>
class Option {
public:
    // Konstruktor für "Some"
    static Option<T> some(const T& value) {
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

// Beispiel-Dummyfunktionen
Option<User> getCurrentUser(bool includeUser) {
    // Simuliert entweder einen Benutzer oder keinen
    if (includeUser) {
        return Option<User>::some(User{"John Doe"});
    }
    return Option<User>::none();
}

Option<Pet> getPet(const User& user, bool includePet) {
    // Simuliert entweder ein Haustier oder keins
    if (includePet && user.name == "John Doe") {
        return Option<Pet>::some(Pet{"Buddy"});
    }
    return Option<Pet>::none();
}

Option<std::string> getNickname(const Pet& pet, bool includeNickname) {
    // Simuliert entweder einen Spitznamen oder keinen
    if (includeNickname) {
        return Option<std::string>::some(pet.nickname);
    }
    return Option<std::string>::none();
}

// Funktion getPetname
Option<std::string> getPetname(bool includeUser, bool includePet, bool includeNickname) {
    // Versuchen, den aktuellen Benutzer zu holen
    Option<User> user = getCurrentUser(includeUser);
    if (!user.is_some()) {
        return Option<std::string>::none();
    }

    // Versuchen, das Haustier des Benutzers zu holen
    Option<Pet> pet = getPet(user.value(), includePet);
    if (!pet.is_some()) {
        return Option<std::string>::none();
    }

    // Versuchen, den Spitznamen des Haustiers zu holen
    Option<std::string> nickname = getNickname(pet.value(), includeNickname);
    if (!nickname.is_some()) {
        return Option<std::string>::none();
    }

    // Spitznamen zurückgeben
    return nickname;
}

// Hauptprogramm
int main() {
    // Beispiel 1: Alles vorhanden
    Option<std::string> result1 = getPetname(true, true, true);
    if (result1.is_some()) {
        std::cout << "Example 1: Pet name: " << result1.value() << "\n";
    } else {
        std::cout << "Example 1: No pet name found.\n";
    }

    // Beispiel 2: Kein Benutzer
    Option<std::string> result2 = getPetname(false, true, true);
    if (result2.is_some()) {
        std::cout << "Example 2: Pet name: " << result2.value() << "\n";
    } else {
        std::cout << "Example 2: No pet name found.\n";
    }

    // Beispiel 3: Kein Haustier
    Option<std::string> result3 = getPetname(true, false, true);
    if (result3.is_some()) {
        std::cout << "Example 3: Pet name: " << result3.value() << "\n";
    } else {
        std::cout << "Example 3: No pet name found.\n";
    }

    // Beispiel 4: Kein Spitzname
    Option<std::string> result4 = getPetname(true, true, false);
    if (result4.is_some()) {
        std::cout << "Example 4: Pet name: " << result4.value() << "\n";
    } else {
        std::cout << "Example 4: No pet name found.\n";
    }

    return 0;
}
