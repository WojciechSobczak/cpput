# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.8)
project("cpput")
set(CMAKE_CXX_STANDARD 20)

add_subdirectory("./core")
add_subdirectory("./test")

