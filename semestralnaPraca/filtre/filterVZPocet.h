#pragma once

#include "filter.h"
#include "criterionVZPocet.h"

class FilterVzPocet : public Filter_FI<int>{
public:
    FilterVzPocet(int pIndex, int pMin, int pMax) :
        Filter_FI(new CriterionVZPocet(pIndex), pMin, pMax) {}
};
