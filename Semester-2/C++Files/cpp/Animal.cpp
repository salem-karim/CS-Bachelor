#include "../h/Animal.h"
#include "../h/UniquePtr.h"
#include <iostream>
// #include <vector>

using namespace std;

int main() {
  // vector<Animal> animals;

  UniquePtr<Animal> myPointer(new Animal());
  cout << "RAII" << endl;
  return 0;
}
