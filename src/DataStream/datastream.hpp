#ifndef DATASTREAM
#define DATASTREAM
// Use this file to define the DataStream
// base class to be used or inherited later
// on in Data Analysis
//
// This DataStream is a contiguous chunk of 
// memory.

#include <cassert>
#include <cstdint>
#include <vector>

namespace DataStreams
{
    template<typename data_t>
    class DataStream
    {
        public:
            DataStream() = default;
            virtual ~DataStream() { delete [] data_copy; }
            
            // Define some inline const getters
            const data_t * data_start() const { return _start; }
            const data_t * data_end()   const { return _end;   }
            std::uint32_t  data_size()  const { return _size;  }
            const data_t datum( const std::uint32_t idx ) const 
            {
                #ifndef NDEBUG
                    // Check that the index is within bounds
                    // This will be slow in Debug mode.
                    assert( _start + idx < _end /* ERROR: index out of range in DataStream */ ); 
                #endif // DEBUG
                return *(_start + idx); 
            } 

            // Declare data import functions
            // Contiguous imports
            virtual void data_import( const data_t * const start,
                                      const data_t * const end );
            virtual void data_import( const data_t * const start,
                                      const std::uint32_t length );
                            
            virtual void data_import( const std::vector<data_t> & data );
            // Non-contiguous imports
            virtual void data_import( const data_t * const * const start,
                                      const data_t * const * const end );
            virtual void data_import( const data_t * const * const start,
                                      const std::uint32_t length );

            virtual void data_import( const std::vector<data_t*> & data );

        private:
            const data_t * _start = nullptr;
            const data_t * _end   = nullptr;
            std::uint32_t _size;

            data_t * data_copy = nullptr;
    };

    /* ******************************************************* */
    // Begin setup function definitions
    
        /* All defined inline */

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
        delete [] data_copy; // Delete previous copy
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
}


#endif // DATASTREAM