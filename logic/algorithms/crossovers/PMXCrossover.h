//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_PMXCROSSOVER_H
#define PEA_PROJECT4_PMXCROSSOVER_H

#include <gmpxx.h>
#include "ICrossover.h"
#include "../../MyRand.h"

class PMXCrossover : public ICrossover {
public:
    [[nodiscard]] Path crossover(const Path& firstParent, const Path& secondParent) const override {
        int size = firstParent.size();
        Path child(firstParent.size(), -1);

        int crossoverStart = MyRand::getRandomInt(0, size - 1);
        int crossoverEnd = MyRand::getRandomInt(0, size - 1);

        if (crossoverStart == crossoverEnd) {
            return firstParent;
        }

        if (crossoverStart > crossoverEnd) {
            std::swap(crossoverStart, crossoverEnd);
        }

        for (int i = crossoverStart; i <= crossoverEnd; i++) {
            child[i] = firstParent[i];
        }

        for (int i = crossoverStart; i <= crossoverEnd; i++) {
            if (find(child.begin(), child.end(), secondParent[i]) == child.end()) {
                int value = secondParent[i];
                int index = i;
                while (child[index] != -1) {
                    index = find(secondParent.begin(), secondParent.end(), firstParent[index]) - secondParent.begin();
                }
                child[index] = value;
            }
        }

        for (int i = 0; i < size; i++) {
            if (child[i] == -1) {
                child[i] = secondParent[i];
            }
        }
        std::cout << "\nCrossoverStart: ";
        std::cout << crossoverStart << " ";
        std::cout << "\nCrossoverEnd: ";
        std::cout << crossoverEnd << " ";
        std::cout << "\nParent1: ";
        for (int x : firstParent) std::cout << x << " ";
        std::cout << "\nParent2: ";
        for (int x : secondParent) std::cout << x << " ";
        std::cout << "\nChild: ";
        for (int x : child) std::cout << x << " ";
        std::cout << std::endl;

        return child;
    }

private:
    Graph graph;

};

#endif //PEA_PROJECT4_PMXCROSSOVER_H
