#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void print(const string &text) { cout << text; }

auto formatDodecahedron = [](const float V) {
  return [=](const float A) {
    return [=](const float ri) {
      return [=](const float ru) {
        stringstream output;
        output << "Volumen:" << V;
        output << " Oberfläche:" << A;
        output << " Inkreisradius:" << ri;
        output << " Umkreisradius:" << ru << endl;
        return output.str();
      };
    };
  };
};

string dodekaeder(const int a) {
  auto volume = [a]() { return pow(a, 3) * (15 + 7 * sqrt(5)) / 4.0f; };
  auto area = [a]() { return 3 * pow(a, 2) * sqrt(5 * (5 + 2 * sqrt(5))); };
  auto inradius = [a]() { return a * sqrt(10 * (25 + 11 * sqrt(5))) / 20.0f; };
  auto circumradius = [a]() { return a * sqrt(3) * (1 + sqrt(5)) / 4.0f; };
  return formatDodecahedron(volume())(area())(inradius())(circumradius());
}

int main(int argc, char *argv[]) {
  const int a = 2;
  print(dodekaeder(a));
  return 0;
}
