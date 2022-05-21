//
// Created by Tobias on 21/05/2022.
//

#include "aplikacia.h"

Aplikacia::Aplikacia() :
    kraj(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    okres(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    obec(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    loader(new DataLoader("../semestralnaPraca/dataLoader/rawData/kraje.csv"))
{

}

Aplikacia::~Aplikacia() {
    vycistiTable(kraj);
    delete kraj;
    kraj = nullptr;
    vycistiTable(kraj);
    delete kraj;
    okres = nullptr;
    vycistiTable(okres);
    delete okres;
    obec = nullptr;
    vycistiTable(obec);
    delete obec;
    obec = nullptr;
    delete loader;
    loader = nullptr;
}

void Aplikacia::vycistiTable(structures::UnsortedSequenceTable<wstring, StoredData *> *table) {
    for (auto item: *table) {
        delete item->accessData();
    }
}

