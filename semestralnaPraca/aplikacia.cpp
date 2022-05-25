//
// Created by Tobias on 21/05/2022.
//

#include "aplikacia.h"

Aplikacia::Aplikacia() :
        kraj(new structures::UnsortedSequenceTable<wstring, StoredData*>),
        okres(new structures::UnsortedSequenceTable<wstring, StoredData*>),
        obec(new structures::UnsortedSequenceTable<wstring, StoredData*>),
        vzdelanieObec(new structures::SortedSequenceTable<wstring, StoredData*>),
        vzdelanieOkres(new structures::SortedSequenceTable<wstring, StoredData*>),
        vzdelanieKraj(new structures::SortedSequenceTable<wstring, StoredData*>),
        nameIndex(new structures::SortedSequenceTable<wstring, StoredData*>),
        codeIndex(new structures::SortedSequenceTable<wstring, StoredData*>),
        statIndex(new structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*>),
        krajIndex(new structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*>),
        okresIndex(new structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*>)
{
    TableLoader tableLoader;
    cout << "Nacitavam data" << endl;
    tableLoader.loadTable(*kraj, *okres, *obec, *vzdelanieObec, *nameIndex);
    cout << "Indexujem" << endl;
    tableLoader.indexingTable(*kraj, *okres, *obec, *vzdelanieObec, *nameIndex,
                              *statIndex, *krajIndex, *okresIndex);
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
    vycistiTable(vzdelanieObec);
    delete vzdelanieObec;
    vzdelanieObec = nullptr;
    vycistiTable(vzdelanieOkres);
    delete vzdelanieOkres;
    vzdelanieOkres = nullptr;
    vycistiTable(vzdelanieKraj);
    delete vzdelanieKraj;
    vzdelanieKraj = nullptr;

    delete nameIndex;
    nameIndex = nullptr;
    delete codeIndex;
    codeIndex = nullptr;

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

void Aplikacia::menu() {
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
        changeColor(Color::Red);
        wcout << arrKraj->getKey() << endl;
        for (auto ixKraj: *arrKraj->accessData()) {
            changeColor(Color::Green);
            wcout << "\t";
            for (int i = 0; i < ixKraj->getSize(); ++i) {
                wcout << ixKraj->at(i) << L" ";
            }
            wcout << endl;
            auto arrOkres = krajIndex->find(ixKraj->at(5));
            for (auto ixOkres: *arrOkres) {
                changeColor(Color::Magenta);
                wcout << "\t" << "\t";
                for (int i = 0; i < ixOkres->getSize(); ++i) {
                    wcout << ixOkres->at(i) << L" ";
                }
                wcout << endl;
                resetColor();
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
    resetColor();
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

void Aplikacia::changeColor(Color color) {
    switch (color) {
        case Color::Red:
            wcout << "\x1B[91m";
            break;

        case Color::Green:
            wcout << "\x1B[92m";
            break;

        case Color::Blue:
            wcout << "\x1B[94m";
            break;

        case Color::Yellow:
            wcout << "\x1B[93m";
            break;

        case Color::Magenta:
            wcout << "\x1B[95m";
            break;

        case Color::Cyan:
            wcout << "\x1B[96m";
            break;

        case Color::White:
            wcout << "\x1B[97m";
            break;

        default:
            wcout << "\x1B[97m";
            break;
    }
}

void Aplikacia::resetColor() {
    wcout << "\x1B[0m"; // reset farby na zakladne
}
