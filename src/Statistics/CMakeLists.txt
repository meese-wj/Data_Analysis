# Add the headers to the install
list(APPEND install_headers measures_of_center.hpp)
set(install_headers ${install_headers} PARENT_SCOPE)

# This is just to be sure the library
# compiles successfully
add_library(Statistics 
            measures_of_center.cpp)


# Define the testing directory and include it
set(Stats_Tests_DIR "${CMAKE_BINARY_DIR}/Testing/bin/Statistics")
add_subdirectory(Tests)

# Add an installation for the statistics library
# set(install_lib_name Data_Analysis_Statistics)
# set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/${install_lib_name}")
# message(STATUS "CMake Install Location: ${CMAKE_INSTALL_PREFIX}")
# include(Statistics_Installer.cmake)