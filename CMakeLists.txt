cmake_minimum_required(VERSION 3.16)

project(FastParser)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(FastParser
    src/main.cpp
    src/Person.cpp
    src/Parser.cpp
)