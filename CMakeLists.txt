cmake_minimum_required(VERSION 3.7)
project(MetaHeuristics)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Heuristics.cpp src/Heuristics.h src/Solution.cpp src/Solution.h)
add_executable(MetaHeuristics ${SOURCE_FILES})