//
// Created by Tobias on 25/05/2022.
//

#include "criterion.h"
#include "string"

#pragma once
class CriterionNazov : public Criterion<std::string> {
public:
    string evaluate(const StoredData &data) override;

};

inline string CriterionNazov::evaluate(const StoredData &data) {
    return data.getOfficialTitle();
}
