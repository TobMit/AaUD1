//
// Created by Tobias on 27/05/2022.
//
#pragma once

#include "filter.h"

class FilterUJPrislusnost : Filter<bool> {
    bool pass(const StoredData &data, Criterion<bool> *criterion) override;

};

inline bool FilterUJPrislusnost::pass(const StoredData &data, Criterion<bool> *criterion) {
    return criterion->evaluate(data);
}

