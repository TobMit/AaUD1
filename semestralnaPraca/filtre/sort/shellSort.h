//
// Created by Tobias on 28/05/2022.
//
#include <iostream>
#include <cmath>
#include "unsorted_sequence_table.h"
#include "array_list.h"

class ShellSort {
public:
    ShellSort();

private:
    void sortData(int krok, structures::UnsortedSequenceTable<string, StoredData *> &pTable, bool zozstupne);
    void printArray(structures::UnsortedSequenceTable<string, StoredData *> &pTable, int size);

};

inline ShellSort::ShellSort() {
    structures::UnsortedSequenceTable<string, StoredData *> *data = new structures::UnsortedSequenceTable<string, StoredData *>;
    for (int i = 1; i <= 99; i++) {
        data->insert(std::to_string(i), nullptr);
    }
    int size = data->size();
    sortData(log10(data->size()), *data, true);
    cout << "Sorted array: \n";
    printArray(*data, size);
    delete data;
}


inline void
ShellSort::sortData(int krok, structures::UnsortedSequenceTable<string, StoredData *> &pTable, bool zozstupne) {
    for (int delta = 0; delta < krok; ++delta) {
        for (int i = delta; i < pTable.size() ; i += krok) {
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
    if (krok > 1)
        sortData(krok-1, pTable,zozstupne);

}

inline void ShellSort::printArray(structures::UnsortedSequenceTable<string, StoredData *> &pTable, int size) {
    int i;
    for (i = 0; i < size; i++)
        cout << pTable.getItemAtIndex(i).getKey() << " ";
    cout << endl;
}
