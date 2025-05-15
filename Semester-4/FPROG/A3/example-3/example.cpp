#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void print(const string &text) { cout << text; }

auto formatTetrahedronCurried = [](const float V) {
  return [V](const float A) {
    return [V, A](const float ri) {
      return [V, A, ri](const float ru) {
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

auto volume = [](const int a) { return (pow(a, 3) * sqrt(2)) / 12.0f; };

auto area = [](const int a) { return pow(a, 2) * sqrt(3); };

auto inradius = [](const int a) { return (a * sqrt(6)) / 12.0f; };

auto circumradius = [](const int a) { return (a * sqrt(6)) / 4.0f; };

string tetrahedron(const int a) {
  return formatTetrahedronCurried(volume(a))(area(a))(inradius(a))(
      circumradius(a));
}

int main(int argc, char *argv[]) {
  const int a = 1;
  print(tetrahedron(a));
  return 0;
}
