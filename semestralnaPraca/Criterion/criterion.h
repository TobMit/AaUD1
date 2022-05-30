#pragma once

#include "storedData.h"

template <typename returnType>
class Criterion {
public:
    virtual returnType evaluate(const StoredData &data) = 0;
};
