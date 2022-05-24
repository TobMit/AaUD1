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

    for (auto arrKraj: *statIndex) {
        wcout << "\x1B[91m"; // cislo za [nastavi farbu podla ANSI escape sequences
        wcout << arrKraj->getKey() << endl;
        for (auto ixKraj: *arrKraj->accessData()) {
            wcout << "\x1B[92m";
            wcout << "\t";
            for (int i = 0; i < ixKraj->getSize(); ++i) {
                wcout << ixKraj->at(i) << L" ";
            }
            wcout << endl;
            auto arrOkres = krajIndex->find(ixKraj->at(5));
            for (auto ixOkres: *arrOkres) {
                wcout << "\x1B[94m";
                wcout << "\t" << "\t";
                for (int i = 0; i < ixOkres->getSize(); ++i) {
                    wcout << ixOkres->at(i) << L" ";
                }
                wcout << endl;
                wcout << "\x1B[0m";
                auto arrObec = okresIndex->find(ixOkres->getCode());
                for (auto ixObce: *arrObec) {
                    wcout << "\t" << "\t" << "\t";
                    for (int i = 0; i < ixObce->getSize(); ++i) {
                        wcout << ixObce->at(i) << L" ";
                    }
                    wcout << endl;
                }
            }
        }
    }
    wcout << "\x1B[0m"; // reset farby na zakladne
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

