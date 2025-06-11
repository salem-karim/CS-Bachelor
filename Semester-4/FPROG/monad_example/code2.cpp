#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// Function zum Quadrieren einer Zahl mit Logging
std::tuple<int, std::vector<std::string>> square(int x) {
  int result = x * x;
  std::vector<std::string> logs = {"Squared " + std::to_string(x) + " to get " +
                                   std::to_string(result) + "."};
  return {result, logs};
}

// Function, die 1 zu einer Zahl hinzufügt, mit Logging
std::tuple<int, std::vector<std::string>>
addOne(int x, const std::vector<std::string> &previousLogs) {
  int result = x + 1;
  std::vector<std::string> logs = previousLogs;
  logs.push_back("Added 1 to " + std::to_string(x) + " to get " +
                 std::to_string(result) + ".");
  return {result, logs};
}

// Hauptprogramm
int main() {
  // Schritt 1: Quadrieren mit Logging
  auto [squareResult, squareLogs] = square(2);

  // Schritt 2: 1 hinzufügen mit Logging
  auto [finalResult, finalLogs] = addOne(squareResult, squareLogs);

  // Ergebnis und Logs ausgeben
  std::cout << "Result: " << finalResult << "\n";
  std::cout << "Logs:\n";
  for (const auto &log : finalLogs) {
    std::cout << "  " << log << "\n";
  }

  return 0;
}
