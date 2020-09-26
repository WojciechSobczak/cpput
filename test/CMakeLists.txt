cmake_minimum_required (VERSION 3.8)
project ("test")

add_executable(${PROJECT_NAME}
    "main.cpp"
)

add_dependencies(${PROJECT_NAME} "core")
target_include_directories(${PROJECT_NAME} PRIVATE "../core/include/")
target_link_libraries(${PROJECT_NAME} "core")