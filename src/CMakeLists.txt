set(project_include_dirs "")
set(install_namespace "Data_Analysis")
set(install_headers "")
set(install_location ${CMAKE_INSTALL_PREFIX})
get_filename_component(subdir ${install_location} NAME)
if ( NOT ${subdir} STREQUAL ${install_namespace} )
    # Append the subdirectory to the CMake Install Prefix only once
    # as it is saved in the Cache
    set(CMAKE_INSTALL_PREFIX ${install_location}/${install_namespace} CACHE PATH "Manually force install folder substructure." FORCE)
endif()

add_subdirectory(DataStream)
add_subdirectory(DataFiles)
add_subdirectory(Statistics)

add_executable(DataAnalysis main.cpp)
target_include_directories(DataAnalysis PUBLIC ${project_include_dirs})

target_link_libraries(DataAnalysis
                      Statistics
                      DataFiles
                      DataStreams)


# Install Data Analysis headers
message(STATUS "Headers files to install:")
list(APPEND CMAKE_MESSAGE_INDENT "    ")
foreach(header ${install_headers})
    message(STATUS "${header}")
endforeach()
list(POP_BACK CMAKE_MESSAGE_INDENT)

include(Data_Analysis_Installer.cmake)