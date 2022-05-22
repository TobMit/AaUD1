//
// Created by Tobias on 22/05/2022.
//
#pragma once
#include "dataLoader.h"

#include "../../structures/table/table.h"
#include "storedData.h"
#include "uzemnaJednotka.h"

class TableLoader
{
public:
    TableLoader();

    ~TableLoader();

    void loadTable(structures::Table<wstring, StoredData *> &kraj, structures::Table<wstring, StoredData *> &okres,
                   structures::Table<wstring, StoredData *> &obec,
                   structures::Table<wstring, StoredData *> &vzdelanie,
                   structures::Table<wstring, StoredData *> &nameIndex);
};

inline TableLoader::TableLoader() {

}

inline TableLoader::~TableLoader() {

}

inline void
TableLoader::loadTable(structures::Table<wstring, StoredData *> &kraj, structures::Table<wstring, StoredData *> &okres,
                       structures::Table<wstring, StoredData *> &obec,
                       structures::Table<wstring, StoredData *> &vzdelanie,
                       structures::Table<wstring, StoredData *> &nameIndex)
{
    DataLoader loader;
    loader.openNew("../semestralnaPraca/dataLoader/rawData/kraje.csv");
    if (loader.isOpen()){
        while (loader.nextLine()) {
            UzemnaJednotka *data = new UzemnaJednotka();
            while (loader.hasNextParameter()) {
                data->setNextParameter(loader.getNextParameter());
            }
            kraj.insert(data->getOfficialTitle(), data);
            nameIndex.insert(data->getOfficialTitle(), data);
        }
    }
}




