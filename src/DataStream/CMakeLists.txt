# Add headers to install headers
list(APPEND install_headers ${CMAKE_CURRENT_LIST_DIR}/datastream.hpp)
set(install_headers ${install_headers} PARENT_SCOPE)

# Add this library to just be sure 
# the DataStreams compile
add_library(DataStreams
            datastream.cpp)

# Add testing functionality
set(DataStream_Tests_DIR "${CMAKE_BINARY_DIR}/Testing/bin/DataStream")
add_subdirectory(Tests)

list(APPEND project_include_dirs ${CMAKE_CURRENT_LIST_DIR})
set(project_include_dirs ${project_include_dirs} PARENT_SCOPE)
target_include_directories(DataStreams PUBLIC ${project_include_dirs})