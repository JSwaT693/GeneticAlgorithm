//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_SWAPMUTATION_H
#define PEA_PROJECT4_SWAPMUTATION_H

#include "IMutator.h"
#include "../../MyRand.h"

class SwapMutation : public IMutator {
public:
    Path mutate(const Path& path) const override {
        Path cities = path;
        int n = path.size();
        int i = MyRand::getRandomInt(0, n - 1);
        int j = MyRand::getRandomInt(0, n - 1);
        while (i == j) {
            j = MyRand::getRandomInt(0, n - 1);
        }
        std::swap(cities[i], cities[j]);
        return cities;
    }

};

#endif //PEA_PROJECT4_SWAPMUTATION_H
