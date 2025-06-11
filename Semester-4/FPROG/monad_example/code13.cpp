// compile with g++ -std=c++23 -Wall -Wextra code13.cpp
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

// Funktion getPetNickname
std::optional<std::string> getPetNickname() {
    return getCurrentUser()
        .and_then(getPet)       // Hole das Haustier des Benutzers
        .and_then(getNickname); // Hole den Spitznamen des Haustiers
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
