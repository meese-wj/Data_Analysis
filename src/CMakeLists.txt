set(install_namespace "Data_Analysis")
set(install_headers "")

add_subdirectory(DataStream)
add_subdirectory(DataFiles)
add_subdirectory(Statistics)

add_executable(DataAnalysis main.cpp)

target_link_libraries(DataAnalysis
                      Statistics
                      DataFiles
                      DataStreams)


# Install Data Analysis headers
message(STATUS "Headers files to install: ${install_headers}")
include(Data_Analysis_Installer.cmake)