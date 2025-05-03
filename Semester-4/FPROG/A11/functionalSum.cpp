#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct Sums {
  Sums() : evenSum(0), oddSum(0), total(0) {}
  Sums(const int &even, const int &odd, const int &total)
      : evenSum(even), oddSum(odd), total(total) {}

  int evenSum;
  int oddSum;
  int total;
};

const bool isEven(const int &value) { return value % 2 == 0; }

const bool isOdd(const int &value) { return value % 2 != 0; }

template <typename T, template <typename...> typename CollectionType>
const T sum(const CollectionType<T> &input, const T &init = 0) {
  return accumulate(input.begin(), input.end(), init);
}

template <typename CollT, typename UnaryPredicate>
const CollT filter(const CollT &input, UnaryPredicate filterFunction) {
  CollT filtered;
  copy_if(input.begin(), input.end(), back_inserter(filtered), filterFunction);
  return filtered;
}

const Sums sums(const vector<int> &numbers) {
  return Sums(sum(filter(numbers, isEven)), sum(filter(numbers, isOdd)),
              sum(numbers));
}

int main() {
  vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8};

  Sums theTotals = sums(numbers);
  cout << theTotals.oddSum << ", " << theTotals.evenSum << ", "
       << theTotals.total << endl;
}
