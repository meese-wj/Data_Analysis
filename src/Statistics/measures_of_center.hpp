#ifndef MEASURES_OF_CENTER
#define MEASURES_OF_CENTER
// This header defines the measures of center class.

#include <vector>

namespace Statistics
{
    enum Measures
    {
        mean, standard_deviation, standard_error, median, mode, skewness, kurtosis, NUM_MEASURES
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

            // Statistical functions
            virtual output_t nth_central_moment( const input_t nth );
            virtual void compute_statistics() const;

            // Getter functions
            virtual output_t get_measure( const Measures measure ) const;
            virtual output_t get_measure( const std::uint32_t measure ) const;

        protected:
            // Store the measures on the stack
            output_t moc [Measures::NUM_MEASURES];

            // Assume that the data is contiguous in memory
            std::uint32_t _size;
            input_t * _start;
            input_t * _end;

    };
}


#endif