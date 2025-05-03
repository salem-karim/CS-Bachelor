#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void printCube(const string &text) { cout << text; }

string formatString(int V, int A, float d, float ru, float ri) {
  stringstream output;
  output << "Volumen:" << V;
  output << " Oberfläche:" << A;
  output << " Diagonale:" << d;
  output << " Umkreisradius:" << ru;
  output << " Inkreisradius:" << ri << endl;
  return output.str();
}

string wuerfel(int a) {
  const int V = pow(a, 3);
  const int A = 6 * pow(a, 2);
  const float d = a * sqrt(3);
  const float ru = (float)a / 2 * sqrt(3);
  const float ri = (float)a / 2;
  return formatString(V, A, d, ru, ri);
}

int main(int argc, char *argv[]) {
  const int a = 2;
  printCube(wuerfel(a));
  return 0;
}
