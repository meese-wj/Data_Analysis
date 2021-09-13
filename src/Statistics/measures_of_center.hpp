#ifndef MEASURES_OF_CENTER
#define MEASURES_OF_CENTER
// This header defines the measures of center class.

#include <cstdint>
#include <vector>

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
    };
}


#endif