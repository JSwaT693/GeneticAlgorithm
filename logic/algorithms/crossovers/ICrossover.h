//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_ICROSSOVER_H
#define PEA_PROJECT4_ICROSSOVER_H

#include "../../MyTypes.h"

class ICrossover {
public:
    virtual ~ICrossover() = default;
    virtual Path crossover(const Path& firstParent, const Path& secondParent) const = 0;
};

#endif //PEA_PROJECT4_ICROSSOVER_H
