#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void print(const string &text) { cout << text; }

auto formatIcosahedronCurried = [](const float V) {
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

string ikosaeder(const int a) {
  auto volume = [a]() { return (5 * pow(a, 3) * (3 + sqrt(5))) / 12.0f; };
  auto area = [a]() { return 5 * pow(a, 2) * sqrt(3); };
  auto inradius = [a]() { return (a * sqrt(3) * (3 + sqrt(5))) / 12.0f; };
  auto circumradius = [a]() { return (a / 4.0f) * sqrt(2 * (5 + sqrt(5))); };
  return formatIcosahedronCurried(volume())(area())(inradius())(circumradius());
}

int main(int argc, char *argv[]) {
  const int a = 2;
  print(ikosaeder(a));
  return 0;
}
