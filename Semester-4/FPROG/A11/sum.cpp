#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

const bool isEven(const int &value) { return value % 2 == 0; }

const bool isOdd(const int &value) { return value % 2 != 0; }

int sum(const vector<int> &input) {
  return accumulate(input.begin(), input.end(), 0);
}

template <typename UnaryPrediacte>
const vector<int> filter(const vector<int> &input, UnaryPrediacte filterfunc) {
  vector<int> copy;
  copy_if(input.begin(), input.end(), back_inserter(copy), filterfunc);
  return copy;
}

int sum_subWithFunctionalLoops(const vector<int> &numbers) {
  return sum(filter(numbers, isEven)) - sum(filter(numbers, isOdd));
}

int main() {
  vector<int> numbers = {
      8,
      3,
      1,
  };
  cout << "Total (even added, odd subtracted): "
       << sum_subWithFunctionalLoops(numbers) << endl;

  return 0;
}
