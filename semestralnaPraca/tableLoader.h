//
// Created by Tobias on 06/05/2022.
//
#pragma once
#include <string>
#include "structure.h"
#include "../structures/table/table.h"
#include "dataLoader/dataLoader.h"
#include "dataStructure/storedData.h"

using namespace structures;
class TableLoader {
private:
    DataLoader *dataLoader;
public:
    TableLoader();
    ~TableLoader();
    void loadData(Table<wstring, StoredData*> &kraj,
                  Table<wstring, StoredData*> &okres,
                  Table<wstring, StoredData*> &obec,
                  Table<wstring, StoredData*> &vzdelanie);
};

TableLoader::~TableLoader() {
    delete dataLoader;
    dataLoader = nullptr;
}


