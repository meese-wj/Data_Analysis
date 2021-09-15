#ifndef MEASURES_OF_CENTER
#define MEASURES_OF_CENTER
// This header defines the measures of center class.

#include <cstdint>
#include <vector>
#include <cmath>
#include <iostream>

namespace Statistics
{
    enum Measures
    {
        // TODO: Add median and mode functions too
        mean, variance, skewness, kurtosis, NUM_MEASURES
    };

    // Convert enum measure to int type
    template<typename int_t>
    constexpr int_t measure_to_( const Measures measure )
    {
        return static_cast<int_t>( measure );
    }

    template<typename input_t, typename output_t = input_t>
    class Measures_of_Center 
    {
        public:
            // Setup functions
            Measures_of_Center() = default;
            virtual void MoC_initialize();
            virtual ~Measures_of_Center() { /* intentionally empty */ };
            virtual void collect_data( const input_t * const data_start, const input_t * const data_end );
            virtual void collect_data( const std::vector<input_t> & data );
            virtual void reset_measures();

            // Statistical functions
            virtual output_t mean();
            virtual output_t variance();
            virtual output_t standard_deviation();
            virtual output_t standard_error();
            virtual output_t skewness();
            virtual output_t kurtosis();
            virtual output_t nth_central_moment( const output_t nth );
            virtual void compute_statistics();

            // Getter functions
            virtual output_t get_datum( const std::uint32_t idx ) const;
            virtual output_t get_measure( const Measures measure ) const;
            virtual output_t get_measure( const std::uint32_t measure ) const;

            // Output functions
            virtual void print_moc() const;

        protected:
            // Assume that the data is contiguous in memory
            std::uint32_t _size;
            const input_t * _start;
            const input_t * _end;
            
            // Store whether each measure is known
            // yet or not.
            std::uint8_t moc_computed [Measures::NUM_MEASURES];

            // Store the measures on the stack
            output_t moc [Measures::NUM_MEASURES];
            
            // Store the statistical function pointers on the 
            // stack to for iteration purposes
            output_t (Measures_of_Center<input_t, output_t>::* stat_functions [Measures::NUM_MEASURES]) (void);
    
    };  // Measures_of_Center

    /* ************************************************ */
    // Begin Setup Function Definitions
    
    // Two-part construction is necessary since this in
    // a base template class
    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::MoC_initialize()
    {
        // Assign the statistical functions for
        // the measures of center
        stat_functions[Measures::mean] = &Measures_of_Center<input_t, output_t>::mean;
        stat_functions[Measures::variance] = &Measures_of_Center<input_t, output_t>::variance;
        stat_functions[Measures::skewness] = &Measures_of_Center<input_t, output_t>::skewness;
        stat_functions[Measures::kurtosis] = &Measures_of_Center<input_t, output_t>::kurtosis;
    }

    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::collect_data( const input_t * const data_start, 
                                                              const input_t * const data_end )
    {
        // This assumes the input data is contiguous as
        // it is for the STL vector.
        _start = data_start;
        _end   = data_end;
        _size  = static_cast<std::uint32_t>( _end - _start );

        reset_measures();
    }
    
    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::collect_data( const std::vector<input_t> & data )
    {
        collect_data( data.data(), data.data() + data.size() );
    }

    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::reset_measures()
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
    output_t Measures_of_Center<input_t, output_t>::mean()
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
    output_t Measures_of_Center<input_t, output_t>::variance()
    {
        if (!moc_computed[Measures::variance])
        {   
            moc[Measures::variance] = 0;
            output_t mean_val = mean();
            
            output_t temp = 0;
            for ( std::uint32_t idx = 0; idx != _size; ++idx )
            {
                temp = get_datum(idx) - mean_val;
                moc[Measures::variance] += temp * temp;
            }

            // Assumes this is not a sampling variance
            moc[Measures::variance] /= static_cast<output_t>( _size );
            moc_computed[Measures::variance] = true;
        }
        return moc[Measures::variance];
    }

    // This should really only be called after 
    // the variance has been computed for speed.
    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::standard_deviation()
    {
        output_t var_val = variance();
        return sqrt( var_val );
    }

    // This should really only be called after 
    // the variance has been computed for speed.
    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::standard_error()
    {
        output_t var_val = variance();
        return sqrt( var_val / static_cast<std::uint32_t>(_size) );
    }

    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::skewness()
    {
        if (!moc_computed[Measures::skewness])
        {
            output_t std_val = standard_deviation();

            output_t mean_val = mean();
            output_t temp = 0;
            for ( std::uint32_t idx = 0; idx != _size; ++idx )
            {
                temp = get_datum(idx) - mean_val;
                moc[Measures::skewness] += temp * temp * temp;
            }
            moc[Measures::skewness] /= static_cast<output_t>(_size);
            moc[Measures::skewness] /= (std_val * std_val * std_val);
            moc_computed[Measures::skewness] = true;
        }
        return moc[Measures::skewness];
    }

    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::kurtosis()
    {
        if (!moc_computed[Measures::kurtosis])
        {
            output_t var_val = variance();

            output_t mean_val = mean();
            output_t temp = 0;
            for ( std::uint32_t idx = 0; idx != _size; ++idx )
            {
                temp = get_datum(idx) - mean_val;
                moc[Measures::kurtosis] += temp * temp * temp * temp;
            }
            moc[Measures::kurtosis] /= static_cast<output_t>(_size);
            moc[Measures::kurtosis] /= (var_val * var_val);
            moc_computed[Measures::kurtosis] = true;
        }
        return moc[Measures::kurtosis];
    }

    // Not recommended for use unless the nth power is unusual.
    template<typename input_t, typename output_t>
    output_t Measures_of_Center<input_t, output_t>::nth_central_moment( const output_t nth )
    {
        if ( nth == 2 )
            return variance();
        
        output_t mean_val = mean();
        output_t nth_val = 0;
        for ( std::uint32_t idx = 0; idx != _size; ++idx )
        {
            nth_val += pow(get_datum(idx) - mean_val, nth);
        }
        nth_val /= static_cast<output_t>( _size );
        return nth_val;                    
    }

    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::compute_statistics()
    {
        for ( std::uint32_t meas = 0; meas != measure_to_<std::uint32_t>(Measures::NUM_MEASURES); ++meas )
            (this ->* stat_functions[meas])();
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

    /* ************************************************ */
    // Begin Output Function Definitions
    template<typename input_t, typename output_t>
    void Measures_of_Center<input_t, output_t>::print_moc() const
    {
        std::cout << "\n";
        std::cout << "\nMeasures of Center:";
        std::cout << "\n  Mean      = " << get_measure(Measures::mean);
        std::cout << "\n  Variance  = " << get_measure(Measures::variance);
        std::cout << "\n  Std. Dev. = " << sqrt( get_measure(Measures::variance) );
        std::cout << "\n  Std. Err. = " << sqrt( get_measure(Measures::variance) / static_cast<output_t>(_size) );
        std::cout << "\n  Skewness  = " << get_measure(Measures::skewness);
        std::cout << "\n  Kurtosis  = " << get_measure(Measures::kurtosis);
        std::cout << "\n";
        std::cout << "\n";
    }

    /* ================================================ */
}


#endif