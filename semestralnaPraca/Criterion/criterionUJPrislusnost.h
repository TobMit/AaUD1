//
// Created by Tobias on 25/05/2022.
//

#include "criterion.h"

#pragma once
class CriterionUJPrislusnost : Criterion<bool> {
private:
    //todo skontrolovat ci to nerobí mem leaks
    StoredData * dataToCompare;
public:
    CriterionUJPrislusnost(StoredData &comparedData);

    bool evaluate(const StoredData &data) override;


};

CriterionUJPrislusnost::CriterionUJPrislusnost(StoredData &comparedData) :
    dataToCompare(&comparedData)
{

}

inline bool CriterionUJPrislusnost::evaluate(const StoredData &data) {
    return data.belongsTo(*dataToCompare);
}

