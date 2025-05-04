#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void print(const string &text) { cout << text; }

string formattedString(const float V, const float A, const float ri,
                       const float ru) {
  stringstream output;
  output << "Volumen:" << V;
  output << " Oberfläche:" << A;
  output << " Inkreisradius:" << ri;
  output << " Umkreisradius:" << ru << endl;
  return output.str();
}

string ikosaeder(const int a) {
  float V = 5 * pow(a, 3) * (3 + sqrt(5)) / 12;
  float A = 5 * pow(a, 2) * sqrt(3);
  float ru = a / 4.0 * sqrt(2 * (5 + sqrt(5)));
  float ri = a * sqrt(3) * (3 + sqrt(5)) / 12;
  return formattedString(V, A, ri, ru);
}

int main(int argc, char *argv[]) {
  int a = 2;
  print(ikosaeder(a));
  return 0;
}
