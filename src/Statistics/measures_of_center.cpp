// This is the implementation source for the 
// Measures of Center class

#include "measures_of_center.hpp"
#include "int_power_templates.hpp"
#include <cmath>

namespace Statistics
{
    /* ************************************************ */
    // Begin Setup Function Definitions
    template<typename input_t, typename output_t>
    Measures_of_Center<input_t, output_t>::Measures_of_Center()
    {
        // Assign the statistical functions for
        // the measures of center
        stat_functions[Measures::mean] = &( mean() );
        stat_functions[Measures::variance] = &( variance() );
        stat_functions[Measures::skewness] = &( skewness() );
        stat_functions[Measures::kurtosis] = &( kurtosis() );
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

        reset_measures();
    }
    
    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::collect_data( const std::vector<input_t> & data )
    {
        collect_data( data.begin(), data.end() );
    }

    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::reset_measures() const
    {
        for ( std::uint32_t meas = 0; meas != measure_to_<std::uint32_t>(Measures::NUM_MEASURES); ++meas )
        {
            moc_computed[meas] = false;
            moc[meas] = 0;
        }
    }
    // End of Setup Function Definitions
    /* ================================================ */

    /* ************************************************ */
    // Begin Statistical Function Definitions
    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::mean() const
    {
        if (!moc_computed[Measures::mean])
        {
            moc[Measures::mean] = 0;
            for ( std::uint32_t idx = 0; idx != _size; ++idx )
            {
                moc[Measures::mean] += get_datum( idx );
            }
            moc[Measures::mean] /= static_cast<output_t>(_size);
            moc_computed[Measures::mean] = true;
        }
        return moc[Measures::mean];
    }
    
    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::variance() const
    {
        if (!moc_computed[Measures::variance])
        {   
            moc[Measures::variance] = 0;
            output_t mean_val = mean();
            
            for ( std::uint32_t idx = 0; idx != _size; ++idx )
            {
                moc[Measures::variance] += Math_Helpers::IntPower<output_t, 2>( get_datum(idx) - mean_val );
            }

            // Assumes this is not a sampling variance
            moc[Measures::variance] /= static_cast<output_t>( _size );
            moc[Measures::variance] = true;
        }
        return moc[Measures::variance];
    }

    // This should really only be called after 
    // the variance has been computed for speed.
    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::standard_deviation() const
    {
        output_t var_val = variance();
        return sqrt( var_val );
    }

    // This should really only be called after 
    // the variance has been computed for speed.
    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::standard_error() const
    {
        output_t var_val = variance();
        return sqrt( var_val / static_cast<std::uint32_t>(_size) );
    }

    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::skewness() const
    {
        if (!moc_computed[Measures::skewness])
        {
            output_t std_val = standard_deviation();
            moc[Measures::skewness] = nth_central_moment( 3 ) / Math_Helpers::IntPower<output_t, 3>(std_val);
            moc_computed[Measures::skewness] = true;
        }
        return moc[Measures::skewness];
    }

    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::kurtosis() const
    {
        if (!moc_computed[Measures::kurtosis])
        {
            output_t var_val = variance();
            moc[Measures::kurtosis] = nth_central_moment( 4 ) / Math_Helpers::IntPower<output_t, 4>(var_val);
            moc_computed[Measures::kurtosis] = true;
        }
        return moc[Measures::kurtosis];
    }

    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::nth_central_moment( const output_t nth ) const
    {
        if ( nth == 2 )
            return variance();
        
        output_t mean_val = mean();
        output_t nth_val = 0;
        for ( std::uint32_t idx = 0; idx != _size; ++idx )
        {
            nth_val += Math_Helpers::IntPower<output_t, nth>( get_datum(idx) - mean_val );
        }
        nth_val /= static_cast<output_t>( _size );
        return nth_val;                    
    }

    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::compute_statistics() const
    {
        for ( std::uint32_t meas = 0; meas != measure_to_<std::uint32_t>(Measures::NUM_MEASURES); ++meas )
            stat_functions[meas]();
    }
    // End of Statistical Function Definitions
    /* ================================================ */
    
    /* ************************************************ */
    // Begin Getter Function Definitions
    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::get_datum( const std::uint32_t idx ) const
    {
        // Assumes contiguous memory like STL vectors
        return static_cast<output_t>( *(_start + idx) );
    } 

    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::get_measure( const Measures measure ) const
    {
        return get_measure( measure_to_<std::uint32_t>(measure) );
    }

    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::get_measure( const std::uint32_t measure ) const
    {
        return moc[measure];
    }
    // End of Getter Function Definitions
    /* ================================================ */


    // Declare a bunch of different measures of 
    // center types to prevent linker errors.
    Measures_of_Center<double> mocdd();
    Measures_of_Center<double, float> mocdf();
    Measures_of_Center<float, double> mocfd();
}



