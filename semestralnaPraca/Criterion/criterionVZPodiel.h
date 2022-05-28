//
// Created by Tobias on 25/05/2022.
//
#include "criterion.h"
#include "criterionVZPocet.h"

#pragma once
class CriterionVZPodiel : Criterion<double> {
public:
    CriterionVZPodiel(const int pIndex);

    double evaluate(const StoredData &data) override;

private:
    int index;

};

inline CriterionVZPodiel::CriterionVZPodiel(const int pIndex) :
    index(pIndex)
{
}

inline double CriterionVZPodiel::evaluate(const StoredData &data) {
    //todo skontrolovat memleaky
    double retunrValue = 0;
    if (data.getVzdelavanie() != nullptr) {
        auto ostatneData = dynamic_cast<const OstatneUdaje &>(*data.getVzdelavanie());
        CriterionVZPocet *pocet = new CriterionVZPocet(index);
        int pocetObyvatelov = 0;
        for (int i = 0; i < ostatneData.getSize(); ++i) {
            pocetObyvatelov += ostatneData.intAt(i);
        }
        retunrValue = 100 * (pocet->evaluate(data) / pocetObyvatelov);
        delete pocet;
    }
    return retunrValue;
}
