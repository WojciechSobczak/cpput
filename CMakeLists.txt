cmake_minimum_required(VERSION 3.8)
project("cpput")
set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC
    "src/signaled_variable.hpp" "src/signaled_variable.cpp"
    "src/defer.hpp" "src/defer.cpp"
)

if (DEV_BUILD)
    add_executable("test" "main.cpp")
    target_link_libraries(${PROJECT_NAME})
endif()