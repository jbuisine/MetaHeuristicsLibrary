cmake_minimum_required(VERSION 3.6)
project(MetaHeuristics)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Algorithms/Heuristics.hpp src/solutions/CombinatorySolution.hpp src/solutions/Solution.hpp src/solutions/BinaryCombinatorySolution.hpp src/Algorithms/Utilities.hpp src/utils.h src/mainILS.cpp)
add_executable(MetaHeuristics ${SOURCE_FILES})