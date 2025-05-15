#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void printCube(const string &text) { cout << text; }

auto formatStringCurried = [](const int V) {
  return [V](const int A) {
    return [V, A](const float d) {
      return [V, A, d](const float ru) {
        return [V, A, d, ru](const float ri) {
          stringstream output;
          output << "Volumen:" << V;
          output << " Oberfläche:" << A;
          output << " Diagonale:" << d;
          output << " Umkreisradius:" << ru;
          output << " Inkreisradius:" << ri << endl;
          return output.str();
        };
      };
    };
  };
};

auto volume = [](const int a) { return pow(a, 3); };

auto area = [](const int a) { return 6 * pow(a, 2); };

auto diagonal = [](const int a) { return a * sqrt(3); };

auto circumradius = [](const int a) { return (sqrt(3) * a) / 2.0f; };

auto inradius = [](const int a) { return a / 2.0f; };

string cube(const int a) {
  return formatStringCurried(volume(a))(area(a))(diagonal(a))(circumradius(a))(
      inradius(a));
}

int main(int argc, char *argv[]) {
  const int a = 2;
  printCube(cube(a));
  return 0;
}
