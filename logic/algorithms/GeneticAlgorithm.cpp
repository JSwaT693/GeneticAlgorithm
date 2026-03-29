//
// Created by jakub on 13.01.2025.
//

#include "GeneticAlgorithm.h"
#include "../MyRand.h"
#include "../GraphActions.h"
#include "greedy/IGreedy.h"
#include "mutations/IMutator.h"
#include "crossovers/ICrossover.h"
#include "greedy/RandomAlgorithm.h"
#include "greedy/NearestNeighbour.h"
#include "../Logger.h"

#include <utility>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

GeneticAlgorithm::GeneticAlgorithm(Graph graph) : graph(std::move(graph)) {}

Solution GeneticAlgorithm::geneticAlgorithm(int populationSize, int timeLimit, int tournamentSize, double crossoverRate, double mutationRate, const ICrossover& crossover, const IMutator& mutator,  const IGreedy& greedy, Logger& logger) {
    Path fitness(populationSize);
    long long elapsedTime;
    RandomAlgorithm randomAlgorithm(graph);
    NearestNeighbour nn(graph);
    bestSolution.bestCost = std::numeric_limits<int>::max();

//    Graph population = greedy.greedyAlgorithm(populationSize);
    Graph nnPopulation = nn.greedyAlgorithm(int(populationSize * 0.75));
    Graph randomPopulation = randomAlgorithm.greedyAlgorithm(int(populationSize - nnPopulation.size()));
    Graph population = nnPopulation;
    population.insert(population.end(), randomPopulation.begin(), randomPopulation.end());
    Graph newPopulation(populationSize);

    for (const auto& element : population) {
        int cost = GraphActions::calculateCost(element, graph);
        if (cost < bestSolution.bestCost) {
            bestSolution.bestCost = cost;
            bestSolution.bestPath = element;

            auto currentTime = std::chrono::steady_clock::now();
            bestSolution.timeFound = 0;
        }
    }

//    int iterations = 0;
//    int updates = 0;
//    int crossovers = 0;
//    int mutations = 0;
    int restart = 0;

    logger.saveCosts(bestSolution.bestCost, bestSolution.timeFound);

    auto startTime = std::chrono::steady_clock::now();

    do {
        for (int i = 0; i < populationSize; i++) {
            Path firstParent = tournamentSelection(population, fitness, tournamentSize);
            Path secondParent = tournamentSelection(population, fitness, tournamentSize);

            Path child = firstParent;
            if (MyRand::getRandomDouble(0.0, 1.0) < crossoverRate) {
                child = crossover.crossover(firstParent, secondParent);
//                crossovers++;
            }

            if (MyRand::getRandomDouble(0.000, 1.000) < mutationRate) {
                child = mutator.mutate(child);
//                mutations++;
            }

            newPopulation[i] = child;
        }

        population = newPopulation;
        Path newFitness(populationSize);
        auto bestCost = bestSolution.bestCost;

        for (int i = 0; i < populationSize; i++) {
            int cost = GraphActions::calculateCost(population[i], graph);
            fitness[i] = cost;

            if (cost < bestSolution.bestCost) {
                bestSolution.bestCost = cost;
                bestSolution.bestPath = population[i];
//                std::cout << bestSolution.bestCost << std::endl;

//                updates++;
                restart = 0;
                auto currentTime = std::chrono::steady_clock::now();
                bestSolution.timeFound = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
                logger.saveCosts(cost, bestSolution.timeFound);
            }
        }

        auto newBestCost = bestSolution.bestCost;
        if (bestCost == newBestCost) {
            restart++;
        }

        if (restart == 0.1 * populationSize) {
            auto path = bestSolution.bestPath;
            for (int i = 0; i < populationSize; i++) {
                path = mutator.mutate(path);
                population[i] = Path(path);
            }

//            std::cout << "Restarted" << std::endl;
            restart = 0;
        }

        auto currentTime = std::chrono::steady_clock::now();
        elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
//        iterations++;
    } while (elapsedTime < timeLimit);

//    std::cout <<"Liczba wykonanych iteracji: " + std::to_string(iterations) << std::endl
//            << "Liczba wykonanych krzyzowan: " + std::to_string(crossovers) << std::endl
//            << "Liczba wykonanych mutacji: " + std::to_string(mutations) << std::endl
//            << "Liczba znalezionych lepszych wynikow: " + std::to_string(updates) << std::endl;

    auto currentTime = std::chrono::steady_clock::now();
    elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    bestSolution.time = elapsedTime;
    logger.saveCosts(bestSolution.bestCost, bestSolution.time);

    return bestSolution;
}

Path GeneticAlgorithm::tournamentSelection(Graph population, const Path &fitness, int tournamentSize) {
    Path selected;
    for (int i = 0; i < tournamentSize; i++) {
        int randomIndex = MyRand::getRandomInt(0, population.size() - 1);
        selected.push_back(randomIndex);
    }
    return population[*min_element(selected.begin(), selected.end(), [&](int a, int b) {
        return fitness[a] < fitness[b];
    })];
}
