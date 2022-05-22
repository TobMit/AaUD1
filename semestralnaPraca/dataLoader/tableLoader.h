//
// Created by Tobias on 22/05/2022.
//
#pragma once
#include "dataLoader.h"

#include "../../structures/table/table.h"
#include "storedData.h"

class TableLoader
{
public:
    TableLoader();

    ~TableLoader();

    void loadTable(structures::Table<wstring, StoredData*> &kraj,
                   structures::Table<wstring, StoredData*> &okres,
                   structures::Table<wstring, StoredData*> &obec,
                   structures::Table<wstring, StoredData*> &vzdelanie);
};

inline TableLoader::TableLoader() {

}

inline TableLoader::~TableLoader() {

}

inline void TableLoader::loadTable(structures::Table<wstring, StoredData *> &kraj, structures::Table<wstring, StoredData *> &okres,
                                   structures::Table<wstring, StoredData *> &obec, structures::Table<wstring, StoredData *> &vzdelanie)
{

}




