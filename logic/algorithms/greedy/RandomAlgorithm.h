//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_RANDOMALGORITHM_H
#define PEA_PROJECT4_RANDOMALGORITHM_H

#include <algorithm>
#include <random>
#include "IGreedy.h"
#include "../../Solution.h"
#include "../../GraphActions.h"

class RandomAlgorithm : public IGreedy {
public:
    explicit RandomAlgorithm(const Graph& graph) : graph(graph) {}

    [[nodiscard]] Graph greedyAlgorithm(int populationSize) const override {
        Graph population;
        Path path(graph.size());

        iota(path.begin(), path.end(), 0);

        for (int i = 0; i < populationSize; ++i) {
            shuffle(path.begin(), path.end(), std::mt19937(std::random_device()()));
            population.push_back(path);
        }
        return population;
    }
private:
    const Graph& graph;

};

#endif //PEA_PROJECT4_RANDOMALGORITHM_H
