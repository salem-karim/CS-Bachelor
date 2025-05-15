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

string oktaeder(const int a) {
  const float V = pow(a, 3) * sqrt(2) / 3;
  const float A = 2 * pow(a, 2) * sqrt(3);
  const float ru = a * sqrt(2) / 2;
  const float ri = a * sqrt(6) / 6;
  return formattedString(V, A, ri, ru);
}

int main(int argc, char *argv[]) {
  const int a = 2;
  print(oktaeder(a));
  return 0;
}
