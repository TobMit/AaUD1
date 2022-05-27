//
// Created by Tobias on 26/05/2022.
//
#pragma once

#include "filter.h"
#include "criterionVZPocet.h"

class FilterVzPocet : Filter<int> {
private:
    int minimum = 0;
    int maximum = 0;
    int index = 0;
public:
    FilterVzPocet(int min, int max) :
        minimum(min),
        maximum(max)
    {
    };
    bool pass(const StoredData &data, Criterion<int> *criterion) override;
};

inline bool FilterVzPocet::pass(const StoredData &data, Criterion<int> *criterion) {
    bool retrunValue = false;
    if (minimum >= criterion->evaluate(data) && criterion->evaluate(data) <= maximum) {
        retrunValue = true;
    }
    return retrunValue;
}

