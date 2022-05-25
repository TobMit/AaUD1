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

    void indexingTable(structures::UnsortedSequenceTable<wstring, StoredData *> &kraj,
                       structures::UnsortedSequenceTable<wstring, StoredData *> &okres,
                       structures::UnsortedSequenceTable<wstring, StoredData *> &obec,
                       structures::SortedSequenceTable<wstring, StoredData *> &vzdelanie,
                       structures::SortedSequenceTable<wstring, StoredData *> &nameIndex,
                       structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> &statIndex,
                       structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> &krajIndex,
                       structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> &okresIndex);
};





