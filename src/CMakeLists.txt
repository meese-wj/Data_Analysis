add_subdirectory(Statistics)

add_executable(DataAnalysis main.cpp)

target_link_libraries(DataAnalysis
                      Statistics)