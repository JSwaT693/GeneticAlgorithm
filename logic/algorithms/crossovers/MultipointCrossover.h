//
// Created by jakub on 18.01.2025.
//

#ifndef PEA_PROJECT4_MULTIPOINTCROSSOVER_H
#define PEA_PROJECT4_MULTIPOINTCROSSOVER_H

#include <gmpxx.h>
#include "ICrossover.h"
#include "../../MyRand.h"
#include <algorithm>
#include <vector>

class MultipointCrossover : public ICrossover {
public:
    [[nodiscard]] Path crossover(const Path& firstParent, const Path& secondParent) const override {
        int size = firstParent.size();
        Path child(size, -1);

        int start = MyRand::getRandomInt(0, size - 1);
        int end = MyRand::getRandomInt(0, size - 1);
        if (start > end) std::swap(start, end);

        for (int i = start; i <= end; i++) {
            child[i] = firstParent[i];
        }

        std::unordered_set<int> existingElements(child.begin() + start, child.begin() + end + 1);

        int currentIndex = 0;
        for (int i = 0; i < size; i++) {
            int element = secondParent[i];

            if (existingElements.find(element) != existingElements.end()) {
                continue;
            }

            while (child[currentIndex] != -1) {
                currentIndex++;
            }

            child[currentIndex] = element;
        }

        return child;
    }

private:
    Graph graph;

};


#endif //PEA_PROJECT4_MULTIPOINTCROSSOVER_H
