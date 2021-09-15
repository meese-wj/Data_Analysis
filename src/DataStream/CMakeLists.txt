add_library(DataStreams
            datastream.cpp)

# Add testing functionality
set(DataStream_Tests_DIR "${CMAKE_BINARY_DIR}/Testing/bin/DataStream")
add_subdirectory(Tests)