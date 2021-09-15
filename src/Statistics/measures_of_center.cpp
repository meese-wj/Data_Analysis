// This is the implementation source for the 
// Measures of Center class

#include "measures_of_center.hpp"

namespace Statistics
{
    // Declare a bunch of different measures of 
    // center types to check for compilation errors.
    namespace TemplateDeclarations
    {
        void Declaration_Function()
        {    
            Measures_of_Center<int> mocii;
            Measures_of_Center<int, double> mocid;
            Measures_of_Center<int, float> mocif;
            Measures_of_Center<double> mocdd;
            Measures_of_Center<double, float> mocdf;
            Measures_of_Center<float, double> mocfd;
        }
    }
}



