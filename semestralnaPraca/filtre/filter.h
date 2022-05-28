//
// Created by Tobias on 26/05/2022.
//
#pragma once

#include "storedData.h"
#include "criterion.h"

class Filter {
public:
    virtual bool pass(const StoredData *data) = 0;
    virtual ~Filter() = default;
};

template <typename  ValueType>
class FilterWithCriterion : public Filter {
    Criterion<ValueType> *criterion;
protected:
    virtual bool passFilter(ValueType pValue) = 0;
public:
    explicit FilterWithCriterion(Criterion<ValueType> *pCriterion) :
        criterion(pCriterion) {};
    ~FilterWithCriterion() {
        delete criterion;
        criterion = nullptr;
    }
    inline bool pass (const StoredData* data) override {
        return passFilter(criterion->evaluate(data));
    }
};

template <typename ValueType>
class Filter_fi : public FilterWithCriterion<ValueType> {
    ValueType value;
protected:
    bool passFilter(ValueType pValue) override {
        return value == pValue;
    }
public:
    explicit Filter_fi(Criterion<ValueType> *criterion) : FilterWithCriterion<ValueType>(criterion) {
    }
};

template <typename ValueType>
class Filter_FI : public FilterWithCriterion<ValueType> {
    ValueType min;
    ValueType max;
protected:
    inline bool passFilter(ValueType pValue) override {
        return pValue >= min && pValue <= max;
    }
public:
    explicit Filter_FI(Criterion<ValueType> *criterion, ValueType pMin, ValueType pMax) :
            FilterWithCriterion<ValueType>(criterion),
            min(pMin),
            max(pMax)
    {
    }
};
