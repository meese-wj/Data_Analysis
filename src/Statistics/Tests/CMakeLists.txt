# Add testing functionality for the Statistics directory
add_executable(MoC_Test moc_test.cpp)
target_link_libraries(MoC_Test Statistics)
set_target_properties(MoC_Test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${Stats_Tests_DIR})
add_test(NAME MoC_Test COMMAND MoC_Test WORKING_DIRECTORY ${Stats_Tests_DIR})
message(STATUS "Find MoC_Test in ${Stats_Tests_DIR}")