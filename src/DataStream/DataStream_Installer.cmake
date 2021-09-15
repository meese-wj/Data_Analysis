message(STATUS "Opening installation settings.")
# Load GNU variables to use:
#   * CMAKE_INSTALL_LIBDIR
#   * CMAKE_INSTALL_BINDIR
#   * CMAKE_INSTALL_INCLUDEDIR
include(GNUInstallDirs)

set(cmake_config_in   ${CMAKE_CURRENT_SOURCE_DIR}/${install_lib_name}_Config.cmake.in)
set(cmake_config_out  ${CMAKE_CURRENT_BINARY_DIR}/${install_lib_name}Config.cmake)
set(cmake_version_out ${CMAKE_CURRENT_BINARY_DIR}/${install_lib_name}_ConfigVersion.cmake)
set(cmake_install_file ${install_lib_name}_Targets.cmake)
set(cmake_install_dest ${CMAKE_INSTALL_LIBDIR}/cmake/${install_lib_name})

set(install_targ "${install_namespace}_DataStream")
add_library(${install_targ} INTERFACE)
target_include_directories(${install_targ} INTERFACE  
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

install(TARGETS ${install_targ}
        EXPORT ${install_lib_name}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES datastream.hpp 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT ${install_lib_name}
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