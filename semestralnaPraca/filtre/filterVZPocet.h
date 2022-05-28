//
// Created by Tobias on 26/05/2022.
//
#pragma once

#include "filter.h"

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
    bool pass(const StoredData &data, int criterionValue) override;
};

inline bool FilterVzPocet::pass(const StoredData &data, int criterionValue) {
    bool retrunValue = false;
    if (minimum >= criterionValue && criterionValue <= maximum) {
        retrunValue = true;
    }
    return retrunValue;
}
