//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_GENETICALGORITHM_H
#define PEA_PROJECT4_GENETICALGORITHM_H


#include "../Solution.h"
#include "../MyTypes.h"
#include "crossovers/ICrossover.h"
#include "mutations/IMutator.h"
#include "greedy/IGreedy.h"
#include "../Logger.h"

class GeneticAlgorithm {
public:
    explicit GeneticAlgorithm(Graph graph);

    Solution geneticAlgorithm(int populationSize, int timeLimit, int tournamentSize, double crossoverRate, double mutationRate, const ICrossover& crossover, const IMutator& mutator,  const IGreedy& greedy, Logger& logger);

private:
    Graph graph;
    Solution bestSolution;

    Path tournamentSelection(Graph populationm, const Path& fitness, int tournamentSize);
};


#endif //PEA_PROJECT4_GENETICALGORITHM_H
