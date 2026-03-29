//
// Created by jakub on 13.01.2025.
//

#include <unordered_map>
#include <fstream>
#include <memory>
#include "Config.h"
#include "Logger.h"
#include "algorithms/greedy/IGreedy.h"
#include "algorithms/greedy/RandomAlgorithm.h"
#include "algorithms/crossovers/ICrossover.h"
#include "algorithms/crossovers/PMXCrossover.h"
#include "algorithms/mutations/IMutator.h"
#include "algorithms/mutations/SwapMutation.h"
#include "algorithms/mutations/InverseMutation.h"
#include "algorithms/GeneticAlgorithm.h"
#include "algorithms/crossovers/OrderCrossover.h"
#include "algorithms/greedy/NearestNeighbour.h"
#include "algorithms/mutations/ScrambleMutation.h"
#include "algorithms/crossovers/MultipointCrossover.h"

void Config::run() {
    readFile();
    runTask();
}

void Config::readFile() {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku CSV: " + path);
    }

    std::unordered_map<std::string, std::string> config;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        auto delimiterPos = line.find('=');
        if (delimiterPos == std::string::npos) {
            throw std::runtime_error("Niepoprawny format linii w pliku konfiguracyjnym: " + line);
        }

        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        config[key] = value;
    }

    if (config.find("task") != config.end()) {
        task = config["task"];
    } else {
        throw std::runtime_error("Brak wymaganego klucza 'task' w pliku konfiguracyjnym");
    }

    inputFile = config["inputFile"];
    doShowGraph = config["doShowGraph"];
    timeLimit = std::stoi(config["timeLimitSeconds"]);
    greedyAlgorithm = config["greedyAlgorithm"];
    populationSize = std::stoi(config["populationSize"]);
    tournamentSize = std::stoi(config["tournamentSize"]);
    crossoverMethod = config["crossoverMethod"];
    crossoverRate = std::stod(config["crossoverRate"]);
    mutationMethod = config["mutationMethod"];
    mutationRate = std::stod(config["mutationRate"]);

    if (task == "simulation") {
        outputFile = config["outputFile"];
        testAmount = std::stoi(config["testAmount"]);
        progressBar = config["showProgressBar"];


    } else if (task == "test") {

    } else {
        throw std::runtime_error("Nieprawidłowy typ zadania: " + task);
    }
}

void Config::runTask() {
    graph = GraphActions::readGraph(inputFile);
    GeneticAlgorithm algorithm(graph);

    std::unique_ptr<IGreedy> greedy;
    if (greedyAlgorithm == "random") {
        greedy = std::make_unique<RandomAlgorithm>(graph);
    } else if (greedyAlgorithm == "nn") {
        greedy = std::make_unique<NearestNeighbour>(graph);
    } else {
        throw std::runtime_error("Nieprawidlowy typ zachlannego algorytmu: " + greedyAlgorithm);
    }

    std::unique_ptr<ICrossover> crossover;
    if (crossoverMethod == "pmx") {
        crossover = std::make_unique<PMXCrossover>();
    } else if (crossoverMethod == "order"){
        crossover = std::make_unique<OrderCrossover>();
    } else if (crossoverMethod == "multipoint") {
        crossover = std::make_unique<MultipointCrossover>();
    } else {
        throw std::runtime_error("Nieprawidlowy typ krzyzowania: " + crossoverMethod);
    }

    std::unique_ptr<IMutator> mutator;
    if (mutationMethod == "swap") {
        mutator = std::make_unique<SwapMutation>();
    } else if (mutationMethod == "inverse") {
        mutator = std::make_unique<InverseMutation>();
    } else if (mutationMethod == "scramble"){
        mutator = std::make_unique<ScrambleMutation>();
    } else {
        throw std::runtime_error("Nieprawidlowy typ mutacji: " + mutationMethod);

    }

    if (task == "test") {
        Logger logger;

        if (doShowGraph == "yes") {
            GraphActions::showGraph(graph);
        }

        bestSolution = algorithm.geneticAlgorithm(populationSize, timeLimit, tournamentSize, crossoverRate, mutationRate, *crossover, *mutator, *greedy, logger);

        logger.showResults(bestSolution);
    } else if (task == "simulation") {
        Logger logger(outputFile);
        for (int i; i < testAmount; i++) {
            bestSolution = algorithm.geneticAlgorithm(populationSize, timeLimit, tournamentSize, crossoverRate, mutationRate, *crossover, *mutator, *greedy, logger);
            //logger.saveResults(bestSolution);
            if (progressBar == "yes") {
                showProgressBar(i);
            }
        }
    }
}

void Config::showProgressBar(int i) const {
    if (i == 0) {
        std::cout << "<-";
    } else if (i == testAmount - 1) {
        std::cout << "->" << std::endl;
    } else {
        std::cout << "-";
    }
}

Config::Config(std::string path) : path(std::move(path)) {}