//
// Created by Tobias on 26/05/2022.
//
#pragma once

#include "storedData.h"

class Filter {
public:
    virtual bool pass(const StoredData &data) = 0;
};

