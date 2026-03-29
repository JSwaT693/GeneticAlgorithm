//
// Created by jakub on 13.01.2025.
//

#include "Logger.h"
const int expectedResult = 2480;

Logger::Logger(const std::string& filePath) {
    file.open(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku: " + filePath);
    }
}

Logger::Logger() = default;

void Logger::saveCosts(int cost, long long timeFound) {
    file << "(" << ((cost - expectedResult) * 100) / expectedResult << ", " << timeFound << "), ";
}


void Logger::saveResults(const Solution& solution) {
    file << "Elapsed time: " << solution.time << std::endl
         << "Best cost: " << solution.bestCost << std::endl
         << "Time found: " << solution.timeFound << std::endl
         << "Best path: " << std::endl;
    for (int city : solution.bestPath) file << city << " ";
    file << std::endl;
}

void Logger::showResults(const Solution& solution) {
    std::cout << "Best found cost: " + std::to_string(solution.bestCost) << std::endl;
    std::cout << "Time it was found: " + std::to_string(solution.timeFound) << std::endl;
    std::cout << "Best Path: ";
    for (int city: solution.bestPath) std::cout << city << " ";
    std::cout << std::endl << "Elapsed time: " << solution.time << std::endl;
}