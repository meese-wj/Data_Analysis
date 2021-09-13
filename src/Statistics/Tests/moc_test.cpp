// This is the unit test for 
// the Measures of Center base 
// class implementation
#include "../measures_of_center.hpp"

// Define some test data
int data_array [] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0,
                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


int main()
{
    Statistics::Measures_of_Center<int> int_moc;
    int_moc.collect_data( data_array, data_array + sizeof(data_array) / sizeof(int) );
    return 0;
}