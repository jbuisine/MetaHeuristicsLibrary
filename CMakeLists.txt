cmake_minimum_required(VERSION 3.6)
project(MetaHeuristics)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Heuristics.hpp src/solutions/CombinatorySolution.hpp src/solutions/Solution.hpp src/solutions/BinaryCombinatorySolution.hpp src/Utilities.cpp src/Utilities.h)
add_executable(MetaHeuristics ${SOURCE_FILES})