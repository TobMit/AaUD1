//
// Created by Tobias on 28/05/2022.
//
#pragma once
#include <iostream>
#include <cmath>
#include "unsorted_sequence_table.h"
#include "array_list.h"

template<typename critVal>
class ShellSort {
public:
    ShellSort();

    void sordData(structures::UnsortedSequenceTable<string, StoredData *> &pTable,
                  Criterion<critVal> *criterion, bool zozstupne);
private:
    void sortData(int krok, structures::UnsortedSequenceTable<string, StoredData *> &pTable,
                  Criterion<critVal> *criterion, bool zozstupne);
    void printTable(structures::UnsortedSequenceTable<string, StoredData *> &pTable, int size);

};

template<typename critVal>
inline ShellSort<critVal>::ShellSort() {
//    structures::UnsortedSequenceTable<string, StoredData *> *data = new structures::UnsortedSequenceTable<string, StoredData *>;
//    for (int i = 1; i <= 99; i++) {
//        data->insert(std::to_string(i), nullptr);
//    }
//    int size = data->size();
//    sortData(log10(data->size()), *data, true);
//    cout << "Sorted array: \n";
//    printTable(*data, size);
//    delete data;
}


template<typename critVal>
inline void ShellSort<critVal>::sordData(structures::UnsortedSequenceTable<string, StoredData *> &pTable,
                                  Criterion<critVal> *criterion, bool zozstupne) {
    if (pTable.size() < 10) {
        sortData(pTable.size()/2, pTable, criterion, zozstupne);
    } else {
        sortData(log10(pTable.size()), pTable, criterion, zozstupne);
    }
}
template<typename critVal>
inline void ShellSort<critVal>::sortData(int krok, structures::UnsortedSequenceTable<string, StoredData *> &pTable,
                                         Criterion<critVal> *criterion, bool zozstupne) {
    for (int delta = 0; delta < krok; ++delta) {
        for (int i = delta; i < pTable.size() ; i += krok) {
            int j = i;
            if (!zozstupne) {
                while (j - krok >= delta && criterion->evaluate(*pTable.getItemAtIndex(j).accessData()) < criterion->evaluate(*pTable.getItemAtIndex(j - krok).accessData())) {
                    structures::Utils::swap(pTable.getItemAtIndex(j), pTable.getItemAtIndex(j - krok));
                    j -= krok;
                }
            } else {
                while (j - krok >= delta && criterion->evaluate(*pTable.getItemAtIndex(j).accessData()) > criterion->evaluate(*pTable.getItemAtIndex(j - krok).accessData())) {
                    structures::Utils::swap(pTable.getItemAtIndex(j), pTable.getItemAtIndex(j - krok));
                    j -= krok;
                }
            }
        }
    }
    if (krok > 1)
        sortData(krok - 1, pTable, criterion, zozstupne);

}

template<typename critVal>
inline void ShellSort<critVal>::printTable(structures::UnsortedSequenceTable<string, StoredData *> &pTable, int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << pTable.getItemAtIndex(i).getKey() << " ";
    cout << endl;
}
