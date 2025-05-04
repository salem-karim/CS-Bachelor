#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void print(const string &text) { cout << text; }

string formattedString(float V, float A, float ri, float ru) {
  stringstream output;
  output << "Volumen:" << V;
  output << " Oberfläche:" << A, output << " Inkreisradius:" << ri;
  output << " Umkreisradius:" << ru << endl;
  return output.str();
}

string tetraeder(int a) {
  float V = pow(a, 3) * sqrt(2) / 12;
  float A = pow(a, 2) * sqrt(3);
  float ru = a * sqrt(6) / 4;
  float ri = a * sqrt(6) / 12;
  return formattedString(V, A, ri, ru);
}

int main(int argc, char *argv[]) {
  int a = 2;
  print(tetraeder(a));
  return 0;
}
