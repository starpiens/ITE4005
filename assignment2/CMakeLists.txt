cmake_minimum_required(VERSION 3.16)
project(assignment2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE -O3)

include_directories(include)

add_executable(assignment2
        src/main.cpp
        include/attribute.hpp src/attribute.cpp include/data.hpp src/data.cpp)