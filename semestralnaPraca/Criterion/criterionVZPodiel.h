#include "criterion.h"
#include "criterionVZPocet.h"

#pragma once
class CriterionVZPodiel : public Criterion<double> {
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
    double retunrValue = 0;
    if (data.getVzdelavanie() != nullptr) {
        auto *ostatneData = dynamic_cast<OstatneUdaje *>(data.getVzdelavanie());
        int pocetObyvatelov = ostatneData->getPocOsob();
        double medcziPocet = ostatneData->intAt(index);
        retunrValue = 100 * (medcziPocet/ pocetObyvatelov);
    }
    return retunrValue;
}
