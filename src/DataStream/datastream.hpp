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
}


#endif // DATASTREAM