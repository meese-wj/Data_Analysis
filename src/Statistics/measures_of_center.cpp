#include "measures_of_center.hpp"

namespace Statistics
{


    // Declare a bunch of different measures of 
    // center types to prevent linker errors.
    Measures_of_Center<double> mocdd();
    Measures_of_Center<double, float> mocdf();
    Measures_of_Center<float, double> mocfd();
}



