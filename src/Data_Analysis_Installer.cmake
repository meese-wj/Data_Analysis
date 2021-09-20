message(STATUS "Opening ${install_namespace} installation settings.")
message(STATUS "CMAKE INSTALL PREFIX = ${CMAKE_INSTALL_PREFIX}")
# Load GNU variables to use:
#   * CMAKE_INSTALL_LIBDIR
#   * CMAKE_INSTALL_BINDIR
#   * CMAKE_INSTALL_INCLUDEDIR
include(GNUInstallDirs)

set(cmake_config_in   ${CMAKE_CURRENT_SOURCE_DIR}/${install_namespace}_Config.cmake.in)
set(cmake_config_out  ${CMAKE_CURRENT_BINARY_DIR}/${install_namespace}Config.cmake)
set(cmake_version_out ${CMAKE_CURRENT_BINARY_DIR}/${install_namespace}_ConfigVersion.cmake)
set(cmake_install_file ${install_namespace}_Targets.cmake)
set(cmake_install_dest ${CMAKE_INSTALL_LIBDIR}/cmake/${install_namespace})

set(install_targ "${install_namespace}")
add_library(${install_targ} INTERFACE)
target_include_directories(${install_targ} INTERFACE  
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

install(TARGETS ${install_targ}
        EXPORT ${install_namespace}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

message(STATUS "Adding the following header subfolder structure to the installation:")
list(APPEND CMAKE_MESSAGE_INDENT "    ")
foreach(header ${install_headers})
get_filename_component(filename ${header} NAME)
get_filename_component(dirname ${header} DIRECTORY)
get_filename_component(dirname ${dirname} NAME)
message(STATUS "Header: ${dirname}/${filename}")
install(FILES ${header}
DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${dirname})       
endforeach()
list(POP_BACK CMAKE_MESSAGE_INDENT)

# install(FILES ${install_headers} 
#         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${install_namespace}
        FILE ${cmake_install_file}
        NAMESPACE "${install_namespace}::"
        DESTINATION ${cmake_install_dest})

# Add config helpers for 
# configure_package_config_file()
include(CMakePackageConfigHelpers)

configure_package_config_file(${cmake_config_in}
                              ${cmake_config_out}
                              INSTALL_DESTINATION 
                              ${cmake_install_dest})

install(FILES 
        ${cmake_config_out}
        ${cmake_version_out}
        DESTINATION 
        ${cmake_install_dest})

# Create a Package Version
set(version 1.0)

write_basic_package_version_file(${cmake_version_out}
                                VERSION ${version}
                                COMPATIBILITY AnyNewerVersion)