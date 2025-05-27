#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <algorithm>
#include <set>
#include <string>
#include <vector>

using std::set;
using std::string;
using std::vector;

// auto stringReplace = [](const string &str, const char oldChar,
//                         const char newChar) { return str; };

// auto stringReplace = [](string &str, const char oldChar, const char newChar)
// {
//   replace(str.begin(), str.end(), oldChar, newChar);
//   return str;
// };

// 1) Immutable String Replace
auto stringReplace = [](const string &str, const char oldChar,
                        const char newChar) {
  string result(str);
  replace(result.begin(), result.end(), oldChar, newChar);
  return result;
};

TEST_CASE("Immutable String Replace") {
  SUBCASE("Replace single character") {
    string original = "hello world";
    string result = stringReplace(original, 'l', 'x');

    CHECK_EQ(result, "hexxo worxd");
    CHECK_EQ(original, "hello world");
  }

  SUBCASE("Replace character that doesn't exist") {
    string original = "hello";
    string result = stringReplace(original, 'z', 'x');

    CHECK_EQ(result, "hello");
    CHECK_EQ(original, "hello");
  }

  SUBCASE("Replace in empty string") {
    string original = "";
    string result = stringReplace(original, 'a', 'b');

    CHECK_EQ(result, "");
    CHECK_EQ(original, "");
  }
}

// auto setUnion = [](const set<int> &set1, const set<int> &set2) {
//   return set1;
// };

// auto setUnion = [](set<int> &set1, const set<int> &set2) {
//   set1.insert(set2.begin(), set2.end());
//   return set1;
// };

// 2) Immutable Set Union
auto setUnion = [](const set<int> &set1, const set<int> &set2) {
  set<int> result(set1);
  result.insert(set2.begin(), set2.end());
  return result;
};

TEST_CASE("Immutable Set Union") {
  SUBCASE("Union of two non-overlapping sets") {
    set<int> set1 = {1, 2, 3};
    set<int> set2 = {4, 5, 6};
    set<int> result = setUnion(set1, set2);

    CHECK_EQ(result, set<int>{1, 2, 3, 4, 5, 6});
    CHECK_EQ(set1, set<int>{1, 2, 3});
    CHECK_EQ(set2, set<int>{4, 5, 6});
  }

  SUBCASE("Union of overlapping sets") {
    set<int> set1 = {1, 2, 3};
    set<int> set2 = {3, 4, 5};
    set<int> result = setUnion(set1, set2);

    CHECK_EQ(result, set<int>{1, 2, 3, 4, 5});
    CHECK_EQ(set1, set<int>{1, 2, 3});
    CHECK_EQ(set2, set<int>{3, 4, 5});
  }

  SUBCASE("Union with empty set") {
    set<int> set1 = {1, 2, 3};
    set<int> set2 = {};
    set<int> result = setUnion(set1, set2);

    CHECK_EQ(result, set<int>{1, 2, 3});
    CHECK_EQ(set1, set<int>{1, 2, 3});
    CHECK(set2.empty());
  }
}

// template <typename T>
// auto vectorCons = [](const T &element, vector<T> &vec) {
//   return vec;
// };

// template <typename T>
// auto vectorCons = [](const T &element, const vector<T> &vec) {
//   vec.insert(result.begin(), element);
//   return vec;
// };

// 3) Immutable Vector Append (Cons)
template <typename T>
auto vectorCons = [](const T &element, const vector<T> &vec) {
  vector<T> result(vec);
  result.insert(result.begin(), element);
  return result;
};

TEST_CASE("Immutable Vector Append (Cons)") {
  SUBCASE("Cons to non-empty vector") {
    vector<int> original = {2, 3, 4};
    vector<int> result = vectorCons<int>(1, original);

    CHECK_EQ(result, vector<int>{1, 2, 3, 4});
    CHECK_EQ(original, vector<int>{2, 3, 4});
  }

  SUBCASE("Cons to empty vector") {
    vector<int> original = {};
    vector<int> result = vectorCons<int>(62, original);

    CHECK_EQ(result, vector<int>{62});
    CHECK(original.empty());
  }

  SUBCASE("Cons string to vector") {
    vector<string> original = {"world", "!"};
    vector<string> result = vectorCons<string>("hello", original);

    CHECK_EQ(result, vector<string>{"hello", "world", "!"});
    CHECK_EQ(original, vector<string>{"world", "!"});
  }
}

// auto vectorReverse = [](const vector<int> &vec) {
//   return vec;
// };

// auto vectorReverse = [](vector<int> &vec) {
//   reverse(vec.begin(), vec.end());
//   return vec;
// };

// 4) Immutable Integer List Reversal
auto vectorReverse = [](const vector<int> &vec) {
  vector<int> result(vec);
  reverse(result.begin(), result.end());
  return result;
};

TEST_CASE("Immutable Integer List Reversal") {
  SUBCASE("Reverse non-empty vector") {
    vector<int> original = {1, 2, 3, 4, 5};
    vector<int> result = vectorReverse(original);

    CHECK_EQ(result, vector<int>{5, 4, 3, 2, 1});
    CHECK_EQ(original, vector<int>{1, 2, 3, 4, 5});
  }

  SUBCASE("Reverse single element vector") {
    vector<int> original = {49};
    vector<int> result = vectorReverse(original);

    CHECK_EQ(result, vector<int>{49});
    CHECK_EQ(original, vector<int>{49});
  }

  SUBCASE("Reverse empty vector") {
    vector<int> original = {};
    vector<int> result = vectorReverse(original);

    CHECK(result.empty());
    CHECK(original.empty());
  }
}
