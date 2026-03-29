//
// Created by jakub on 13.01.2024.
//

#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include "GraphActions.h"

void GraphActions::showGraph(std::vector<std::vector<int>> graph) {
    for (auto & item : graph) {
        for (int j : item) {
            std::cout << j << "    ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>> GraphActions::readGraph(std::string path) {
    std::ifstream file(path);

    if (file.is_open()) {
        int vertices = 0;
        std::string line, fileType;
        std::vector<std::vector<int>> tempMatrix;
        bool isMatrixSection = false;
        std::vector<int> values;

        while (std::getline(file, line)) {
            line.erase(0, line.find_first_not_of(" \t"));

            if (line.find("DIMENSION") != std::string::npos) {
                vertices = std::stoi(line.substr(line.find(": ") + 1));
                tempMatrix.resize(vertices, std::vector<int>(vertices, 0));
            } else if (line.find("EDGE_WEIGHT_SECTION") != std::string::npos) {
                isMatrixSection = true;

            } else if (isMatrixSection) {
                std::istringstream stream(line);
                int value;
                while (stream >> value) {
                    values.push_back(value);
                }
            }
        }
        file.close();

        int enumerate = 0;

        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                int value = values[enumerate++];
                tempMatrix[i][j] = value;
            }
        }

        return tempMatrix;
    } else {
        std::cout << "Nie znalezniono pliku" << std::endl;
    }
}

std::vector<int> GraphActions::flattenGraph(std::vector<std::vector<int>> graph) {
    std::vector<int> flattenedGraph;

    for (const auto& row : graph) {
        for (int value : row) {
            if (value != 0 && value != 100000000) {
                flattenedGraph.push_back(value);
            }
        }
    }

    return flattenedGraph;
}

int GraphActions::findMinMaxDiff(std::vector<std::vector<int>> graph) {
    auto tempGraph = flattenGraph(std::move(graph));
    auto [minIt, maxIt] = std::minmax_element(tempGraph.begin(), tempGraph.end());
    auto temp = (*maxIt) - (*minIt);
    return temp;
}


int GraphActions::calculateCost(const std::vector<int>& path, const std::vector<std::vector<int>>& graph) {
    int cost = 0;
    for (int i = 0; i < path.size() - 1; i++) {
        cost += graph[path[i]][path[i + 1]];
    }
    cost += graph[path.back()][path[0]];
    return cost;
}
