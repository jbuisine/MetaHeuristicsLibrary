cmake_minimum_required(VERSION 3.6)
project(MetaHeuristics)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Heuristics.cpp src/Heuristics.h src/solutions/CombinatorySolution.cpp src/solutions/CombinatorySolution.h src/solutions/Solution.cpp src/solutions/Solution.h src/solutions/BinaryCombinatorySolution.cpp src/solutions/BinaryCombinatorySolution.h src/Utilities.cpp src/Utilities.h)
add_executable(MetaHeuristics ${SOURCE_FILES})