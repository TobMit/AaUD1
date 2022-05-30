#include "criterion.h"

#pragma once
class CriterionUJTyp : public Criterion<UJTyp> {
public:
    UJTyp evaluate(const StoredData &data) override;

};

inline UJTyp CriterionUJTyp::evaluate(const StoredData &data) {
    return data.getUJTyp();
}