// This is the implementation source for the 
// Measures of Center class

#include "measures_of_center.hpp"
#include <cmath>

namespace Statistics
{
    /* ************************************************ */
    // Setup Functions
    template<typename input_t, typename output_t>
    Measures_of_Center<input_t, output_t>::Measures_of_Center()
    {
        // intentionally empty
    }                     

    /* ************************************************ */


    // Declare a bunch of different measures of 
    // center types to prevent linker errors.
    Measures_of_Center<double> mocdd();
    Measures_of_Center<double, float> mocdf();
    Measures_of_Center<float, double> mocfd();
}



