#ifndef DATASTREAM_TESTER
#define DATASTREAM_TESTER
// This header defines the DataStream tests

#include <iostream>
#include "../datastream.hpp"

namespace DataStream_Tests
{
    using test_t = int;

    int input_data [] = { 0, 1, 2, 3, 4, 5 };
    const std::uint32_t input_size = sizeof(input_data) / sizeof(test_t);
    const std::vector<test_t> vector_input( input_data, input_data + input_size );

    struct DataStream_Tester : public DataStreams::DataStream<test_t>
    {
        test_t ** scattered_data = nullptr;
        std::uint32_t scattered_size = 0;

        DataStream_Tester() : DataStreams::DataStream<test_t>::DataStream()
        {
            // intentionally empty
        }

        ~DataStream_Tester()
        {
            for( std::uint32_t idx = 0; idx != scattered_size; ++idx )
                delete scattered_data[idx];
            delete [] scattered_data;
        }

        bool datastream_equal_array( const test_t * const start_A, const std::uint32_t size_A )
        {
            if ( size_A != data_size() ) return false;

            bool equal = true;
            for ( std::uint32_t idx = 0; idx != size_A; ++idx )
                equal *= ( *(start_A + idx) == datum(idx) );
            
            return equal;
        }

        void test_contiguous_imports( )
        {
            std::cout << "Testing data_import( const test_t * const, const test_t * const )... ";
            data_import( input_data, input_data + input_size );
            assert( datastream_equal_array( input_data, input_size ) );
            
            std::cout << "\nTesting data_import( const test_t * const, const std::uint32_t )... ";
            data_import( input_data, input_size );
            assert( datastream_equal_array( input_data, input_size ) );
            
            std::cout << "\nTesting data_import( const std::vector<test_t> & )... ";
            data_import( vector_input );
            assert( datastream_equal_array( input_data, input_size ) );

            std::cout << "\nAll contiguous import tests passed.\n";
        }

        void scatter_array( test_t **& scattered, 
                            const test_t * const array, 
                            const std::uint32_t size )
        {
            // Scatter the contiguous array throughout RAM
            // and store the locations in the contiguous
            // scattered array
            delete [] scattered;
            scattered = new test_t * [ input_size ];

            // Define the step size to be 32KB of memory
            std::uint32_t step_size = (8 << 12) * sizeof(test_t) / sizeof(float); 
            delete [] scattered_data;
            scattered_size = input_size * step_size;
            scattered = new test_t* [ scattered_size ];
            std::cout << "Building scattered array of size: " << sizeof(scattered) << " bytes.";
            
            test_t value = 0;
            for ( std::uint32_t idx = 0; idx != scattered_size; ++idx )
            {
                value =  input_data[ idx / input_size ] * (idx % step_size == 0); // Store the input_data at these locations
                value += ( -static_cast<int>(idx) ) * (idx % step_size != 0);     // Put garbage in the other locations

                *scattered_data[idx] = value;          // store the value in scattered data
            }

            std::cout << "\nScatter complete. Now building contiguous array of pointers...";
            // Store the addresses in the scattered array
            for ( std::uint32_t idx = 0; idx != scattered_size; idx += step_size )
                scattered[idx / step_size] = scattered_data[idx];

            std::cout << "Function: " << __FUNCTION__ << " completed.\n";
        }

        void test_noncontiguous_imports()
        {
            test_t ** scattered = nullptr;
            scatter_array(scattered, input_data, input_size);
            const std::vector<test_t*> scattered_vector( scattered, scattered + input_size );
            
            std::cout << "\nTesting data_import( const test_t * const * const, const test_t * const * const )... ";
            data_import( scattered, scattered + input_size );
            assert( datastream_equal_array( input_data, input_size ) );

            std::cout << "\nTesting data_import( const test_t * const * const, const std::uint32_t )... ";
            data_import( scattered, input_size );
            assert( datastream_equal_array( input_data, input_size ) );

            std::cout << "\nTesting data_import( const std::vector<test_t*> & )... ";
            data_import( scattered_vector );
            assert( datastream_equal_array( input_data, input_size ) );

            std::cout << "\nAll non-contiguous import tests passed.\n";
            delete [] scattered;
        }

    };
}

#endif // DATASTREAM_TESTER