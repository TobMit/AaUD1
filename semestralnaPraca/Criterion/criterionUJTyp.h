//
// Created by Tobias on 25/05/2022.
//

#include "criterion.h"
#include "string"

#pragma once
class CriterionUJTyp : Criterion<UJTyp> {
public:
    UJTyp evaluate(const StoredData &data) override;

};

inline UJTyp CriterionUJTyp::evaluate(const StoredData &data) {
    return data.getUJTyp();
}