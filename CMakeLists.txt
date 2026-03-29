cmake_minimum_required(VERSION 3.27)
project(pea_project4)

set(CMAKE_CXX_STANDARD 17)

add_executable(pea_project4 main.cpp
        logic/Config.cpp
        logic/Config.h
        logic/Solution.h
        logic/MyTypes.h
        logic/GraphActions.cpp
        logic/GraphActions.h
        logic/Logger.cpp
        logic/Logger.h
        logic/algorithms/crossovers/ICrossover.h
        logic/algorithms/mutations/IMutator.h
        logic/MyRand.cpp
        logic/MyRand.h
        logic/algorithms/GeneticAlgorithm.cpp
        logic/algorithms/GeneticAlgorithm.h
        logic/algorithms/greedy/RandomAlgorithm.h
        logic/algorithms/greedy/IGreedy.h
        logic/algorithms/crossovers/PMXCrossover.h
        logic/algorithms/mutations/SwapMutation.h
        logic/algorithms/greedy/NearestNeighbour.h
        logic/algorithms/crossovers/OrderCrossover.h
        logic/algorithms/mutations/InverseMutation.h
        logic/algorithms/mutations/ScrambleMutation.h
        logic/algorithms/crossovers/MultipointCrossover.h)
