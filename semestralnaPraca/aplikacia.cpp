//
// Created by Tobias on 21/05/2022.
//

#include "aplikacia.h"

Aplikacia::Aplikacia() :
    kraj(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    okres(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    obec(new structures::UnsortedSequenceTable<wstring, StoredData*>),
    vzdelanie(new structures::SortedSequenceTable<wstring, StoredData*>),
    nameIndex(new structures::SortedSequenceTable<wstring, StoredData*>),
    statIndex(new structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*>),
    krajIndex(new structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*>),
    okresIndex(new structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*>)
{
    TableLoader tableLoader;
    cout << "Nacitavam data" << endl;
    tableLoader.loadTable(*kraj, *okres, *obec, *vzdelanie, *nameIndex);
    cout << "Indexujem" << endl;
    tableLoader.indexingTable(*kraj, *okres, *obec, *vzdelanie, *nameIndex,
                          *statIndex, *krajIndex, *okresIndex);

//    wstring test;
//    wcout << L"Zadaj nazov: ";
//    std::getline(wcin, test);
//    auto testKraj = nameIndex->find(test);
//    for (int i = 0; i < testKraj->getSize(); ++i) {
//        wcout << testKraj->at(i) << L"\t";
//    }
//    wcout << endl;
//    auto testVzdelanie = vzdelanie->find(testKraj->getCode());
//    auto testVzdelanieNew = dynamic_cast<OstatneUdaje*>(testVzdelanie);
//    if (testVzdelanieNew) {
//        for (int i = 0; i < testVzdelanieNew->getSize(); ++i) {
//            wcout << testVzdelanieNew->intAt(i) << L"\t";
//        }
//    }
//    wcout << endl << endl;

    for (auto ixStat: *statIndex) {
        wcout << ixStat->getKey() << endl;
        for (auto ixKraj: *ixStat->accessData()) {
            wcout << "\t";
            for (int i = 0; i < ixKraj->getSize(); ++i) {
                wcout << ixKraj->at(i) << L" ";
            }
            wcout << endl;
            auto ixOkres = krajIndex->find(ixKraj->at(5));
            for (auto item: *ixOkres) {
                wcout << "\t" << "\t";
                for (int i = 0; i < item->getSize(); ++i) {
                    wcout << item->at(i) << L" ";
                }
                wcout << endl;
            }
        }
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

    vicistiIndex(statIndex);
    delete statIndex;
    statIndex = nullptr;
    vicistiIndex(krajIndex);
    delete krajIndex;
    krajIndex = nullptr;
    vicistiIndex(okresIndex);
    delete okresIndex;
    okresIndex = nullptr;

}

void Aplikacia::vycistiTable(structures::Table<wstring, StoredData *> *table) {
    for (auto item: *table) {
        delete item->accessData();
    }
}

void Aplikacia::vicistiIndex(structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> *pTable) {
    for (auto item: *pTable) {
        delete item->accessData();
        item->accessData() = nullptr;
    }
}

