//
// Created by Tobias on 21/05/2022.
//

#include "aplikacia.h"

Aplikacia::Aplikacia() :
    kraj(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    okres(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    obec(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    vzdelanie(new structures::UnsortedSequenceTable<wstring, StoredData*>)
{

}

Aplikacia::~Aplikacia() {
    vycistiTable(kraj);
    delete kraj;
    kraj = nullptr;
    vycistiTable(okres);
    delete okres;
    okres = nullptr;
    vycistiTable(obec);
    delete obec;
    obec = nullptr;
    vycistiTable(vzdelanie);
    delete vzdelanie;
    vzdelanie = nullptr;
}

void Aplikacia::vycistiTable(structures::UnsortedSequenceTable<wstring, StoredData *> *table) {
    if (table->size() != 0) {
        for (auto item: *table) {
            delete item->accessData();
        }
    }
}

void Aplikacia::loadTable() {

}

