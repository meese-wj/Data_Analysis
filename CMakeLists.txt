cmake_minimum_required(VERSION 3.15)
project(Data_Analysis)

string(TIMESTAMP cmake_time "%Y-%m-%d: %H:%M:%S")
message(STATUS "CMake Configure Time: ${cmake_time}")

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
message(STATUS "CMake Source Location: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMake Binary Location: ${CMAKE_BINARY_DIR}")
message(STATUS "CMake Runtime Output Location: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

enable_testing()
add_subdirectory(src)

set(test_var "directory/name.cpp")
get_filename_component(dirname ${test_var} DIRECTORY)
get_filename_component(flname ${test_var} NAME)
message(STATUS "Directory ${dirname}")
message(STATUS "Filename ${flname}")