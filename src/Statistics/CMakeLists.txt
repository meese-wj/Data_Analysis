# This is just to be sure the library
# compiles successfully
add_library(Statistics 
            measures_of_center.cpp)


# Define the testing directory and include it
set(Stats_Tests_DIR "${CMAKE_BINARY_DIR}/Testing/bin/Statistics")
add_subdirectory(Tests)
