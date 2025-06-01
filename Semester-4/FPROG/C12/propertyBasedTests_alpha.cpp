#include <algorithm>
#include <random>
#include <functional>
#include <numeric>
#include <limits>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace std::placeholders;
using namespace std::chrono;

auto range = [](const int minValue, const int maxValue){
    vector<int> range(maxValue - minValue + 1);
    iota(range.begin(), range.end(), minValue);
    return range;
};

template<typename DestinationType>
auto transformAll = [](const auto& source, const auto& fn){
    DestinationType result;
    result.resize(source.size());
    transform(source.begin(), source.end(), result.begin(), fn);
    return result;
};

auto power = [](const int first, const int second){
    return pow(first, second);
};

auto generate_ints = [](const int min, const int max){
    if(min > max) {
        return vector<int>();
    }

    if(min == max){
        return range(min, min);
    }

    if(max - min <= 100){
        return range(min, max);
    }

    random_device rd;					// use for generating the seed
    mt19937 generator(rd());	// used for generating pseudo-random numbers
    uniform_int_distribution<int> distribution(min, max); // used to generate uniformly distributed numbers between min and max
    auto values = transformAll<vector<int>>(range(0, 98), // generates the range [0..98] 
            [&distribution, &generator](auto){
                return distribution(generator); // generate the random numbers
            });
    values.push_back(min); // ensure that min and max values are included
    values.push_back(max);
    return values;
};

auto generate_ints_greater_than_1 = bind(generate_ints, 1, numeric_limits<int>::max());

auto property_0_to_power_0_is_1 = [](){
    return power(0, 0) == 1;
};

TEST_CASE("Properties"){
    cout << "Property: 0 to power 0 is 1" << endl;
    CHECK(property_0_to_power_0_is_1);
}
