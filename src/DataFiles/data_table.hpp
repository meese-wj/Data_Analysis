#ifndef DATAFILES_DATA_TABLE
#define DATAFILES_DATA_TABLE
// Template class for a data table.
// The tables are a simple row-major
// ordered array of size num_rows * num_cols.
//
// Data ownership is kept track of with the 
// data_owned char. If the DataTable does own
// its data, it will delete its data when the
// destructor is called.
//
// I think I'll make then dynamically-sized
// eventually. That or I'll switch to using
// STL vectors... 
// TODO: Undecided, presently (09/16/2021)

#include <cstdint>
#include <vector>

namespace DataFiles
{
    template<typename data_t>
    class DataTable
    {
        public:
            DataTable() = default;
            DataTable( const std::uint32_t rows, const std::uint32_t cols ) : num_rows(rows), num_cols(cols), num_elements(num_rows * num_cols)
            {
                data_owned = true;
                table = new data_t [ num_elements ];
            }
            virtual ~DataTable()
            { 
                if (data_owned)
                    delete [] table; 
            }

            // Accessing functions
            std::uint32_t index( const std::uint32_t row, const std::uint32_t col ) const { return row * num_cols + col; }
            data_t & datum( const std::uint32_t idx ) { return &table[idx]; }
            data_t & datum( const std::uint32_t row, const std::uint32_t col ) 
            { 
                return datum( index( row, col ) ); 
            }

            // Data import function declarations
            // These currently assume the incoming data
            // is of the proper size.
            void data_import( data_t * const array );


            // Resizing function declarations

        private:
            std::uint32_t data_owned = false;
            std::uint32_t num_rows;
            std::uint32_t num_cols;
            std::uint32_t num_elements;
            data_t * table;

    };  // DataTable

}

#endif  // DATAFILES_DATA_TABLE