//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_GRAPHACTIONS_H
#define PEA_PROJECT4_GRAPHACTIONS_H

#include <vector>
#include <string>

class GraphActions {
public:
    static void showGraph(std::vector<std::vector<int>> graph);
    static std::vector<std::vector<int>> readGraph(std::string path);
    static std::vector<int> flattenGraph(std::vector<std::vector<int>> graph);
    static int findMinMaxDiff(std::vector<std::vector<int>> graph);
    static int calculateCost(const std::vector<int>& path, const std::vector<std::vector<int>>& graph);


};


#endif //PEA_PROJECT4_GRAPHACTIONS_H
