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

string dodekaeder(const int a) {
  float V = pow(a, 3) * (15 + 7 * sqrt(5)) / 4.0;
  float A = 3 * pow(a, 2) * sqrt(5 * (5 + 2 * sqrt(5)));
  float ru = a * sqrt(3) * (1 + sqrt(5)) / 4.0;
  float ri = a * sqrt(10 * (25 + 11 * sqrt(5))) / 20.0;
  return formattedString(V, A, ri, ru);
}

int main(int argc, char *argv[]) {
  int a = 2;
  print(dodekaeder(a));
  return 0;
}
