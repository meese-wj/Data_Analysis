// This is the unit test for 
// the Measures of Center base 
// class implementation
#include "../measures_of_center.hpp"
#include <cassert>
#include <iostream>

// Define some test int data
// This array has the following properties:
//   * mean     = 0
//   * variance = 36.66667 (converts to 36)
//   * skewness = 0
//   * kurtosis = 1.794545 (converts to 1)
//
constexpr int test_mean = 0;
constexpr int test_variance = 36.66667;
constexpr int test_skewness = 0;
constexpr int test_kurtosis = 1.794545;
int data_array [] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0,
                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


int main()
{
    Statistics::Measures_of_Center<int, double> int_moc;
    int_moc.collect_data( data_array, data_array + sizeof(data_array) / sizeof(int) );
    int_moc.compute_statistics();
    int_moc.print_moc();

    // Testing here...
    assert(int_moc.mean() == test_mean);
    assert(int_moc.variance() == test_variance);
    assert(int_moc.skewness() == test_skewness);
    assert(int_moc.kurtosis() == test_kurtosis);

    return 0;
}