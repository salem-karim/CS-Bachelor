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
auto generate_ints_greater_than_0 = bind(generate_ints, 0, numeric_limits<int>::max());

auto all_of_collection = [](const auto& collection, const auto& fn){
    return all_of(collection.begin(), collection.end(), fn);
};

auto printGeneratedValues = [](const string& generatorName, const auto& values){
    cout << "Check generator " << generatorName << endl;
    for_each(values.begin(), values.end(), [](auto value) { cout << value << ", ";});
    cout << endl;
 };

auto check_property = [](const auto& generator, const auto& property, const string& generatorName){
    auto values = generator();
    printGeneratedValues(generatorName, values); // should be commented finally
    bool pass = all_of_collection(values, property);
    CHECK(pass);
    return pass;
};

auto property_0_to_power_0_is_1 = [](){
    return power(0, 0) == 1;
};

auto prop_0_to_any_nonzero_int_is_0= [](const int exponent){
    CHECK(exponent > 0);
    return power(0, exponent) == 0;
};

TEST_CASE("Properties"){
    cout << "Property: 0 to power 0 is 1" << endl;
    CHECK(property_0_to_power_0_is_1);

    cout << "Property: 0 to any non-zero power is 0" << endl;
    check_property(generate_ints_greater_than_1, prop_0_to_any_nonzero_int_is_0, "generate ints");
}
