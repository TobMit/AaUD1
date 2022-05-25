//
// Created by Tobias on 25/05/2022.
//
#include "criterion.h"
#include "ostatneUdaje.h"

#pragma once
class CriterionUJTyp : Criterion<int> {
public:
    CriterionUJTyp(const int pIndex);

    int evaluate(const StoredData &data) override;

private:
    int index;

};

CriterionUJTyp::CriterionUJTyp(const int pIndex) :
    index(pIndex)
{
}

int CriterionUJTyp::evaluate(const StoredData &data) {
    auto ostatneData = dynamic_cast<const OstatneUdaje &>(data);
    return ostatneData.intAt(index);
}
