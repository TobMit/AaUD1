//
// Created by Tobias on 06/05/2022.
//
#pragma once
#include <string>
#include "structure.h"
#include "../structures/table/table.h"
#include "dataLoader/dataLoader.h"
#include "dataStructure/storedData.h"

class TableLoader {
public:
    TableLoader();
    ~TableLoader();
    void loadData(structures::Table<std::wstring, StoredData<auto>>&tabler, DataLoader &loader);
};


