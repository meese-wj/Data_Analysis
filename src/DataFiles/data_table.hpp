#ifndef DATAFILES_DATA_TABLE
#define DATAFILES_DATA_TABLE
// Template class for a data table.
// The tables are a simple row-major
// ordered array of STL vector pointers
//
// Data ownership is kept track of with the 
// data_owned char. If the DataTable does own
// its data, it will delete its data when the
// destructor is called.
//

#include <cstdint>
#include <vector>

namespace DataFiles
{
    template<typename data_t>
    class DataTable
    {
        public:
            DataTable() = default;
            DataTable( const std::uint32_t rows, const std::uint32_t cols ) : num_rows(rows), num_cols(cols), table(rows)
            {
                for ( auto & row : table ) row = new std::vector<data_t>(num_cols);
            }
            virtual ~DataTable() 
            { 
                for ( auto & row : table ) delete row;
            }

            // Accessing functions
            std::uint32_t number_rows() const { return num_rows; }
            std::uint32_t number_columns() const { return num_cols; }
            std::uint32_t number_elements() const { return number_rows() * number_columns(); }
            data_t & datum( const std::uint32_t row, const std::uint32_t col ) 
            { 
                return (*table[row])[col]; 
            }
            std::vector<data_t>* const row( const std::uint32_t row ) const
            {
                return table[row];
            }

            // Data import function declarations
            // These currently assume the incoming data
            // is of the proper size.
            void data_import( data_t * const array );


            // Resizing function declarations
            void resize_rows( const std::uint32_t new_rows );
            void resize_columns( const std::uint32_t new_cols );
            void resize( const std::uint32_t new_rows, const std::uint32_t new_cols );

        private:
            std::uint32_t num_rows;
            std::uint32_t num_cols;
            std::vector<std::vector<data_t>*> table;

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
    void DataTable<data_t>::resize_rows( const std::uint32_t new_rows )
    {
        if ( num_rows == new_rows ) return;  // null resize

        table.resize( new_rows );
        // Only allocate memory if current rows < new rows
        for ( std::uint32_t row = num_rows; row < new_rows; ++row )
            table[row] = new std::vector<data_t>( num_cols );
        
        num_rows = new_rows;
        return;
    }

    template<typename data_t>
    void DataTable<data_t>::resize_columns( const std::uint32_t new_cols )
    {
        if ( num_cols == new_cols ) return; // null resize

        for ( const auto & row : table )
            row -> resize( new_cols );
        
        num_cols = new_cols;
        return;
    }

    template<typename data_t>
    void DataTable<data_t>::resize( const std::uint32_t new_rows, const std::uint32_t new_cols )
    {
        // Change the columns first, and then move onto the rows
        resize_columns( new_cols );
        resize_rows( new_rows );        
    }
    
    // End Resizing Function Definitions
    /* ====================================================================================== */

} // namespace DataFiles

#endif  // DATAFILES_DATA_TABLE