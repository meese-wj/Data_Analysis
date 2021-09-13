add_library(Statistics 
            measures_of_center.cpp)

# Add testing functionality
set(Stats_Tests_DIR "${CMAKE_BINARY_DIR}/Testing/bin/Statistics")
add_executable(MoC_Test moc_test.cpp)
set_target_properties(MoC_Test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${Stats_Tests_DIR})
add_test(NAME MoC_Test COMMAND MoC_Test WORKING_DIRECTORY ${Stats_Tests_DIR})
message(STATUS "Find MoC_Test in ${Stats_Tests_DIR}")