#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

void printCube(const string &text) { cout << text; }

string formatString(const int V, const int A, const float d, const float ru,
                    const float ri) {
  stringstream output;
  output << "Volumen:" << V;
  output << " Oberfläche:" << A;
  output << " Diagonale:" << d;
  output << " Umkreisradius:" << ru;
  output << " Inkreisradius:" << ri << endl;
  return output.str();
}

string wuerfel(const int a) {
  const int V = pow(a, 3);
  const int A = 6 * pow(a, 2);
  const float d = a * sqrt(3);
  const float ru = sqrt(3) * a / 2;
  const float ri = a / 2.0f;
  return formatString(V, A, d, ru, ri);
}

int main(int argc, char *argv[]) {
  const int a = 2;
  printCube(wuerfel(a));
  return 0;
}
