cmake_minimum_required(VERSION 3.6)
project(MetaHeuristics)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/mainKnapsack.cpp src/algorithms/Heuristics.hpp src/solutions/CombinatorySolution.hpp src/solutions/Solution.hpp src/solutions/BinaryCombinatorySolution.hpp src/algorithms/Utilities.hpp src/algorithms/TabuSearch.hpp src/algorithms/Utilities.hpp src/utils/Utils.hpp src/algorithms/SimulatedAnnealing.hpp src/algorithms/MetaLocalSearch.hpp src/algorithms/localsearch/LocalSearch.hpp src/metaheuristics.h src/algorithms/EvolutionaryAlgorithmSearch.hpp src/algorithms/operators/EAOperators.hpp)
add_executable(MetaHeuristics ${SOURCE_FILES})