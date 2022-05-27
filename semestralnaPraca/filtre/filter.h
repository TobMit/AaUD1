//
// Created by Tobias on 26/05/2022.
//
#pragma once

#include "storedData.h"
#include "criterion.h"

template <typename criterioValue>
class Filter {
public:
    virtual bool pass(const StoredData &data, Criterion<criterioValue> *criterion) = 0;
};

