cmake_minimum_required(VERSION 3.8)
project(pea_1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    CMakeLists.txt
    Graph.cpp
    Graph.h
    GraphMatrix.cpp
    GraphMatrix.h
    main.cpp
    Timer.cpp
    Timer.h
    TravellingSalesmanProblem.cpp
    TravellingSalesmanProblem.h)

add_executable(pea_1 ${SOURCE_FILES})