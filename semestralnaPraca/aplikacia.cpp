//
// Created by Tobias on 21/05/2022.
//

#include "aplikacia.h"

Aplikacia::Aplikacia() :
    kraj(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    okres(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    obec(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    vzdelanie(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    nameIndex(new structures::SortedSequenceTable<wstring, StoredData*>)
{
    TableLoader tableLoader;
    tableLoader.loadTable(*kraj, *okres, *obec, *vzdelanie, *nameIndex);

    wstring test;
    wcout << L"Zadaj nazov: ";
    std::getline(wcin, test);
    auto testKraj = nameIndex->find(test);
    for (int i = 0; i < testKraj->getSize(); ++i) {
        wcout << testKraj->at(i) << L"\t";
    }
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

    delete nameIndex;
    nameIndex = nullptr;
}

void Aplikacia::vycistiTable(structures::Table<wstring, StoredData *> *table) {
    for (auto item: *table) {
        delete item->accessData();
    }
}

