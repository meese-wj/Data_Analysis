#ifndef MOC_TESTS
#define MOC_TESTS
// Use this header to define the 
// tests for the Measures of Center
#include <cassert>
#include <iostream>
#include "../../measures_of_center.hpp"

#define TEST_ID() std::cout << __FUNCTION__ << " test in " << __FILE__ << ": " << __LINE__ << ".";
#define PRINT_TEST_VALUE(x) std::cout << "\nTest Value: " << x << "\n";

namespace MoC_Tests
{
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
    int data_array [] = { -10, -9, -8, -7, -6, 
                        -5, -4, -3, -2, -1, 0,
                            1, 2, 3, 4, 5, 6, 7, 
                            8, 9, 10 };
    
    struct MoC_Tester
    {
        Statistics::Measures_of_Center<int, int> int_moc;
        MoC_Tester() : int_moc()
        {
            int_moc.collect_data( data_array, data_array + sizeof(data_array) / sizeof(int) );
            int_moc.compute_statistics();
        }

        void mean_test()
        {
            int value = int_moc.get_measure(Statistics::Measures::mean);
            TEST_ID()
            PRINT_TEST_VALUE( value )
            assert(value == test_mean); 
        }

        void variance_test()
        {
            int value = int_moc.get_measure(Statistics::Measures::variance);
            TEST_ID()
            PRINT_TEST_VALUE( value )
            assert(value == test_variance); 
        }
        
        void skewness_test()
        {
            int value = int_moc.get_measure(Statistics::Measures::skewness);
            TEST_ID()
            PRINT_TEST_VALUE( value )
            assert(value == test_skewness); 
        }
        
        void kurtosis_test()
        {
            int value = int_moc.get_measure(Statistics::Measures::kurtosis);
            TEST_ID()
            PRINT_TEST_VALUE( value )
            assert(value == test_kurtosis); 
        }

        ~MoC_Tester(){ /* intentionally empty */ }
    };
}

#endif // MOC_TESTS