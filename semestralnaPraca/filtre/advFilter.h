//
// Created by Tobias on 28/05/2022.
//
#pragma once
#include "../../structures/list/array_list.h"
#include "filter.h"

class CompositeFilter : public Filter {
protected:
    structures::ArrayList<Filter*> registredFilters;
public:
    void registerFilter(Filter * filter) {
        registredFilters.add(filter);
    }
    ~CompositeFilter(){
        for (auto filter: registredFilters) {
            delete filter;
        }
    }
};

class AND_Filter : public CompositeFilter {
public:
    inline bool pass(const StoredData &data) override {
        bool returnValue = true;
        for (auto filter: registredFilters) {
            returnValue = returnValue && filter->pass(data);
        }
        return returnValue;
    }

    inline void coutEvaluate(const StoredData &data, string text) override {
        for (int i = 1; i <= registredFilters.size(); ++i) {
            cout << i << ". " << text;
            registredFilters.at(i-1)->coutEvaluate(data, "");
        }
    }

    double filterEvaluate(const StoredData &data) override {
        return 0;
    }
};

class OR_Filter : public CompositeFilter {
public:
    inline bool pass(const StoredData &data) override {
        bool returnValue = true;
        for (auto filter: registredFilters) {
            returnValue = returnValue || filter->pass(data);
        }
        return returnValue;
    }

    inline void coutEvaluate(const StoredData &data, string text) override {
        for (int i = 1; i <= registredFilters.size(); ++i) {
            cout << i << ". " << text;
            registredFilters.at(i-1)->coutEvaluate(data, "");
        }
    }

    double filterEvaluate(const StoredData &data) override {
        return 0;
    }
};