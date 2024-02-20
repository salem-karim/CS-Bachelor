#include <iostream>
using namespace std;

void increment(int &i) { i++; }

int main() {
  int i = 123;
  increment(i);
  string myString = "Hello World!";
  cout << myString << endl << i << endl;
  return 0;
}
