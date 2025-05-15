#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void print(const string &text) { cout << text; }

auto formatIcosahedronCurried = [](float V) {
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

auto volume = [](int a) { return (5 * pow(a, 3) * (3 + sqrt(5))) / 12.0f; };

auto area = [](int a) { return 5 * pow(a, 2) * sqrt(3); };

auto inradius = [](int a) { return (a * sqrt(3) * (3 + sqrt(5))) / 12.0f; };

auto circumradius = [](int a) { return (a / 4.0f) * sqrt(2 * (5 + sqrt(5))); };

string ikosaeder(int a) {
  return formatIcosahedronCurried(volume(a))(area(a))(inradius(a))(
      circumradius(a));
}

int main(int argc, char *argv[]) {
  const int a = 2;
  print(ikosaeder(a));
  return 0;
}
