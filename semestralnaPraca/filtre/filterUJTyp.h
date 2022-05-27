//
// Created by Tobias on 27/05/2022.
//
#include "filter.h"

class FilterUJTyp : Filter<UJTyp> {
private:
    UJTyp compareTyp;
public:
    FilterUJTyp(UJTyp typ) :
        compareTyp(typ)
    {};
    bool pass(const StoredData &data, Criterion<UJTyp> *criterion) override;
};

inline bool FilterUJTyp::pass(const StoredData &data, Criterion<UJTyp> *criterion) {
    return criterion->evaluate(data) == compareTyp;
}


