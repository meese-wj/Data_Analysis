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
            std::uint32_t size() const { return num_elements; }
            std::uint32_t rows() const { return num_rows; }
            std::uint32_t columns() const { return num_cols; }
            std::uint32_t index( const std::uint32_t row, const std::uint32_t col, 
                                 const std::uint32_t ncols = num_cols ) const { return row * ncols + col; }
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
            void resize_rows( const std::uint32_t new_rows, const std::uint8_t will_be_owned = true );
            void resize_columns( const std::uint32_t new_cols, const std::uint8_t will_be_owned = true );
            void resize( const std::uint32_t new_rows, const std::uint32_t new_cols, const std::uint8_t will_be_owned = true );

        private:
            std::uint32_t data_owned = false;
            std::uint32_t num_rows;
            std::uint32_t num_cols;
            std::uint32_t num_elements;
            data_t * table = nullptr;

    };  // class DataTable

    /* ************************************************************************************** */
    // Begin Initialization Function Definitions

        /* Currently all defined inline */
    
    // End Initialization Function Definitions
    /* ====================================================================================== */
    
    /* ************************************************************************************** */
    // Begin Accessing Function Definitions

        /* Currently all defined inline */
    
    // End Accessing Function Definitions
    /* ====================================================================================== */
    
    /* ************************************************************************************** */
    // Begin Data Import Function Definitions

    template<typename data_t>
    void DataTable<data_t>::data_import( data_t * const array )
    {
        
    }
    
    // End Data Import Function Definitions
    /* ====================================================================================== */
    
    /* ************************************************************************************** */
    // Begin Resizing Function Definitions

    template<typename data_t>
    void DataTable<data_t>::resize_rows( const std::uint32_t new_rows, const std::uint8_t will_be_owned  )
    {
        if ( num_rows == new_rows ) return;  // null resize
    }

    template<typename data_t>
    void DataTable<data_t>::resize_columns( const std::uint32_t new_cols, const std::uint8_t will_be_owned )
    {
        if ( num_cols == new_cols ) return;  // null resize

        // Deleting columns is the easy part...
        if ( num_cols > new_cols )
        {
            if (data_owned)
            {
                for ( std::uint32_t row = 0; row != num_rows; ++row )
                {
                    for ( std::uint32_t col = new_cols; col != num_cols; ++col )
                        delete datum( row, col );
                }
            }
        }
        else
        {
            data_owned = will_be_owned;
            if (data_owned)
            {

            }
        }

        num_cols = new_cols;
        num_elements = num_rows * num_cols;
        return;
    }

    template<typename data_t>
    void DataTable<data_t>::resize( const std::uint32_t new_rows, const std::uint32_t new_cols, const std::uint8_t will_be_owned )
    {
        if ( num_rows == new_rows && num_cols == new_cols ) return;  // null resize...

        
    }
    
    // End Resizing Function Definitions
    /* ====================================================================================== */

} // namespace DataFiles

#endif  // DATAFILES_DATA_TABLE