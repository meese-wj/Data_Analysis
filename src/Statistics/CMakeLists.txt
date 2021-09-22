# Add the headers to the install
list(APPEND install_headers ${CMAKE_CURRENT_LIST_DIR}/measures_of_center.hpp)
set(install_headers ${install_headers} PARENT_SCOPE)

# This is just to be sure the library
# compiles successfully
add_library(Statistics 
            measures_of_center.cpp)


# Define the testing directory and include it
set(Stats_Tests_DIR "${CMAKE_BINARY_DIR}/Testing/bin/Statistics")
add_subdirectory(Tests)

list(APPEND project_include_dirs ${CMAKE_CURRENT_LIST_DIR})
set(project_include_dirs ${project_include_dirs} PARENT_SCOPE)
target_include_directories(Statistics PUBLIC ${project_include_dirs})