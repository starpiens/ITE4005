cmake_minimum_required(VERSION 3.15)
project(assignment1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(apriori
        src/main.cpp
        src/ItemSet.cpp
        src/AssociationRule.cpp)