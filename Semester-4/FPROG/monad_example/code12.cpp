#include <iostream>
#include <optional>
#include <string>

// Platzhaltertypen
struct User {
    std::string name;
};

struct Pet {
    std::string nickname;
};

// Beispiel-Dummyfunktionen
std::optional<User> getCurrentUser() {
    return User{"John Doe"};  // Gibt einen Benutzer zurück
    // return std::nullopt;  // Simuliert keinen Benutzer
}

std::optional<Pet> getPet(const User& user) {
    if (user.name == "John Doe") {
        return Pet{"Buddy"};
    }
    return std::nullopt;
}

std::optional<std::string> getNickname(const Pet& pet) {
    return pet.nickname;
}

// Funktion, die eine Transformation auf ein std::optional anwendet
template <typename T, typename U, typename Func>
std::optional<U> run(const std::optional<T>& input, Func transform) {
    if (!input) {
        return std::nullopt;
    }
    return transform(*input);
}

// Funktion getPetNickname
std::optional<std::string> getPetNickname() {
    // Hole den aktuellen Benutzer
    std::optional<User> user = getCurrentUser();

    // Hole das Haustier des Benutzers
    std::optional<Pet> userPet = run<User, Pet>(user, [](const User& u) -> std::optional<Pet> {
        return getPet(u);
    });

    // Hole den Spitznamen des Haustiers
    std::optional<std::string> userPetNickname = run<Pet, std::string>(userPet, [](const Pet& p) -> std::optional<std::string> {
        return getNickname(p);
    });

    return userPetNickname;
}

// Hauptprogramm
int main() {
    std::optional<std::string> petName = getPetNickname();

    if (petName) {
        std::cout << "Pet name: " << *petName << "\n";
    } else {
        std::cout << "No pet name found.\n";
    }

    return 0;
}
