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
            std::vector<data_t>* const row_vector( const std::uint32_t row ) const
            {
                return table[row];
            }

            // Data import function declarations
            void column_copy( const std::uint32_t column, const data_t * const column_start, const data_t * const column_end );
            void column_copy( const std::uint32_t column, const data_t * const column_start, const std::uint32_t column_size );
            void column_copy( const std::uint32_t column, const std::vector<data_t> & column_vector );
            
            void row_copy( const std::uint32_t row, const data_t * const row_start, const data_t * const row_end );
            void row_copy( const std::uint32_t row, const data_t * const row_start, const std::uint32_t row_size );
            void row_copy( const std::uint32_t row, const std::vector<data_t> & row_vector );

            void data_copy( const data_t * const array, const std::uint32_t array_rows, const std::uint32_t array_cols );
            void data_copy( const DataTable<data_t> * const other_table );
            
            void data_import( const data_t * const array, const std::uint32_t array_rows, const std::uint32_t array_cols );

            // Data column appenders
            void append_column( const data_t * const column_start, const data_t * const column_end );
            void append_column( const data_t * const column_start, const std::uint32_t column_size)
            { 
                append_column( column_start, column_start + column_size ); 
            }
            void append_column( const std::vector<data_t> & column ) { append_column( column.data(), column.data() + column.size() ); }
            
            // Data row appenders
            void append_row( const data_t * const row_start, const data_t * const row_end );
            void append_row( const data_t * const row_start, const std::uint32_t row_size)
            { 
                append_row( row_start, row_start + row_size ); 
            }
            void append_row( const std::vector<data_t> & row ) { append_row( row.data(), row.data() + row.size() ); }

            // Resizing function declarations
            void resize_rows( const std::uint32_t new_rows );
            void resize_columns( const std::uint32_t new_cols );
            void resize( const std::uint32_t new_rows, const std::uint32_t new_cols );

            // Element-wise in-place DataTable operations
            void operator += (const DataTable<data_t> & other_data);
            void operator -= (const DataTable<data_t> & other_data);
            void operator *= (const DataTable<data_t> & other_data);
            void operator /= (const DataTable<data_t> & other_data);

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
    void DataTable<data_t>::column_copy( const std::uint32_t column, const data_t * const column_start, const data_t * const column_end )
    {
        assert( column <= number_columns() /* ERROR: the column cannot be copied into the specified column. */ );
        if ( column == number_columns() ) resize_columns( number_columns() + 1 );

        std::uint32_t column_size = column_end - column_start;
        assert( column_size == number_rows() /* ERROR: column to be copied is of a different size. */ );
        for (std::uint32_t row = 0; row != column_size; ++row)
            datum(row, column) = *(column_start + row);
    }
    
    template<typename data_t>
    void DataTable<data_t>::column_copy( const std::uint32_t column, const data_t * const column_start, const std::uint32_t column_size )
    {
        column_copy( column, column_start, column_start + column_size );
    }
    
    template<typename data_t>
    void DataTable<data_t>::column_copy( const std::uint32_t column, const std::vector<data_t> & column_vector )
    {
        column_copy( column, column_vector.data(), column_vector.data() + column_vector.size() );
    }

    template<typename data_t>
    void DataTable<data_t>::row_copy( const std::uint32_t row, const data_t * const row_start, const data_t * const row_end )
    {
        assert( row <= number_rows() /* ERROR: the row cannot be copied into the specified row. */ );
        if ( row == number_rows() ) resize_rows( number_rows() + 1 );

        std::uint32_t row_size = row_end - row_start;
        assert( row_size == number_columns() /* ERROR: row to be copied is of a different size. */ );
        for (std::uint32_t col = 0; col != row_size; ++col)
            datum(row, col) = *(row_start + col);
    }

    template<typename data_t>
    void DataTable<data_t>::row_copy( const std::uint32_t row, const data_t * const row_start, const std::uint32_t row_size )
    {
        row_copy( row, row_start, row_start + row_size );
    }
    
    template<typename data_t>
    void DataTable<data_t>::row_copy( const std::uint32_t row, const std::vector<data_t> & row_vector )
    {
        row_copy( row, row_vector.data(), row_vector.data() + row_vector.size() );
    }

    // Import and resize the table to match
    // the given array dimensions. This function
    // copies the data into the table.
    template<typename data_t>
    void DataTable<data_t>::data_copy( const data_t * const array, const std::uint32_t array_rows, const std::uint32_t array_cols )
    {
        resize(array_rows, array_cols);
        std::uint32_t index = 0;
        for (std::uint32_t row = 0; row != num_rows; ++row)
        {
            index = row * num_cols;
            for (std::uint32_t col = 0; col != num_cols; ++col, ++index)
            {
                datum(row, col) = array[ index ];
            }
        }
    }
    
    // Import an existing DataTable's table into
    // this one by copying the data.
    template<typename data_t>
    void DataTable<data_t>::data_copy( const DataTable<data_t> * const other_table )
    {
        resize(other_table -> number_rows(), other_table -> number_columns());
        for (std::uint32_t row = 0; row != num_rows; ++row)
        {
            for (std::uint32_t col = 0; col != num_cols; ++col)
            {
                datum(row, col) = other_table -> datum(row, col);
            }
        }
    }
    
    // Import and resize the table to match
    // the given array dimensions. This function
    // assigns the row vectors to point to the 
    // existing arrays.
    template<typename data_t>
    void DataTable<data_t>::data_import( const data_t * const array, const std::uint32_t array_rows, const std::uint32_t array_cols )
    {
        resize(array_rows, array_cols);
        for (std::uint32_t row = 0; row != num_rows; ++row)
        {
            *row_vector( row ) = std::vector<data_t>( array + row * num_cols, array + (row + 1) * num_cols );
        }

        // TODO: Should I delete the array pointer? 
        // If so, it can't be a const pointer probably...
        // delete array;
    }

    // Append the column to the DataTable
    template<typename data_t>
    void DataTable<data_t>::append_column( const data_t * const column_start, const data_t * const column_end )
    {
        resize_columns( number_columns() + 1 );
        std::uint32_t column_size = column_end - column_start;
        assert( column_size == number_rows() /* ERROR: cannot append column of different size */ );
        for (std::uint32_t row = 0; row != column_size; ++row)
        {
            datum( row, number_columns() - 1 ) = *(column_start + row);
        }
    }
    
    // Append the row to the DataTable
    template<typename data_t>
    void DataTable<data_t>::append_row( const data_t * const row_start, const data_t * const row_end )
    {
        resize_rows( number_rows() + 1 );
        std::uint32_t row_size = row_end - row_start;
        assert( row_size == number_columns() /* ERROR: cannot append column of different size */ );
        for (std::uint32_t row = 0; row != row_size; ++row)
        {
            datum( row, number_columns() - 1 ) = *(row_start + row);
        }
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
    
    /* ************************************************************************************** */
    // Begin Element-wise In-place Operator Definitions

    template<typename data_t>
    void DataTable<data_t>::operator += ( const DataTable<data_t> & other_table)
    {
        assert( number_rows() == other_table.number_rows() /* ERROR: row mismatch on += */ );
        assert( number_columns() == other_table.number_columns() /* ERROR: column mismatch on += */ );

        std::uint32_t nrows = number_rows(), ncols = number_columns();
        for (std::uint32_t row = 0; row != nrows; ++row)
            for (std::uint32_t col = 0; col != ncols; ++col)
                datum(row, col) += other_table.datum(row, col);
    }
    
    template<typename data_t>
    void DataTable<data_t>::operator -= ( const DataTable<data_t> & other_table)
    {
        assert( number_rows() == other_table.number_rows() /* ERROR: row mismatch on -= */ );
        assert( number_columns() == other_table.number_columns() /* ERROR: column mismatch on -= */ );

        std::uint32_t nrows = number_rows(), ncols = number_columns();
        for (std::uint32_t row = 0; row != nrows; ++row)
            for (std::uint32_t col = 0; col != ncols; ++col)
                datum(row, col) -= other_table.datum(row, col);
    }
    
    template<typename data_t>
    void DataTable<data_t>::operator *= ( const DataTable<data_t> & other_table)
    {
        assert( number_rows() == other_table.number_rows() /* ERROR: row mismatch on *= */ );
        assert( number_columns() == other_table.number_columns() /* ERROR: column mismatch on *= */ );

        std::uint32_t nrows = number_rows(), ncols = number_columns();
        for (std::uint32_t row = 0; row != nrows; ++row)
            for (std::uint32_t col = 0; col != ncols; ++col)
                datum(row, col) *= other_table.datum(row, col);
    }
    
    template<typename data_t>
    void DataTable<data_t>::operator /= ( const DataTable<data_t> & other_table)
    {
        assert( number_rows() == other_table.number_rows() /* ERROR: row mismatch on /= */ );
        assert( number_columns() == other_table.number_columns() /* ERROR: column mismatch on /= */ );

        std::uint32_t nrows = number_rows(), ncols = number_columns();
        for (std::uint32_t row = 0; row != nrows; ++row)
            for (std::uint32_t col = 0; col != ncols; ++col)
                datum(row, col) /= other_table.datum(row, col);
    }

    // End Element-wise In-place Operator Definitions
    /* ====================================================================================== */

} // namespace DataFiles

#endif  // DATAFILES_DATA_TABLE