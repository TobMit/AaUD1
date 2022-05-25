//
// Created by Tobias on 25/05/2022.
//

#include "criterion.h"
#include "string"

#pragma once
class CriterionNazov : Criterion<std::wstring> {
public:
    wstring evaluate(const StoredData &data) override;

};

inline wstring CriterionNazov::evaluate(const StoredData &data) {
    return data.getOfficialTitle();
}
