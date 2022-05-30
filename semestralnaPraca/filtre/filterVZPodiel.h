#pragma once
#include "filter.h"
#include "criterionVZPodiel.h"

class FilterVzPodiel : public Filter_FI<double> {
public:
    FilterVzPodiel(int pIndex, double pMin, double pMax) :
        Filter_FI<double>(new CriterionVZPodiel(pIndex), pMin, pMax) {}

};