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

