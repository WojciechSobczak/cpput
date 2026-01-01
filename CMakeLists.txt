cmake_minimum_required(VERSION 4.2.0)
project(test C CXX)
set(CMAKE_CXX_STANDARD 23)

add_library(cpput STATIC
    "src/signaled_variable.cpp"
    "src/signaled_variable_def.cpp"
    "src/string.cpp"
    "src/cpput.hpp"
    "src/class_macros.hpp"
    "src/defer.hpp"
    "src/dummy_var_macro.hpp"
    "src/result.hpp"
    "src/signaled_variable.hpp"
    "src/signaled_variable_def.hpp"
    "src/string.hpp"
    "src/synchronized.hpp"
)

if (${CPPUT_DEV_BUILD})
    add_executable("test" "main.cpp")
    target_link_libraries("test" cpput)
    target_include_directories("test" PRIVATE "src")
endif()
