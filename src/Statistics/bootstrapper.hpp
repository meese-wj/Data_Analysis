#ifndef DATA_ANALYSIS_BOOTSTRAPPER
#define DATA_ANALYSIS_BOOTSTRAPPER
// This is the base Bootstrapper class
// that takes in a Datastream.
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <time.h>
#include <DataStream/datastream.hpp>
#include <DataFiles/data_table.hpp>

namespace Statistics
{
    template<typename data_t>
    class Bootstrapper : public DataStreams::DataStream<data_t>
    {
        public:
            Bootstrapper() : DataStream::DataStream<data_t>::DataStream() {}
            virtual ~Bootstrapper() 
            { 
                delete bootstrap_statistics;
                delete bootstrap_samples;
            }
            void initialize_bootstrap( const std::uint32_t nboots,
                                       const std::uint32_t nsamples, 
                                       const std::vector<data_t> & data );

            void generate_samples() const;

            void resample_data( std::vector<data_t*> & bootstrap_row ) const; 

            // Bootstrap with an arbitrary statistic
            // in mind accessed by a function pointer
            void bootstrap( data_t (*func) (const data_t) ) const;

            // Export bootstrapped data
            const std::vector<data_t> * const get_bootstrap_statistics() const
            {
                return bootstrap_statistics;
            }

        private:
            // Store the number of samples, stored as rows
            std::uint32_t num_bootstraps;
            std::uint32_t num_samples_per_bootstrap;

            // Store a std::vector with the bootstrap statistics
            std::vector<data_t> * bootstrap_statistics;

            // Store a DataTable of data_t* to point to
            // the individual Bootstrap samples.
            DataFiles::DataTable<data_t*> * bootstrap_samples = nullptr;

    };  // Bootstrapper

    /* ******************************************************* */
    // Begin initializer definitions
    
    template<typename data_t>
    void Bootstrapper<data_t>::initialize_bootstrap( const std::uint32_t nboots, 
                                                     const std::uint32_t nsamples, 
                                                     const std::vector<data_t> & data )
    {
        data_import( data );

        bootstrap_statistics -> resize(nboots);

        bootstrap_samples = new DataFiles::DataTable<data_t*>;
        bootstrap_samples -> resize( nboots, nsamples );

        num_bootstraps = nboots;
        num_samples_per_bootstrap = nsamples; 

        generate_samples();  
    }

    template<typename data_t>
    void Bootstrapper<data_t>::generate_samples() const
    {
        // First seed the rng
        srand(time(NULL));
        for ( std::uint32_t row = 0, nrows = num_bootstraps; row != nrows; ++row )
            resample_data( bootstrap_samples -> row_reference(row) );
    }

    // End initializer definitions
    /* ======================================================= */

    /* ******************************************************* */
    // Begin resampling definitions

    template<typename data_t>
    void Bootstrapper<data_t>::resample_data( std::vector<data_t*> & bootstrap_row ) const
    {
        // Resample the DataStream pointers and store them.
        // This function **should** be fast since it is essentially
        // just randomly sampling integers and storing those instead
        // of looking through the DataStream and copying.
        std::uint32_t stream_size = data_size();
        for ( auto & ptr : bootstrap_row )
            ptr = &datum(0) + ( rand() % stream_size );
    }

    template<typename data_t>
    void Bootstrapper<data_t>::bootstrap( data_t (*func) (const data_t) ) const
    {
        // Use an arbitrary function to calculate the bootstrap.
        // This will take the average of func applied to the 
        // bootstrap samples from the DataStream.
        for ( std::uint32_t row = 0, nrows = num_bootstraps; row != nrows; ++row )
        {
            bootstrap_statistics[row] = 0.;
            for ( const auto & ptr : bootstrap_samples -> row_reference(row) )
                bootstrap_statistics[row] += func( *ptr );
            
            bootstrap_statistics[row] /= static_cast<data_t>( num_samples_per_bootstrap );
        }
    }

    // End resampling definitions
    /* ======================================================= */
    
}

#endif