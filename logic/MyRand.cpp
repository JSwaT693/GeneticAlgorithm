//
// Created by jakub on 13.01.2025.
//

#include <random>
#include "MyRand.h"

int MyRand::getRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>(min, max);
    return dist(mt);
}

double MyRand::getRandomDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist = std::uniform_real_distribution<double>(min, max);
    return dist(mt);
}
