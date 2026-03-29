//
// Created by jakub on 14.01.2025.
//

#ifndef PEA_PROJECT4_ORDERCROSSOVER_H
#define PEA_PROJECT4_ORDERCROSSOVER_H

#include "ICrossover.h"
#include "../../MyRand.h"
#include <unordered_set>

class OrderCrossover : public ICrossover {
public:
    [[nodiscard]] Path crossover(const Path& firstParent, const Path& secondParent) const override {
        int size = firstParent.size();
        Path child(size, -1);

        int start = MyRand::getRandomInt(0, size - 1);
        int end = MyRand::getRandomInt(0, size - 1);
        if (start == end) return firstParent;
        if (start > end) std::swap(start, end);

        for (int i = start; i <= end; ++i) {
            child[i] = firstParent[i];
        }

        std::unordered_set<int> existingElements(child.begin() + start, child.begin() + end + 1);
        int currentIndex = (end + 1) % size;

        for (int i = 0; i < size; ++i) {
            int element = secondParent[(end + 1 + i) % size];
            if (existingElements.find(element) == existingElements.end()) {
                child[currentIndex] = element;
                existingElements.insert(element);
                currentIndex = (currentIndex + 1) % size;
            }
        }

        return child;
    }
};

#endif //PEA_PROJECT4_ORDERCROSSOVER_H
