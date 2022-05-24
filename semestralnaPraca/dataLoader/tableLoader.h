//
// Created by Tobias on 22/05/2022.
//
#pragma once
#include "dataLoader.h"

#include "../../structures/table/table.h"
#include "storedData.h"
#include "uzemnaJednotka.h"
#include "ostatneUdaje.h"
#include "unsorted_sequence_table.h"
#include "sorted_sequence_table.h"

class TableLoader
{
public:
    TableLoader();

    ~TableLoader();

    void loadTable(structures::Table<wstring, StoredData *> &kraj,
                   structures::Table<wstring, StoredData *> &okres,
                   structures::Table<wstring, StoredData *> &obec,
                   structures::Table<wstring, StoredData *> &vzdelanie,
                   structures::Table<wstring, StoredData *> &nameIndex);

    void indexingTable(structures::UnsortedSequenceTable<wstring, StoredData *> kraj,
                       structures::UnsortedSequenceTable<wstring, StoredData *> okres,
                       structures::UnsortedSequenceTable<wstring, StoredData *> obec,
                       structures::SortedSequenceTable<wstring, StoredData *> vzdelanie,
                       structures::SortedSequenceTable<wstring, StoredData *> nameIndex,
                       structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> statIndex,
                       structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> krajIndex,
                       structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> okresIndex);
};

inline TableLoader::TableLoader() {

}

inline TableLoader::~TableLoader() {

}

inline void
TableLoader::loadTable(structures::Table<wstring, StoredData *> &kraj,
                       structures::Table<wstring, StoredData *> &okres,
                       structures::Table<wstring, StoredData *> &obec,
                       structures::Table<wstring, StoredData *> &vzdelanie,
                       structures::Table<wstring, StoredData *> &nameIndex)
{
    //------------------- Kraj ------------------
    DataLoader *loader = new DataLoader("../semestralnaPraca/dataLoader/rawData/kraje.csv");
    if (loader->isOpen()){
        loader->nextLine(); // aby sa preskočil header
        while (loader->nextLine()) {
            UzemnaJednotka *data = new UzemnaJednotka();
            while (loader->hasNextParameter()) {
                data->setNextParameter(loader->getNextParameter());
            }
            kraj.insert(data->getOfficialTitle(), data);
            nameIndex.insert(data->getOfficialTitle(), data);
        }
    }

    //------------------- Okres ------------------
    loader->openNew("../semestralnaPraca/dataLoader/rawData/okresy.csv");
    if (loader->isOpen()){
        loader->nextLine(); // aby sa preskočil header
        while (loader->nextLine()) {
            UzemnaJednotka *data = new UzemnaJednotka();
            while (loader->hasNextParameter()) {
                data->setNextParameter(loader->getNextParameter());
            }
            okres.insert(data->getOfficialTitle(), data);
            nameIndex.insert(data->getOfficialTitle(), data);
        }
    }

    //------------------- Obce ------------------
    loader->openNew("../semestralnaPraca/dataLoader/rawData/obce.csv");
    if (loader->isOpen()){
        loader->nextLine(); // aby sa preskočil header
        while (loader->nextLine()) {
            UzemnaJednotka *data = new UzemnaJednotka();
            while (loader->hasNextParameter()) {
                data->setNextParameter(loader->getNextParameter());
            }
            obec.insert(data->getOfficialTitle(), data);
            nameIndex.insert(data->getOfficialTitle(), data);
            if (data->getOfficialTitle().compare(data->at(3)) != 0) {
                nameIndex.insert(data->at(3), data);
            }
            if (data->at(3).compare(data->at(4)) != 0 && data->getOfficialTitle().compare(data->at(4))) {
                nameIndex.insert(data->at(4), data);
            }

        }
    }


    //---------- Pridanie miest pre Okres ---------
    for (auto item: okres) {
        auto data = item->accessData();
        if (data->getOfficialTitle().compare(data->at(3)) != 0 && !nameIndex.containsKey(data->at(3))) {
            nameIndex.insert(data->at(3), data);
        }
        if (data->at(3).compare(data->at(4)) != 0 && data->getOfficialTitle().compare(data->at(4)) && !nameIndex.containsKey(data->at(4))) {
            for (int i = 0; i < data->getSize(); ++i) {
                wcout << data->at(i) << L",\t";
            }
            wcout << endl;
            nameIndex.insert(data->at(4), data);
        }
    }

    //------------------- Vzdelavanie ------------------
    loader->openNew("../semestralnaPraca/dataLoader/rawData/vzdelanie.csv");
    if (loader->isOpen()){
        loader->nextLine(); // aby sa preskočil header
        while (loader->nextLine()) {
            OstatneUdaje *data = new OstatneUdaje(loader->getNextParameter(), loader->getNextParameter());
            while (loader->hasNextParameter()) {
                data->setNextParameter(loader->getNextParameter());
            }
            vzdelanie.insert(data->getCode(), data);
        }
    }

    delete loader;
}

inline void TableLoader::indexingTable(structures::UnsortedSequenceTable<wstring, StoredData *> kraj,
                                structures::UnsortedSequenceTable<wstring, StoredData *> okres,
                                structures::UnsortedSequenceTable<wstring, StoredData *> obec,
                                structures::SortedSequenceTable<wstring, StoredData *> vzdelanie,
                                structures::SortedSequenceTable<wstring, StoredData *> nameIndex,
                                structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> statIndex,
                                structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> krajIndex,
                                structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> okresIndex)
{
    //---------------- Indexovanie VUC STAT --------------------------------
    structures::ArrayList<StoredData *> *slovensko = new structures::ArrayList<StoredData *>;
    structures::ArrayList<StoredData *> *zahranicie = new structures::ArrayList<StoredData *>;
    for (auto item: kraj) {
        wstring kod = item->accessData()->at(5).substr(0,2);
        if (kod.compare(L"ZZ") != 0) {
            slovensko->add(item->accessData());
        } else {
            zahranicie->add(item->accessData());
        }
    }

}




