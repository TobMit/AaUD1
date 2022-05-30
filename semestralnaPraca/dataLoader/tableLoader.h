#pragma once
#include "dataLoader.h"

#include "../../structures/table/table.h"
#include "storedData.h"
#include "uzemnaJednotka.h"
#include "ostatneUdaje.h"
#include "unsorted_sequence_table.h"
#include "sorted_sequence_table.h"

class TableLoader
{
public:
    TableLoader();

    ~TableLoader();

    void loadTable(structures::Table<string, StoredData *> &kraj, structures::Table<string, StoredData *> &okres,
                   structures::Table<string, StoredData *> &obec, structures::Table<string, StoredData *> &vzdelanie,
                   structures::Table<string, StoredData *> &nameIndex,
                   structures::Table<string, StoredData *> &codeIndex);

    void indexingTable(structures::UnsortedSequenceTable<string, StoredData *> &stat,
                       structures::UnsortedSequenceTable<string, StoredData *> &kraj,
                       structures::UnsortedSequenceTable<string, StoredData *> &okres,
                       structures::UnsortedSequenceTable<string, StoredData *> &obec,
                       structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &statIndex,
                       structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &krajIndex,
                       structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &okresIndex);

    void spracujVzdelanie(structures::SortedSequenceTable<string, StoredData *> &codeIndex,
                          structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &statIndex,
                          structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &krajIndex,
                          structures::SortedSequenceTable<string, structures::ArrayList<StoredData *> *> &okresIndex,
                          structures::SortedSequenceTable<string, StoredData *> &vzdelanieObec,
                          structures::SortedSequenceTable<string, StoredData *> &vzdelanieOkres,
                          structures::SortedSequenceTable<string, StoredData *> &vzdelanieKraj,
                          structures::SortedSequenceTable<string, StoredData *> &vzdelanieStat);
private:
    int spocitajVzdelanie(int index, structures::ArrayList<StoredData *> &data, structures::SortedSequenceTable<string, StoredData *> &vzdelanieUJ);
};





