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
#include "shellSort.h"

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
    structures::UnsortedSequenceTable<string, StoredData*> *stat;
    structures::UnsortedSequenceTable<string, StoredData*> *kraj;
    structures::UnsortedSequenceTable<string, StoredData*> *okres;
    structures::UnsortedSequenceTable<string, StoredData*> *obec;
    structures::SortedSequenceTable<string, StoredData*> *vzdelanieObec;
    structures::SortedSequenceTable<string, StoredData*> *vzdelanieOkres;
    structures::SortedSequenceTable<string, StoredData*> *vzdelanieKraj;
    structures::SortedSequenceTable<string, StoredData*> *vzdelanieStat;

    structures::SortedSequenceTable<string, StoredData*> *nameIndex;
    structures::SortedSequenceTable<string, StoredData*> *codeIndex;
    structures::SortedSequenceTable<string, structures::ArrayList<StoredData*>*> *statIndex;
    structures::SortedSequenceTable<string, structures::ArrayList<StoredData*>*> *krajIndex;
    structures::SortedSequenceTable<string, structures::ArrayList<StoredData*>*> *okresIndex;


public:
    Aplikacia();

    ~Aplikacia();

    bool menu();
private:
    void bodoveVyhladavanie();

    void vypisIformacie(StoredData *data, string odsadenie);

    void filtrovanie();

    void vycistiTable(structures::Table<string, StoredData *> *table);

    void vicistiIndex(structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> *pTable);

    void changeColor(Color color);

    static void resetColor();

    UJTyp prelozNaUJTyp(string naPreklad);
    /// Vypočitava predka, nekotroluje, či sa dá predok vypočítať. (Napr keď z kraja chceme získať okres)
    /// \param data
    /// \param uroven
    /// \return
    string vypocetVUJ(StoredData *data, UJTyp uroven);
    /// Okdstráni z dát nepotrebne údaje. Pozor nekontroluje ci sa jedná naozaj o kraj
    /// \param data
    /// \return
    static string krajGetCode(StoredData *data);

    Filter* filterPocet();
    Filter* filterPodiel();
    void vypisVZmenu();
};



