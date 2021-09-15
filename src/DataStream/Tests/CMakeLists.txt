add_executable(DataStream_Contiguous_Import_Test 
               contiguous_import_test.cpp)
target_link_libraries(DataStream_Contiguous_Import_Test DataStreams)
set_target_properties(DataStream_Contiguous_Import_Test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DataStream_Tests_DIR})
add_test(NAME DataStream_Contiguous_Import_Test
         COMMAND DataStream_Contiguous_Import_Test
         WORKING_DIRECTORY ${DataStream_Tests_DIR} )
         
add_executable(DataStream_Noncontiguous_Import_Test 
               noncontiguous_import_test.cpp)
target_link_libraries(DataStream_Noncontiguous_Import_Test DataStreams)
set_target_properties(DataStream_Noncontiguous_Import_Test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${DataStream_Tests_DIR})
add_test(NAME DataStream_Noncontiguous_Import_Test
        COMMAND DataStream_Noncontiguous_Import_Test
        WORKING_DIRECTORY ${DataStream_Tests_DIR} )

message(STATUS "Find DataStream_Tests(s) in ${DataStream_Tests_DIR}")
