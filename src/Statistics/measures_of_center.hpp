#ifndef MEASURES_OF_CENTER
#define MEASURES_OF_CENTER
// This header defines the measures of center class.

#include <vector>
#include "fast_template_powers.hpp"

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
            Measures_of_Center();
            virtual ~Measures_of_Center();
            virtual void collect_data( const input_t * const data_start, const input_t * const data_end );
            virtual void collect_data( const std::vector<input_t> & data );
            virtual void reset_measures() const;

            // Statistical functions
            virtual output_t mean() const;
            virtual output_t variance() const;
            virtual output_t standard_deviation() const;
            virtual output_t standard_error() const;
            virtual output_t skewness() const;
            virtual output_t kurtosis() const;
            virtual output_t nth_central_moment( const output_t nth ) const;
            virtual void compute_statistics() const;

            // Getter functions
            virtual output_t get_datum( const std::uint32_t idx ) const;
            virtual output_t get_measure( const Measures measure ) const;
            virtual output_t get_measure( const std::uint32_t measure ) const;

        protected:
            // Assume that the data is contiguous in memory
            std::uint32_t _size;
            input_t * _start;
            input_t * _end;
            
            // Store whether each measure is known
            // yet or not.
            std::uint8_t moc_computed [Measures::NUM_MEASURES];

            // Store the measures on the stack
            output_t moc [Measures::NUM_MEASURES];
            
            // Store the statistical function pointers on the 
            // stack to for iteration purposes
            static void * stat_functions [Measures::NUM_MEASURES];

    
    };
}


#endif