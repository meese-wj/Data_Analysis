// This is the implementation source for the 
// Measures of Center class

#include "measures_of_center.hpp"
#include <cmath>

namespace Statistics
{
    /* ************************************************ */
    // Begin Setup Function Definitions
    template<typename input_t, typename output_t>
    Measures_of_Center<input_t, output_t>::Measures_of_Center()
    {
        // intentionally empty
    }                     

    template<typename input_t, typename output_t>
    Measures_of_Center<input_t, output_t>::~Measures_of_Center()
    {
        // Nothing to delete yet
    }

    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::collect_data( const input_t * const data_start, 
                                                              const input_t * const data_end )
    {
        // This assumes the input data is contiguous as
        // it is for the STL vector.
        _start = static_cast<output_t*>( data_start );
        _end   = static_cast<output_t*>( data_end );
        _size  = static_cast<std::uint32_t>( _end - _start );
    }
    
    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::collect_data( const std::vector<input_t> & data )
    {
        collect_data( data.begin(), data.end() );
    }
    // End of Setup Function Definitions
    /* ================================================ */

    /* ************************************************ */
    // Begin Statistical Function Definitions

    // End of Statistical Function Definitions
    /* ================================================ */
    
    /* ************************************************ */
    // Begin Getter Function Definitions


    // End of Getter Function Definitions
    /* ================================================ */


    // Declare a bunch of different measures of 
    // center types to prevent linker errors.
    Measures_of_Center<double> mocdd();
    Measures_of_Center<double, float> mocdf();
    Measures_of_Center<float, double> mocfd();
}



