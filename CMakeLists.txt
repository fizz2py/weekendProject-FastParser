cmake_minimum_required(VERSION 3.16)

project(FastParser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Original executable
add_executable(FastParser
    src/main.cpp
    src/parser.cpp
    src/person.cpp
)

target_compile_options(FastParser PRIVATE
    -Wall
    -Wextra
    -Werror
)

# Day 11 executable
add_executable(stl_container_benchmarks
    Day11/Mainbenchmark.cpp
    src/parser.cpp
    src/person.cpp
)

target_include_directories(stl_container_benchmarks PRIVATE include)

target_compile_options(stl_container_benchmarks PRIVATE
    -Wall
    -Wextra
    -Werror
)