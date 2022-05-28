//
// Created by Tobias on 27/05/2022.
//
#pragma once
#include "filter.h"
#include "criterionVZPodiel.h"

class FilterVzPodiel : Filter_FI<double> {
public:
    FilterVzPodiel(Criterion<double> *criterion, double pMin, double pMax) : Filter_FI(criterion, pMin, pMax) {}


};