cmake_minimum_required(VERSION 3.8)
project("cpput")
set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC
    "src/signaled_variable.hpp" "src/signaled_variable.cpp"
    "src/signaled_variable_def.hpp" "src/signaled_variable_def.cpp"
    "src/defer.hpp" "src/defer.cpp"
    "src/defer_throw.hpp" "src/defer_throw.cpp" 
    "src/dummy_var_macro.hpp"
 "src/cpput.hpp")

if (DEV_BUILD)
    add_executable("test" "main.cpp")
    target_link_libraries("test" ${PROJECT_NAME})
endif()