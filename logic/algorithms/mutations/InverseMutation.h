//
// Created by jakub on 14.01.2025.
//

#ifndef PEA_PROJECT4_INVERSEMUTATION_H
#define PEA_PROJECT4_INVERSEMUTATION_H

#include <algorithm>
#include "IMutator.h"
#include "../../MyRand.h"

class InverseMutation : public IMutator {
public:
    Path mutate(const Path& path) const override {
        Path cities = path;
        int n = path.size();

        int start = MyRand::getRandomInt(0, n - 1);
        int end = MyRand::getRandomInt(0, n - 1);
        if (start > end) std::swap(start, end);

        std::reverse(cities.begin() + start, cities.begin() + end + 1);

        return cities;
    }
};

#endif //PEA_PROJECT4_INVERSEMUTATION_H
