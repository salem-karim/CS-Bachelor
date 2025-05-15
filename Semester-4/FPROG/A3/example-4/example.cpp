#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void print(const string &text) { cout << text; }

auto formatOctahedronCurried = [](float V) {
  return [=](float A) {
    return [=](float ri) {
      return [=](float ru) {
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

auto volume = [](int a) { return (pow(a, 3) * sqrt(2)) / 3.0f; };

auto area = [](int a) { return 2 * pow(a, 2) * sqrt(3); };

auto inradius = [](int a) { return (a * sqrt(6)) / 6.0f; };

auto circumradius = [](int a) { return (a * sqrt(2)) / 2.0f; };

string oktaeder(int a) {
  return formatOctahedronCurried(volume(a))(area(a))(inradius(a))(
      circumradius(a));
}

int main(int argc, char *argv[]) {
  const int a = 2;
  print(oktaeder(a));
  return 0;
}
