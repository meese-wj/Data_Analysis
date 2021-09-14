// Implementation file for the base DataStream
#include "datastream.hpp"

namespace DataStreams
{
    /* ******************************************************* */
    // Begin setup function definitions
    template<typename data_t>
    DataStream<data_t>::~DataStream()
    {
        delete [] data_copy;
    }

    // End setup function definitions
    /* ======================================================= */
    
    /* ******************************************************* */
    // Begin import functions
    template<typename data_t>
    void DataStream<data_t>::data_import( const data_t * const start, 
                                          const data_t * const end )
    {
        // Import the contiguous C-style array
        // directly into _start and _end.
        _start = start;
        _end = end;
        _size = static_cast<std::uint32_t>( end - start );
    }
    
    template<typename data_t>
    void DataStream<data_t>::data_import( const data_t * const start, 
                                          const std::uint32_t length )
    {
        // Overloaded C-style data import for when
        // the size is specified instead of the end
        data_import( start, start + length );
    }

    template<typename data_t>
    void DataStream<data_t>::data_import( const std::vector<data_t> & data )
    {
        // Wrapper for STL vector
        data_import( data.data(), data.data() + data.size() );
    }
    
    template<typename data_t>
    void DataStream<data_t>::data_import( const data_t * const * const start, 
                                          const data_t * const * const end )
    {
        // Here we import a C-style array of pointers to
        // non-contiguous data and COPY it into
        // data_copy to make it contiguous.
        std::uint32_t data_length = static_cast<std::uint32_t>( end - start );
        data_copy = new data_t [data_length](); // Now it must be deleted.
        for ( std::uint32_t idx = 0; idx != data_length; ++idx )
            data_copy[idx] = *( *( start + idx ) );
        
        data_import( data_copy, data_copy + data_length );
    }

    template<typename data_t>
    void DataStream<data_t>::data_import( const data_t * const * const start, 
                                          const std::uint32_t length )
    {
        // Overloaded of C-style non-contiguous 
        // data_import for when the size is specified
        data_import( start, start + length );
    }
    
    template<typename data_t>
    void DataStream<data_t>::data_import( const std::vector<data_t*> & data )
    {
        // Wrapper around the non-contiguous import for STL vectors
        data_import( data.data(), data.data() + data.size() );
    }
    // End import functions
    /* ======================================================= */

    namespace TemplateDeclarations
    {
        void Declaration()
        {
            // Use this dummy function to declare a bunch
            // of different DataStream types.
            DataStream<int> dsi;
            DataStream<std::uint8_t> dsus;
            DataStream<std::uint32_t> dsui;
            DataStream<std::uint64_t> dsul;
            DataStream<long> dsl;
            
            DataStream<float> dsf;
            DataStream<double> dsd;
            DataStream<long double> dsld;
        }
    }
}