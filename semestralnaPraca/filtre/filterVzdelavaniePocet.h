//
// Created by Tobias on 26/05/2022.
//
#pragma once

#include "filter.h"

class FilterVzPocet : Filter {
public:
    bool pass(const StoredData &data) override;
private:

};

inline bool FilterVzPocet::pass(const StoredData &data) {
    return false;
}
