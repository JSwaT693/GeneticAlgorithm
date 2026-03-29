//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_IGREEDY_H
#define PEA_PROJECT4_IGREEDY_H

#include "../../MyTypes.h"

class IGreedy {
public:
    virtual ~IGreedy() = default;
    [[nodiscard]] virtual Graph greedyAlgorithm(int popuationSize) const = 0;

};

#endif //PEA_PROJECT4_IGREEDY_H
