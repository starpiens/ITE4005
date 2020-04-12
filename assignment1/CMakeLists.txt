cmake_minimum_required(VERSION 3.15)
project(assignment1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE -O3)

include_directories(include)

add_executable(apriori
        src/main.cpp
        src/Item.cpp
        src/AssociationRule.cpp)