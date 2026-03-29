//
// Created by jakub on 13.01.2025.
//

#ifndef PEA_PROJECT4_IMUTATOR_H
#define PEA_PROJECT4_IMUTATOR_H

#include "../../MyTypes.h"

class IMutator {
public:
    virtual ~IMutator() = default;
    virtual Path mutate(const Path& path) const = 0;
};

#endif //PEA_PROJECT4_IMUTATOR_H
