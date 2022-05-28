//
// Created by Tobias on 28/05/2022.
//
#include <iostream>
#include "unsorted_sequence_table.h"
#include "array_list.h"

class ShellSort {
public:
    ShellSort();

private:
    void sortData(structures::UnsortedSequenceTable<int, StoredData *> &pTable, int nSize, bool zozstupne);
    void printArray(structures::UnsortedSequenceTable<int, StoredData *> &pTable, int size);

};

inline ShellSort::ShellSort() {
    structures::UnsortedSequenceTable<int, StoredData *> *data = new structures::UnsortedSequenceTable<int, StoredData *>;
    for (int i = 1; i <= 99; i++) {
        data->insert(i, nullptr);
    }
    int size = data->size();
    sortData(*data, size, false);
    cout << "Sorted array: \n";
    printArray(*data, size);
    delete data;
}


inline void ShellSort::sortData(structures::UnsortedSequenceTable<int, StoredData *> &pTable, int nSize, bool zozstupne) {
    for (int krok = nSize / 2; krok > 0; krok /= 2) {
        for (int delta = 0; delta < krok ; delta++) {
            for (int i = delta; i < nSize; i += krok) {
                int j = i;
                if (!zozstupne) {
                    while (j - krok >= delta && pTable.getItemAtIndex(j).getKey() < pTable.getItemAtIndex(j - krok).getKey()) {
                        structures::Utils::swap(pTable.getItemAtIndex(j), pTable.getItemAtIndex(j - krok));
                        j -= krok;
                    }
                } else {
                    while (j - krok >= delta && pTable.getItemAtIndex(j).getKey() > pTable.getItemAtIndex(j - krok).getKey()) {
                        structures::Utils::swap(pTable.getItemAtIndex(j), pTable.getItemAtIndex(j - krok));
                        j -= krok;
                    }
                }
            }

        }

    }

}

inline void ShellSort::printArray(structures::UnsortedSequenceTable<int, StoredData *> &pTable, int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << pTable.getItemAtIndex(i).getKey() << " ";
    cout << endl;
}
