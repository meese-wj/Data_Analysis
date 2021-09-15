set(install_namespace "Data_Analysis")

add_subdirectory(DataStream)
add_subdirectory(Statistics)

add_executable(DataAnalysis main.cpp)

target_link_libraries(DataAnalysis
                      Statistics)