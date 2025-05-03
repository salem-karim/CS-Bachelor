#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

/*unpure*/
void printQuader(const string &text) { cout << text; }

/*pure*/
string quader(int a, int b, int c) {
  stringstream output;
  const int V = a * b * c;
  const int A = 2 * (a * b + a * c + b * c);
  const float d = sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
  output << "Volumen:" << V << " Oberfläche:" << A << " Diagonale:" << d
         << endl;
  return output.str();
}

int main(int argc, char *argv[]) {
  const int a = 2;
  const int b = 3;
  const int c = 4;
  printQuader(quader(a, b, c));
  return 0;
}
