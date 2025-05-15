#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void print(const string &text) { cout << text; }

auto formatDodecahedronCurried = [](float V) {
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

auto volume = [](int a) { return pow(a, 3) * (15 + 7 * sqrt(5)) / 4.0f; };

auto area = [](int a) { return 3 * pow(a, 2) * sqrt(5 * (5 + 2 * sqrt(5))); };

auto inradius = [](int a) {
  return a * sqrt(10 * (25 + 11 * sqrt(5))) / 20.0f;
};

auto circumradius = [](int a) { return a * sqrt(3) * (1 + sqrt(5)) / 4.0f; };

string dodekaeder(int a) {
  return formatDodecahedronCurried(volume(a))(area(a))(inradius(a))(
      circumradius(a));
}

int main(int argc, char *argv[]) {
  const int a = 2;
  print(dodekaeder(a));
  return 0;
}
