//
// Created by Tobias on 26/05/2022.
//
#pragma once

#include "filter.h"
#include "criterionVZPocet.h"

class FilterVzPocet : Filter {
private:
    int minimum = 0;
    int maximum = 0;
    int index = 0;
public:
    FilterVzPocet(int pIndex, int min, int max) :
        index(pIndex),
        minimum(min),
        maximum(max)
    {
    };
    bool pass(const StoredData &data) override;

};

inline bool FilterVzPocet::pass(const StoredData &data) {
    CriterionVZPocet *criterium = new CriterionVZPocet(index);
    bool retrunValue = false;
    if (minimum >= criterium->evaluate(data) && criterium->evaluate(data) <= maximum) {
        retrunValue = true;
    }
    delete criterium;
    return retrunValue;
}
