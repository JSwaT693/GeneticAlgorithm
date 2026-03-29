//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_LOGGER_H
#define PEA_PROJECT4_LOGGER_H

#include <iostream>
#include <fstream>
#include "Solution.h"


class Logger {
public:
    explicit Logger(const std::string& filePath);
    Logger();

    void saveCosts(int cost, long long timeFound);
    void saveResults(const Solution& solution);
    void showResults(const Solution& solution);

private:
    std::ofstream file;

};


#endif //PEA_PROJECT4_LOGGER_H
