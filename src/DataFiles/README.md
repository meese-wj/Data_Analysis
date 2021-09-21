# DataFiles Library

This is a summary overview of the named template classes in this library. All types are defined within the ```namespace DataFiles```.

## DataTable
```c++
class DataTable<data_t>
```
This is a `std::vector` container of `std::vector<data_t>` pointers stored in row-major format. That is, each element of the `DataTable` points to a row containing a `std::vector` of `data_t` data ordered column-wise.

The `DataTable` class is meant to store and manipulate data which interfaces with CSV-type data files upon reading or writing. Many of the members are overloaded to handle `data_t *`, `data_t **`, or `std::vector<data_t> &` arguments. A list of public members are given below (arguments are suppressed for clarity):

* Access `DataTable` sizes:
    * `number_rows(), number_columns(), number_elements()`
* Access data:
    * `datum(), row_vector(), row_reference()`
* Import data:
    * `column_copy(), row_copy(), data_copy(), data_import()`
* Append data:
    * `append_column(), append_row()`
* Resize `DataTable`:
    * `resize_rows(), resize_columns(), resize()`
* Element-wise `DataTable` operations
    * `operators: +=, -=, *=, /=`
    * `manipulate()`
