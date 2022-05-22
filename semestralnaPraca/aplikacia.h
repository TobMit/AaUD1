//
// Created by Tobias on 21/05/2022.
//
#pragma once
#include "iostream"
#include "dataLoader/dataLoader.h"
#include "dataStructure/storedData.h"
#include "../structures/table/table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "../structures/table/sorted_sequence_table.h"
#include "tableLoader.h"

class Aplikacia {
private:
    structures::UnsortedSequenceTable<wstring, StoredData*> *kraj;
    structures::UnsortedSequenceTable<wstring, StoredData*> *okres;
    structures::UnsortedSequenceTable<wstring, StoredData*> *obec;
    structures::UnsortedSequenceTable<wstring, StoredData*> *vzdelanie;

    structures::SortedSequenceTable<wstring, StoredData*> *nameIndex;

public:
    Aplikacia();

    ~Aplikacia();
private:
    void vycistiTable(structures::Table<wstring, StoredData *> *table);
};



