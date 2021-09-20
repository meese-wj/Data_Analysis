# Add headers to install headers
list(APPEND install_headers datastream.hpp)
set(install_headers ${install_headers} PARENT_SCOPE)

# Add this library to just be sure 
# the DataStreams compile
add_library(DataStreams
            datastream.cpp)

# Add testing functionality
set(DataStream_Tests_DIR "${CMAKE_BINARY_DIR}/Testing/bin/DataStream")
add_subdirectory(Tests)

# Add an installation for the datastream library
# set(install_lib_name Data_Analysis_DataStream)
# set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/${install_lib_name}")
# message(STATUS "CMake Install Location: ${CMAKE_INSTALL_PREFIX}")
# include(DataStream_Installer.cmake)