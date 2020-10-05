cmake_minimum_required (VERSION 3.8)
project ("core")

add_library(${PROJECT_NAME} STATIC
    "include/cpput/signaled_variable.hpp" "src/signaled_variable.cpp"
 "include/cpput/defer.hpp" "src/defer.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE "./include/cpput/")

