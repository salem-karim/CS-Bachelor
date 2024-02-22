#include <iostream>
using namespace std;

void increment(int &i) { i++; }

int main() {
  int i = 0;
  cin >> i;
  float pi = 3.14;
  increment(i);
  string myString = "Hello World!";
  cout << myString << endl << i << endl;
  cout << pi << endl;
  return 0;
}