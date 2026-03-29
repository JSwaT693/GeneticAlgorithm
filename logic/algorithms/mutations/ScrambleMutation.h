//
// Created by jakub on 14.01.2025.
//

#ifndef PEA_PROJECT4_SCRAMBLEMUTATION_H
#define PEA_PROJECT4_SCRAMBLEMUTATION_H

#include "IMutator.h"
#include "../../MyRand.h"
#include <algorithm>
#include <random>

class ScrambleMutation : public IMutator {
public:
    Path mutate(const Path& path) const override {
        Path cities = path;
        int n = path.size();

        int start = MyRand::getRandomInt(0, n - 1);
        int end = MyRand::getRandomInt(0, n - 1);
        if (start > end) std::swap(start, end);

        std::shuffle(cities.begin() + start, cities.begin() + end + 1, std::mt19937(std::random_device()()));

        return cities;
    }
};

#endif //PEA_PROJECT4_SCRAMBLEMUTATION_H
