//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_NEARESTNEIGHBOUR_H
#define PEA_PROJECT4_NEARESTNEIGHBOUR_H

#include <limits>
#include <utility>
#include "../../MyTypes.h"
#include "IGreedy.h"
#include "../../MyRand.h"

class NearestNeighbour : public IGreedy {
public:
    explicit NearestNeighbour(const Graph& graph) : graph(graph) {}

    [[nodiscard]] Graph greedyAlgorithm(int populationSize) const override {
        Graph population;

        for (int i = 0; i < populationSize; ++i) {
            int startNode = MyRand::getRandomInt(0, graph.size() - 1);
            Path currentPath = generatePath(startNode);
            population.push_back(currentPath);
        }

        return population;
    }

private:
    const Graph& graph;

    [[nodiscard]] Path generatePath(int startNode) const {
        std::vector<bool> visited(graph.size(), false);
        Path currentPath;
        int currentNode = startNode;

        currentPath.push_back(currentNode);
        visited[currentNode] = true;

        for (int step = 1; step < graph.size(); ++step) {
            int nextNode = -1;
            int minEdgeCost = std::numeric_limits<int>::max();

            for (int neighbor = 0; neighbor < graph.size(); ++neighbor) {
                if (!visited[neighbor] && graph[currentNode][neighbor] != -1 && graph[currentNode][neighbor] < minEdgeCost) {
                    nextNode = neighbor;
                    minEdgeCost = graph[currentNode][neighbor];
                }
            }

            visited[nextNode] = true;
            currentNode = nextNode;
            currentPath.push_back(currentNode);
        }

        return currentPath;
    }
};

#endif //PEA_PROJECT4_NEARESTNEIGHBOUR_H
