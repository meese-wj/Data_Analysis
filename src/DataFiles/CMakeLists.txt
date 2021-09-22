# Add headers to install headers
list(APPEND install_headers ${CMAKE_CURRENT_LIST_DIR}/data_table.hpp)
set(install_headers ${install_headers} PARENT_SCOPE)

add_library(DataFiles
            data_table.cpp)

list(APPEND project_include_dirs ${CMAKE_CURRENT_LIST_DIR})
set(project_include_dirs ${project_include_dirs} PARENT_SCOPE)
target_include_directories(DataFiles PUBLIC ${project_include_dirs})