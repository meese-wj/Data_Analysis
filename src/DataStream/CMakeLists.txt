add_library(DataStream
            datastream.cpp)

# Add testing functionality
set(DataStream_Test_DIR "${CMAKE_BINARY_DIR}/Testing/bin/DataStream")
add_subdirectory(Tests)