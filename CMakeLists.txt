cmake_minimum_required(VERSION 3.19)
project("cpput")
set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC
    "src/signaled_variable.cpp"
    "src/signaled_variable_def.cpp"
    "src/string.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "./include/")

if (${CPPUT_DEV_BUILD})
    add_executable("test" "main.cpp")
    target_include_directories("test" PRIVATE "./include/")
    target_link_libraries("test" ${PROJECT_NAME})
endif()