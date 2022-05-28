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
#include "filterVZPocet.h"
#include "filterVZPodiel.h"
#include "advFilter.h"
#include "Criterion/criterionNazov.h"
#include "Criterion/criterionUJTyp.h"
#include "Criterion/criterionVZPocet.h"
#include "criterionVZPodiel.h"

enum class Color {
    Red,
    BrightGreen,
    Green,
    DarkGren,
    BrightBlue,
    DarkBlue,
    Yellow,
    Magenta,
    Cyan,
    White,
    Default

};

class Aplikacia {
private:
    structures::UnsortedSequenceTable<wstring, StoredData*> *stat;
    structures::UnsortedSequenceTable<wstring, StoredData*> *kraj;
    structures::UnsortedSequenceTable<wstring, StoredData*> *okres;
    structures::UnsortedSequenceTable<wstring, StoredData*> *obec;
    structures::SortedSequenceTable<wstring, StoredData*> *vzdelanieObec;
    structures::SortedSequenceTable<wstring, StoredData*> *vzdelanieOkres;
    structures::SortedSequenceTable<wstring, StoredData*> *vzdelanieKraj;
    structures::SortedSequenceTable<wstring, StoredData*> *vzdelanieStat;

    structures::SortedSequenceTable<wstring, StoredData*> *nameIndex;
    structures::SortedSequenceTable<wstring, StoredData*> *codeIndex;
    structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*> *statIndex;
    structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*> *krajIndex;
    structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData*>*> *okresIndex;


public:
    Aplikacia();

    ~Aplikacia();

    bool menu();
private:
    void bodoveVyhladavanie();

    void vypisIformacie(StoredData *data, wstring odsadenie);

    void filtrovanie();

    void vycistiTable(structures::Table<wstring, StoredData *> *table);

    void vicistiIndex(structures::SortedSequenceTable<wstring, structures::ArrayList<StoredData *> *> *pTable);

    void changeColor(Color color);

    static void resetColor();

    UJTyp prelozNaUJTyp(wstring naPreklad);
    /// Vypočitava predka, nekotroluje, či sa dá predok vypočítať. (Napr keď z kraja chceme získať okres)
    /// \param data
    /// \param uroven
    /// \return
    wstring vypocetVUJ(StoredData *data, UJTyp uroven);
    /// Okdstráni z dát nepotrebne údaje. Pozor nekontroluje ci sa jedná naozaj o kraj
    /// \param data
    /// \return
    static wstring krajGetCode(StoredData *data);

    Filter* filterPocet();
    Filter* filterPodiel();
    void vypisVZmenu();
};



