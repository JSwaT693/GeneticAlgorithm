//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_CONFIG_H
#define PEA_PROJECT4_CONFIG_H

#include <iostream>
#include <vector>
#include "GraphActions.h"
#include "Solution.h"
#include "MyTypes.h"


class Config {
public:
    explicit Config(std::string path);

    void run();

private:
    Graph graph;
    std::string path;
    std::string task;
    std::string inputFile;
    std::string doShowGraph = "no";
    int timeLimit = 0;
    int populationSize = 0;
    int tournamentSize = 0;
    std::string crossoverMethod;
    double crossoverRate = 0.0;
    std::string mutationMethod;
    double mutationRate = 0.0;
    int testAmount = 0;
    std::string outputFile;
    Solution bestSolution;
    std::string progressBar;
    std::string greedyAlgorithm;

    void readFile();
    void runTask();
    void showProgressBar(int i) const;


};


#endif //PEA_PROJECT4_CONFIG_H
