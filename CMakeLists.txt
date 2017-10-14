cmake_minimum_required(VERSION 3.7)
project(pea_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp TravellingSalesmanProblem.cpp TravellingSalesmanProblem.h GraphMatrix.cpp GraphMatrix.h Graph.cpp Graph.h)
add_executable(pea_1 ${SOURCE_FILES})