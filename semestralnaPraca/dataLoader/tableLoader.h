//
// Created by Tobias on 06/05/2022.
//
#pragma once
#include <string>
#include "structure.h"
#include "table/table.h"
#include "dataLoader/dataLoader.h"
#include "dataStructure/storedData.h"

using namespace structures;
class TableLoader {

public:
    TableLoader();
    ~TableLoader();
    void loadData(Table<wstring, StoredData *> &kraj, Table<wstring, StoredData *> &okres,
                  Table<wstring, StoredData *> &obec,
                  Table<wstring, StoredData *> &vzdelanie,
                  Table<wstring, StoredData *> &nameIndex);
};

TableLoader::~TableLoader() {

}

void TableLoader::loadData(Table<wstring, StoredData *> &kraj, Table<wstring, StoredData *> &okres,
                           Table<wstring, StoredData *> &obec, Table<wstring, StoredData *> &vzdelanie,
                           Table<wstring, StoredData *> &nameIndex)
{
    DataLoader loader;
    loader.openNew("../semestralnaPraca/dataLoader/rawData/kraje.csv");

}


