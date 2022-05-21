//
// Created by Tobias on 21/05/2022.
//
#pragma once
#include "iostream"
#include "dataLoader.h"
#include "uzemnaJednotka.h"
#include "storedData.h"
#include "ostatneUdaje.h"
#include "../structures/table/table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "../structures/table/sorted_sequence_table.h"

class Aplikacia {
private:
    structures::UnsortedSequenceTable<wstring, StoredData*> *kraj;
    structures::UnsortedSequenceTable<wstring, StoredData*> *okres;
    structures::UnsortedSequenceTable<wstring, StoredData*> *obec;
    DataLoader *loader;

public:
    Aplikacia();

    ~Aplikacia();
private:
    void vycistiTable(structures::UnsortedSequenceTable<wstring, StoredData*> *table);
};



