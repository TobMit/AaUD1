//
// Created by Tobias on 27/05/2022.
//
#pragma once
#include "filter.h"

class FilterVzPodiel : Filter<double> {
private:
    int index = 0;
    double minimum = 0;
    double maximum = 0;
public:
    FilterVzPodiel(double min, double max) :
        minimum(min),
        maximum(max)
    {};
    bool pass(const StoredData &data, double criterionValue) override;

};

inline bool FilterVzPodiel::pass(const StoredData &data, double criterionValue) {
    bool retrunValue = false;
    if (minimum >= criterionValue && criterionValue <= maximum) {
        retrunValue = true;
    }
    return retrunValue;
}