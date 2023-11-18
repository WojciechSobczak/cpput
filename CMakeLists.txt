cmake_minimum_required(VERSION 3.19)
project(cpput)
set(CMAKE_CXX_STANDARD 20)

add_library(cpput STATIC
    "src/signaled_variable.cpp"
    "src/signaled_variable_def.cpp"
    "src/string.cpp"
)
add_library(cpput::cpput ALIAS cpput)

if (${CPPUT_DEV_BUILD})
    add_executable("test" "main.cpp")
    target_link_libraries("test" cpput)
endif()


##################################
#### CMake installation stuff ####
##################################

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

if (DEFINED CMAKE_INSTALL_INCLUDEDIR)
    set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}/cpput")
else()
    set(INCLUDE_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/include/cpput")
endif()

if (DEFINED CMAKE_INSTALL_LIBDIR)
    set(BINARIES_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
else()
    set(BINARIES_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/lib")
endif()

cmake_path(GET CMAKE_INSTALL_LIBDIR PARENT_PATH CMAKE_INSTALL_CMAKEDIR)
set(CMAKE_INSTALL_CMAKEDIR "${CMAKE_CURRENT_BINARY_DIR}/CMake")

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/CMake/cpputConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/CMake/cpputConfig.cmake"
    INSTALL_DESTINATION
        ${CMAKE_INSTALL_CMAKEDIR}
    PATH_VARS
        INCLUDE_INSTALL_DIR
        BINARIES_INSTALL_DIR
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/cpputConfigVersion.cmake"
  VERSION 
    0.0.0
  COMPATIBILITY
    ExactVersion
)
file(GLOB_RECURSE CPPUT_HEADER_FILES "*.hpp")
install(
    TARGETS cpput
    EXPORT cpput
    LIBRARY DESTINATION "${BINARIES_INSTALL_DIR}"
)
install(
    DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/src"
    DESTINATION "${INCLUDE_INSTALL_DIR}"
    FILES_MATCHING PATTERN "*.h*"
)
install(
    EXPORT cpput
    NAMESPACE cpput::
    DESTINATION ${CMAKE_INSTALL_CMAKEDIR}
)
install(
  FILES
    "${CMAKE_CURRENT_BINARY_DIR}/cpputConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/cpputConfigVersion.cmake"
  DESTINATION
    "${CMAKE_INSTALL_CMAKEDIR}/"
)



