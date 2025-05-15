#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

/*unpure*/
void printQuader(const string &text) { cout << text; }

/*pure*/

string formattedString(const int V, const int A, const float d) {
  stringstream out;
  out << "Volumen:" << V << " Oberfläche:" << A << " Diagonale:" << d << endl;
  return out.str();
}

string quader(const int a, const int b, const int c) {
  const int V = a * b * c;
  const int A = 2 * (a * b + a * c + b * c);
  const float d = sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
  return formattedString(V, A, d);
}

int main(int argc, char *argv[]) {
  const int a = 2;
  const int b = 3;
  const int c = 4;
  printQuader(quader(a, b, c));
  return 0;
}
