#include "criterion.h"

#pragma once
class CriterionUJPrislusnost : public Criterion<bool> {
private:
    StoredData * dataToCompare;
public:
    CriterionUJPrislusnost(StoredData &comparedData);

    bool evaluate(const StoredData &data) override;


};

inline CriterionUJPrislusnost::CriterionUJPrislusnost(StoredData &comparedData) :
    dataToCompare(&comparedData)
{

}

inline inline bool CriterionUJPrislusnost::evaluate(const StoredData &data) {
    return data.belongsTo(*dataToCompare);
}

