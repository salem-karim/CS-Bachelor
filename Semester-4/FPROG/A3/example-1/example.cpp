#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void printQuader(const string &text) { cout << text; }

auto formattedStringCurried = [](const int V) {
  return [V](const int A) {
    return [V, A](const float d) {
      stringstream out;
      out << "Volumen:" << V << " Oberfläche:" << A << " Diagonale:" << d
          << endl;
      return out.str();
    };
  };
};

auto volume = [](const int a, const int b, const int c) { return a * b * c; };

auto area = [](const int a, const int b, const int c) {
  return 2 * (a * b + a * c + b * c);
};

auto diagonal = [](const int a, const int b, const int c) {
  return sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
};

auto quaderCurried = [](int a) {
  return [a](int b) {
    return [a, b](int c) {
      return formattedStringCurried(volume(a, b, c))(area(a, b, c))(
          diagonal(a, b, c));
    };
  };
};

int main() {
  const int a = 2;
  const int b = 3;
  const int c = 4;
  printQuader(quaderCurried(a)(b)(c));
  return 0;
}

// should return Volumen:24 Oberfläche:52 Diagonale:5.38516
