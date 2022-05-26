//
// Created by Tobias on 21/05/2022.
//

#include "aplikacia.h"

Aplikacia::Aplikacia() :
        stat(new structures::UnsortedSequenceTable<wstring, StoredData*>),
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
    auto *slovensko = new UzemnaJednotka(UJTyp::Stat, L"1", L"SK", L"Slovenska republika", L"Slovensko", L"Slovensko", L"1");
    stat->insert(slovensko->getCode(), slovensko);
    auto *zahranicie = new UzemnaJednotka(UJTyp::Stat, L"2", L"ZZ", L"Zahranicie", L"", L"", L"2");
    stat->insert(zahranicie->getCode(), zahranicie);

    TableLoader tableLoader;
    cout << "Nacitavam data" << endl;
    tableLoader.loadTable(*kraj, *okres, *obec, *vzdelanieObec, *nameIndex, *codeIndex);
    cout << "Indexujem" << endl;
    tableLoader.indexingTable(*stat, *kraj, *okres, *obec,
                              *statIndex, *krajIndex, *okresIndex);
    nameIndex->insert(slovensko->getOfficialTitle(), slovensko);
    nameIndex->insert(slovensko->at(4), slovensko);
    nameIndex->insert(zahranicie->getCode(), zahranicie);

    codeIndex->insert(slovensko->getCode(), slovensko);
    codeIndex->insert(zahranicie->getCode(), zahranicie);

}

Aplikacia::~Aplikacia() {
    vycistiTable(stat);
    delete stat;
    stat = nullptr;
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
//    wcout << L"Zadaj code: ";
//    std::getline(wcin, test);
//    auto testData = codeIndex->find(test);
//    for (int i = 0; i < testData->getSize(); ++i) {
//        wcout << testData->at(i) << L"\t";
//    }
//
//    wcout << endl << endl;

    for (auto arrKraj: *statIndex) {
        changeColor(Color::Red);
        auto ixStat = codeIndex->find(arrKraj->getKey());
        for (int i = 0; i < ixStat->getSize(); ++i) {
            wcout << ixStat->at(i) << L" ";
        }
        wcout << endl;
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
