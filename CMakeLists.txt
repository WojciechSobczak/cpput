cmake_minimum_required(VERSION 3.19)
project(cpput)
set(CMAKE_CXX_STANDARD 23)

add_library(cpput STATIC
    "src/signaled_variable.cpp"
    "src/signaled_variable_def.cpp"
    "src/string.cpp"
)

if (${CPPUT_DEV_BUILD})
    add_executable("test" "main.cpp")
    target_link_libraries("test" cpput)
    target_include_directories("test" PRIVATE "src")
endif()

###########################
### INSTALLATION TARGET ###
###########################

set(cpput_public_headers
    "src/cpput.hpp"
    "src/class_macros.hpp"
    "src/cpput.hpp"
    "src/defer.hpp"
    "src/dummy_var_macro.hpp"
    "src/result.hpp"
    "src/signaled_variable.hpp"
    "src/signaled_variable_def.hpp"
    "src/string.hpp"
    "src/synchronized.hpp"
)

install(
    TARGETS cpput
    EXPORT cpputTargets
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)
install(FILES ${cpput_public_headers} DESTINATION include/cpput)
install(
    EXPORT cpputTargets
    FILE cpputTargets.cmake
    NAMESPACE cpput::
    DESTINATION lib/cmake/cpput
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "cpputConfigVersion.cmake"
    VERSION "0.0.1"
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES "cpputConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/cpputConfigVersion.cmake"
    DESTINATION lib/cmake/cpput
)
